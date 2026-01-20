# OOD Documentation

[![Build Status](https://travis-ci.org/OSC/ood-documentation.svg?branch=develop)](https://travis-ci.org/OSC/ood-documentation)
[![GitHub License](https://img.shields.io/badge/license-MIT-green.svg)](https://opensource.org/licenses/MIT)
[![Documentation License](https://img.shields.io/badge/license-CC%20BY%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by/4.0)

- Website: http://openondemand.org/
- Documentation: https://osc.github.io/ood-documentation/latest/
- Main code repo: https://github.com/OSC/ondemand
- Core library repo: https://github.com/OSC/ood_core
- Original repo with JOSS publication: https://github.com/OSC/Open-OnDemand

## Usage

Visit the [latest Open OnDemand documentation](https://osc.github.io/ood-documentation/latest/) 
to see the most recently published release.

To view changes that have not yet been released, see the [development documentation](https://osc.github.io/ood-documentation/develop/).

Open OnDemand also maintains documentation for past versions. To access them, navigate 
to the bottom of the sidebar menu in the documentation.  


## Development

Open pull requests to the develop branch, which is the main branch of this repo. This repo uses the [gitflow branching model](https://nvie.com/posts/a-successful-git-branching-model/).

There are two ways to build the documentation.

1. Use the Docker image that is used to build them in production using Travis.
2. Use pipenv to install local dependencies. `pipenv` has become the [recommended
   package to use by python.org for dependency
   management](https://packaging.python.org/tutorials/managing-dependencies/)

### Default - Docker/Podman Container

Currently all builds are generated using the
[ood-documentation-build](https://github.com/OSC/ood-documentation-build/)
container image. To use the helper methods provided below, you will have to
have either ruby or python installed on your machine. All helper commands 
should be run from the root of the repository.

#### Ruby
The ruby helpers use `rake`, so you'll need to have `ruby` installed on your
system as well as the `rake` gem. Then you can run

```bash
rake build
```
to generate HTML from the local source files,

```bash
rake open
```
to open the HTML with your browser, and

```bash
rake spellcheck
```

to check spelling. Note that spellchecking is automatically executed on all pull requests.

And you can run `rake` without arguments to see each of these tasks in the CLI.

#### Python
The python helpers use the `tasks.py` file, and only require `python` to be installed.

The python commands have the same functions as the ruby ones above, but use the following syntax

```bash
python ./tasks.py build
```

```bash
python ./tasks.py open
```

```bash
python ./tasks.py spellcheck
```

And you can list these commands in the CLI with
```bash
python tasks.py --help
```

### Make with Pip/python

The default way to build these files are to use the container (instructions above)
that has all the dependencies sorted out.  If however you'd rather install all
the dependencies through python's `pip` (or a different python package manager
like `conda`, `venv` and so on) you can use the `requirements.txt` found in the
[ood-documentation-build](https://github.com/OSC/ood-documentation-build/)
repository.

However this may be flaky and/or brittle way to manage this which is why using
a container is the default mechanism for building these html files.

```bash
make html
```

## Contributing

Bug reports and pull requests are welcome on GitHub at
https://github.com/OSC/ood-documentation.

## License

* Documentation, website content, and logo is licensed under
  [CC-BY-4.0](https://creativecommons.org/licenses/by/4.0/)
* Code is licensed under MIT (see LICENSE.txt)
