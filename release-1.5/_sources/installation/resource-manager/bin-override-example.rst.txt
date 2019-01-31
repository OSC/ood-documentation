.. _bin-overrides:

A Working Example Of A ``bin_overrides`` Script
===============================================

``sbatch`` is the Slurm scheduler's submission client. In this example we will show how cluster configuration's ``bin_overrides`` may be used to change default behavior.

This example demonstrates a few uses of wrapping the default scheduler clients:

* Using SSH from the web host to launch ``sbatch`` on the submit host
* Altering arguments passed to the scheduler
* Altering the script passed to ``sbatch`` (which is almost certainly a terrible idea)
* Logging values passed to the scheduler in a custom location (note that the values passed to ``sbatch`` are also logged to the PUN log file at ``/var/log/ondemand-nginx/$USER/error.log`` by the Dashboard and Job Composer when submitting jobs)

.. warning::

    This wrapper when used with the OOD Job Composer will place any ``stdout`` or ``stderr`` files in ``$HOME`` instead of the usual location of ``$HOME/ondemand/data/sys/myjobs/projects/default/$JOBID``.

.. code-block:: python
   
  #!/usr/bin/env python36
  from getpass import getuser
  from select import select
  from sh import ssh, ErrorReturnCode  # pip3 install sh
  import logging
  import os
  import re
  import sys

  '''
  An example of a `bin_overrides` replacing Slurm `sbatch` for use with Open OnDemand.

  Requirements:

  - $USER must be able to SSH from web node to submit node without using a password

  Examples:

  - SSH's from a web node to a submit node
  - Logging values passed to sbatch
  - Altering arguments passed to sbatch
  - Altering the script passed to sbatch (which is almost certainly a bad idea)

  Thoughts for further development:

  - Add out of script configuration (SUBMISSION_NODE, logging preferences)
  - Improve logging permission handling (right now it needs to be done manually)
  - Solve problem of CWD being set to the $HOME

  Note that as of v1.4.9 OOD's job adapters parse stdout but may not validate;
  changing the format of sbatch's stdout can break applications. For exit codes
  OOD's job adapters require that the wrapper exit 0 on success and non 0 on
  failure.
  '''

  logging.basicConfig(filename='/tmp/sbatch.log', level=logging.INFO)

  SUBMISSION_NODE = 'head'
  USER = os.environ['USER']


  def run_remote_sbatch(script, *argv):
    """
    @brief      SSH and submit the job from the submission node
    
    @param      script (str)  The script
    @param      argv (list<str>)    The argument vector for sbatch
    
    @return     output (str) The merged stdout/stderr of the remote sbatch call
    """

    output = None

    try:
      result = ssh(
        '@'.join([USER, SUBMISSION_NODE]),
        '-oBatchMode=yes',  # ensure that SSH does not hang waiting for a password that will never be sent
        '/opt/slurm/bin/sbatch',  # the real sbatch on the remote
        *argv,  # any arguments that sbatch should get
        _in=script,  # redirect the script's contents into stdin
        _err_to_out=True  # merge stdout and stderr
      )

      output = result.stdout.decode('utf-8')
      logging.info(output)
    except ErrorReturnCode as e:
      output = e.stdout.decode('utf-8')
      logging.info(output)
      print(output)
      sys.exit(e.exit_code)

    return output


  def filter_argv(argv):
    """
    @brief      Filter the argument vector to add or remove arguments
    
    @param      argv (list<str>) The original argument vector passed to sbatch
    
    @return     argv (list<str>) The altered argument vector to pass to the real sbatch
    """

    logging.info('ARGV:')
    for arg in argv:
      logging.info(argv)

    argv += ['--export=THE_ANSWER=42']

    return argv


  def filter_script(script):
    """
    @brief      Alter the script that the user is sending to sbatch

    This is a terrible fragile idea, but it is possible, so let's try it! We will set
    an environment variable and cleanup /tmp after the user.
    
    @param      script (str)  The script
    
    @return     script (str) The altered script
    """

    shebang = '#!/bin/bash\n'
    match = re.match('^(#!.+)\n', script)
    if match:
      shebang = match.group()
      script  = script.replace(shebang, '')

    return shebang + '''
    export THE_QUESTION='6*9=?'
    ''' + script + '''
    rm -rf /tmp 2>/dev/null
    '''


  def load_script():
    """
    @brief      Loads a script from stdin.
    
    With OOD and Slurm the user's script is read from disk and passed to sbatch via stdin
    https://github.com/OSC/ood_core/blob/5b4d93636e0968be920cf409252292d674cc951d/lib/ood_core/job/adapters/slurm.rb#L138-L148

    @return     script (str) The script content
    """
    # Do not hang waiting for stdin that is not coming
    if not select([sys.stdin], [], [], 0.0)[0]:
      print('No script available on stdin!')
      sys.exit(1)

    return sys.stdin.read()


  def main():
    """
    @brief      SSHs from web node to submit node and executes the remote sbatch.
    """
    output = run_remote_sbatch(
      filter_script(load_script()),
      filter_argv(sys.argv[1:])
    )

    print(output)

  if __name__ == '__main__':
    main()