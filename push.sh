#!/usr/bin/env bash

GITHUB_ORG="OSC"
GITHUB_REPO="ood-documentation"
NAME="Travis Builder"
EMAIL="oscwiag@gmail.com"

if [[ ${TRAVIS_BRANCH} == "master" ]] || \
   [[ ${TRAVIS_BRANCH} == "develop" ]] || \
   [[ ${TRAVIS_BRANCH} =~ ^release-[0-9]+\.[0-9]+$ ]]
then
  # Update git configuration
  git config user.name "${NAME}"
  git config user.email "${EMAIL}"

  # Clone the gh-pages branch outside of the current repo and cd into it
  cd ..
  git clone -b gh-pages "https://${GITHUB_TOKEN}@github.com/${GITHUB_ORG}/${GITHUB_REPO}.git" gh-pages
  cd gh-pages

  # Clean up old build and copy in the new built html
  rm -fr "${TRAVIS_BRANCH}"
  cp -R ../${GITHUB_REPO}/build/html "${TRAVIS_BRANCH}"

  # Add and commit changes
  git add -A .
  git commit -m "[ci skip] Autodoc commit for ${TRAVIS_COMMIT}."
  # -q is very important, otherwise you leak your GITHUB_TOKEN
  git push -q -f origin gh-pages
else
  echo "Not publishing documentation for this branch ${TRAVIS_BRANCH}"
fi
