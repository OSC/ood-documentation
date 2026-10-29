(app-development-tutorials-dashboard-apps-shell-app)=

# Developing the Shell App

The `shell` app is significantly different from the dashboard app. It is purely a `node.js` app.
This means that we only need to use `npm` to build and do development work.

## Create a Development Shell

1. `clone` the OOD repository into: `cd ~/ondemand/misc` then `git clone git@github.com:OSC/ondemand.git`
2. Work out of the `dev` directory/space: `cd ~/ondemand/dev/`.
3. Symlink to the `shell` app in the cloned repository: `ln -s ../misc/ondemand/apps/dashboard/shell/ shell`
4. Make a branch and to begin word on your development dashboard: `git checkout -b dev_work`
5. Rebuild the `shell` app: `bin/setup`.
6. Navigate to the Sandbox and launch your development `shell` app to use the `dev_work` branch.

Notice the `url` for this app. No longer do you see `*/sys/shell` but instead `*/dev/shell`.

### Build Old Version of Shell

1. pull down ondemand in `~/ondemand/misc`
2. then list versions with `git tags`
3. run `git checkout <version>`
4. now make a branch with your changes and use `bin/setup` to rebuild if needed

Then for the **shell app** from a login terminal run:

1. `cd dev`
2. `ln -s ../misc/ondemand/apps/dashboard/shell/ shell-18`

And then step into that symlinked directory and run:
#. `bin/setup`

If you go start this app from sandbox you'll notice a different URL than before,
showing you are in a development shell: `pun/dev/shell-1.8`

### Issues and Errors

Ensure you are using the correct version of Node when you go to build using `nvm` if possible. Sometimes
this can be set automatically for you in your `.bashrc` so just ensure you are on the version you should
be when you run `bin/setup`.

## Develop the Shell

At this point we have a working development `shell` and can start to make changes to this code and issue rebuilds
for `npm` with `bin/setup` when needed.
