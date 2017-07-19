#!/usr/bin/env bash

GITHUB_ORG="nickjer"
GITHUB_REPO="ood-documentation"
EMAIL="jeremywnicklas@gmail.com"

declare -A PUBLISH_BRANCHES=(
 [master]=1 [v1.0]=1 [v2.1]=1
)

if [[ -n "${PUBLISH_BRANCHES[${TRAVIS_BRANCH}]}" ]] ; then

  # Update git configuration
  git config user.name "Travis Builder"
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
  git push -q --force origin gh-pages

fi
