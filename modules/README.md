Modules for MK2

## Directory Structure

```
modules/
    <module name>/
        src/
        include/
        docs/
        bin/
        test/
        module.mk
        Makefile
        README.md
    README.md
```

#### <module name>

Name of module, ie. navigation, vision, etc.

#### src/

Source files, ie. cpp files

#### include/

Header files, ie. hpp files

#### docs/

Documentation and notes

#### bin/

Compiled executable binaries

#### test/

Testing code

#### module.mk

Makefile to be included when compiling the core. Example can be found in sample module

#### Makefile

Makefile to compile the module for testing. Example can be found in sample module

#### README.md

README
