CeeGee
======

Small C project that I'm working on to teach myself the language.
This is designed for MS-DOS, meaning you need DJGPP to compile it. It uses
the VGA adapter.

This project is still in the very early stages and doesn't work yet!


Installation
------------

To download vendor-specific code, run the `vendor.sh` script. This will
clone several Git repositories into the `vendor/` directory, which it will
create if it doesn't exist.

### Setting up DJGPP

To compile the engine, you'll need to have DJGPP set up to be able to
compile for MS-DOS. You can either get a pre-built release or build
the whole thing from source—follow the instructions on
[andrewwutw/build-djgpp](https://github.com/andrewwutw/build-djgpp) to get
a working compiler.

Set an environment variable `$DJGPP_CC` to the path of your DJGPP GCC binary.
For example, you could add the following to your `~/.bashrc` file:

    export DJGPP_CC=/usr/local/djgpp/bin/i586-pc-msdosdjgpp-gcc


Dependencies
------------

* [argparse](https://github.com/Cofyc/argparse)
* [xorshift](https://github.com/msikma/xorshift)
