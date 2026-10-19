(app-development-tutorials-interactive-apps-add-rstudio-deploy)=

# Deploy RStudio App

After you have confirmed you are happy with all of your app changes you can
deploy it as a System App.

:::{warning}
The following steps **MUST** be done from the OnDemand host and not another
machine.
:::

1. Go to your OnDemand sandbox directory:

   ```sh
   cd ~/ondemand/dev
   ```

2. Copy the app to the system deployment location as **root**:

   ```sh
   sudo cp -r bc_example_rstudio /var/www/ood/apps/sys/.
   ```

3. In your browser navigate to the OnDemand URL and confirm you see the new app
   in the *Interactive Apps* drop-down on the dashboard.

   > <https://ondemand.my_center.edu/>
