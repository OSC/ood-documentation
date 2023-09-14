# OOD Documentation

[![Build Status](https://travis-ci.org/OSC/ood-documentation.svg?branch=develop)](https://travis-ci.org/OSC/ood-documentation)
[![GitHub License](https://img.shields.io/badge/license-MIT-green.svg)](https://opensource.org/licenses/MIT)
[![Documentation License](https://img.shields.io/badge/license-CC%20BY%204.0-lightgrey.svg)](https://creativecommons.org/licenses/by/4.0)

- Website: http://openondemand.org/
- Documentation: https://osc.github.io/ood-documentation/master/
- Main code repo: https://github.com/OSC/ondemand
- Core library repo: https://github.com/OSC/ood_core
- Original repo with JOSS publication: https://github.com/OSC/Open-OnDemand

## Usage

Go to https://osc.github.io/ood-documentation/master/ to see the latest published release version.

Or select your version:

- [Development](https://osc.github.io/ood-documentation/develop/)
- [Latest Stable](https://osc.github.io/ood-documentation/master/)
- [1.6](https://osc.github.io/ood-documentation/release-1.6/)
- [1.5](https://osc.github.io/ood-documentation/release-1.5/)
- [1.4](https://osc.github.io/ood-documentation/release-1.4/)
- [1.3](https://osc.github.io/ood-documentation/release-1.3/)
- [1.2](https://osc.github.io/ood-documentation/release-1.2/)
- [1.1](https://osc.github.io/ood-documentation/release-1.1/)
- [1.0](https://osc.github.io/ood-documentation/release-1.0/)

## Development

Open pull requests to the develop branch, which is the main branch of this repo. This repo uses the [gitflow branching model](https://nvie.com/posts/a-successful-git-branching-model/).

There are two ways to build the documentation.

1. Use the Docker image that is used to build them in production using Travis.
2. Use pipenv to install local dependencies. `pipenv` has become the [recommended
   package to use by python.org for dependency
   management](https://packaging.python.org/tutorials/managing-dependencies/)

### Default - Docker/Podman

Currently all builds are generated using the
[ood-documentation-build](https://github.com/OSC/ood-documentation-build/)
container image. They are built using the following command from the root of this repo:

Note that because we're using `rake`, you'll need to have `ruby` installed on your
system as well as the `rake` gem.

```bash
rake build
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
