# OOD Documentation

Go to https://osc.github.io/ood-documentation/master/

Or select your version:

- [Development](https://osc.github.io/ood-documentation/develop/)
- [Latest Stable](https://osc.github.io/ood-documentation/master/)
- [1.0](https://osc.github.io/ood-documentation/release-1.0/)

## Development

Currently all builds are generated using the
[docker-sphinx](https://github.com/OSC/docker-sphinx/) Docker image. They are
built using the following command from the root of this repo:

```bash
docker run --rm -i -t -v "${PWD}:/doc" -u "$(id -u):$(id -g)" ohiosupercomputer/docker-sphinx make html
```

If you don't want to use Docker, you can also use pipenv. Directions on setting
up your environment assume Homebrew is installed and python 2.7 is installed.
Take the following steps:

```bash
pip install -g pipenv
brew install plantuml
brew install graphviz

# then in the documentation root directory:
WORKDIR=/doc PIPENV_VENV_IN_PROJECT=1 pipenv install
```

When building the html to test, run this command:

```bash
WORKDIR=/doc PIPENV_VENV_IN_PROJECT=1 pipenv run make html
```

## Contributing

Bug reports and pull requests are welcome on GitHub at
https://github.com/OSC/ood-documentation.

## License

The gem is available as open source under the terms of the [MIT
License](http://opensource.org/licenses/MIT).
