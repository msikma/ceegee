CeeGee
======

This is a small open source C game designed for MS-DOS. It's made in mid-90s
PC gaming style, and runs at full speed on a 486 or higher (or in
[DOSBox](http://www.dosbox.com/)).

This project is still in the very early stages and doesn't work yet! Since this
game is designed to run on MS-DOS, you'll need DJGPP to compile it.
Instructions are below.


Builds
------

The [latest builds page](http://ceegee.whahay.com/) is updated as soon
as the `master` branch is changed. You can also follow
[@CeeGeeBuilds](https://twitter.com/CeeGeeBuilds) on Twitter if you
want to know about new builds as soon as they're available.


Installation
------------

### Setting up DJGPP

To compile the game, you'll need to have DJGPP set up to be able to
compile for MS-DOS. You can either get a pre-built release or build
the whole thing from source—follow the instructions on
[andrewwutw/build-djgpp](https://github.com/andrewwutw/build-djgpp) to get
a working compiler. If you follow the instructions in the link, your
compiler should also work out of the box for building the Allegro library.

Set an environment variable `$DJGPP_CC` to the path of your DJGPP GCC binary.
For example, you could add the following to your `~/.bashrc` file:

    export DJGPP_CC=/usr/local/djgpp/bin/i586-pc-msdosdjgpp-gcc

### Vendor code

Vendor code is included as Git submodules. Clone this repo with
`git clone --recursive` to make sure you get them.

Only the Allegro library needs to be compiled separately. It's a fork
from the 4.2.2 version with some tweaks to make it compile on modern
cross-compilers. See the [allegro-4.2.2-xc](https://github.com/msikma/allegro-4.2.2-xc)
page for instructions.

All other vendor code is automatically compiled when you run `make`.

### Allegro datafile utility

The `dat` utility from Allegro 4 is required to process graphical assets.
We can't use the one from `allegro-4.2.2-xc` because that one is designed
to compile for MS-DOS only—the `dat` utility must be usable by your system
*natively*.

Windows users can likely use [a binary](https://www.allegro.cc/files/?v=4.4)
from the Allegro website. For Mac OS X, I've made a build that includes
the `dat` utility, [available on this repository.](https://github.com/msikma/liballeg.4.4.2-osx)
Just clone it and put its `tools` directory in your path, that should be
sufficient. Linux users can probably get the utility by installing Allegro
using their package manager, e.g. [liballegro4-dev](https://packages.debian.org/jessie/liballegro4-dev)
for Debian.

### Compiling the project

After Allegro has been compiled, it should be as simple as running `make`.
This creates a distribution in the `dist/` directory. You can run this
using [DOSBox](https://www.dosbox.com/) for testing. To enable debugging
features, run `make DEBUG=1`.

For easy distribution, run `make dist` to create a zip file containing
the latest build. It will be saved to the `dist/` directory.


Dependencies
------------

* [allegro-4.2.2-xc](https://github.com/msikma/allegro-4.2.2-xc)
* [xorshift](https://github.com/msikma/xorshift)


Copyright
---------

Copyright © 2015-2016, [Michiel Sikma](mailto:michiel@sikma.org)

MIT License
