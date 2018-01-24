#!/bin/bash

# checkout docs files from the develop branch
git checkout develop -- docs
# move the contents of docs/ into current directory
cp -r docs/* .
# remove docs/
rm -r docs/

touch .nojekyll