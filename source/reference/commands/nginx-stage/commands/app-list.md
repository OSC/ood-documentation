(nginx-stage-app-list)=

# `nginx_stage app_list`

This command lists all the deployed web application NGINX
configuration files.

```sh
sudo nginx_stage app_list [OPTIONS]
```

```{eval-rst}
.. program:: nginx_stage app_list
```

## Examples

To list all the deployed app configurations:

```sh
sudo nginx_stage app_list
```

This will return the paths to all the deployed app configurations.
