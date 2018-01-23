#!/bin/sh

doxygen Doxyfile 

rm -r docs/
mv html/ docs/

touch docs/.nojekyll