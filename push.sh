#!/usr/bin/env bash

GITHUB_ORG="OSC"
GITHUB_OFFICIAL_REPO="ood-documentation"
GITHUB_TEST_REPO="ood-documentation-test"
NAME="Travis Builder"
EMAIL="oscwiag@gmail.com"

# Update git configuration
git config user.name "${NAME}"
git config user.email "${EMAIL}"

# Publish built documentation to a given repo
function publish () {
  local repo=${1}
  local workdir="$(mktemp -d)"

  # Clone the gh-pages branch outside of the current repo and cd into it
  cd "${workdir}"
  git clone -b gh-pages "https://${GITHUB_TOKEN}@github.com/${GITHUB_ORG}/${repo}.git" gh-pages
  cd gh-pages

  # Clean up old build and copy in the new built html
  rm -fr "${TRAVIS_BRANCH}"
  cp -R "${TRAVIS_BUILD_DIR}/${GITHUB_REPO}/build/html" "${TRAVIS_BRANCH}"

  # Add and commit changes
  git add -A .
  git commit -m "[ci skip] Autodoc commit for ${TRAVIS_COMMIT}."
  # -q is very important, otherwise you leak your GITHUB_TOKEN
  git push -q -f origin gh-pages
}

# Do not publish if it is a pull request update, but publish if it is a branch
# update (this stops it from publishing twice, and limits it to developers who
# have write access to the repo).

if [[ ${TRAVIS_PULL_REQUEST} == "false" ]]; then
  # Publish documentation for all branches to test repo
  echo "Publishing test documentation for the branch: ${TRAVIS_BRANCH}"
  publish ${GITHUB_TEST_REPO}

  # Publish official documentation for blessed branches
  if [[ \
      ( ${TRAVIS_BRANCH} == "master"  || \
        ${TRAVIS_BRANCH} == "develop" || \
        ${TRAVIS_BRANCH} =~ ^release-[0-9]+\.[0-9]+$
      ) \
    ]]; then
    echo "Publishing official documentation for the branch: ${TRAVIS_BRANCH}"
    publish ${GITHUB_OFFICIAL_REPO}
  else
    echo "Not publishing official documentation for commit: ${TRAVIS_COMMIT}."
  fi
fi
