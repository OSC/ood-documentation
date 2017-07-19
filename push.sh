#!/usr/bin/env bash

GITHUB_ORG="nickjer"
GITHUB_REPO="ood-documentation"
EMAIL="jeremywnicklas@gmail.com"

# Clone the gh-pages branch outside of the current repo and cd into it
cd ..
git clone -b gh-pages "https://${GITHUB_TOKEN}@github.com/${GITHUB_ORG}/${GITHUB_REPO}.git" gh-pages
cd gh-pages

# Update git configuration
git config user.name "Travis Builder"
git config uesr.email "${EMAIL}"

# Copy in the built html
cp -R ../${GITHUB_REPO}/build/html/. ./

# Add and commit changes
git add -A .
git commit -m '[ci skip] Autodoc commit.'
# -q is very important, otherwise you leak your GITHUB_TOKEN
git push -q origin gh-pages
