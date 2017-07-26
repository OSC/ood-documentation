# OOD Documentation

Go to https://osc.github.io/ood-documentation/master/

Or select your version:

- [Development](https://osc.github.io/ood-documentation/develop/)
- [Latest Stable](https://osc.github.io/ood-documentation/master/)

## Development

Currently all builds are generated using the
[docker-sphinx](https://github.com/nickjer/docker-sphinx) Docker image. They
are built using the following command from the root of this repo:

```bash
docker run --rm -i -t -v "${PWD}:/doc" -u "$(id -u):$(id -g)" nickjer/docker-sphinx make html
```

## Contributing

Bug reports and pull requests are welcome on GitHub at
https://github.com/OSC/ood-documentation.

## License

The gem is available as open source under the terms of the [MIT
License](http://opensource.org/licenses/MIT).
