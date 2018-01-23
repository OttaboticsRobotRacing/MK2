#!/bin/sh

doxygen Doxyfile 

rm -r docs/
mv html/ docs/