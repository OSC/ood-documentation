#!/usr/bin/env bash

GITHUB_ORG="OSC"
NAME="oscwiag"
EMAIL="oscwiag@gmail.com"

# Update git configuration
git config --global user.name "${NAME}"
git config --global user.email "${EMAIL}"

repo=${1}
workdir="$(mktemp -d)"
builddir="${PWD}"

# Clone the gh-pages branch outside of the current repo and cd into it
cd "${workdir}"
git clone -b gh-pages "https://${GITHUB_TOKEN}@github.com/${GITHUB_ORG}/${repo}.git" gh-pages
cd gh-pages

REF=${GITHUB_HEAD_REF:-${GITHUB_REF#refs/heads/}}

# Clean up old build and copy in the new built html
rm -fr "${REF}"
cp -R "${builddir}/build/html" "${REF}"

# Add and commit changes
git add -A .
git commit -m "[ci skip] Autodoc commit for ${GITHUB_SHA}."
# -q is very important, otherwise you leak your GITHUB_TOKEN
git push -q -f origin gh-pages


