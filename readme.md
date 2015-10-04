CeeGee
======

Small C project that I'm working on to teach myself the language.
This is designed for MS-DOS, meaning you need DJGPP to compile it. It uses
the VGA adapter.

Clone *argparse* and *Allegro* in a subdirectory named `vendor`. The
installation will be automated soon.


Sources
--------

This couldn't have been built without the excellent information available
online on C programming in general and MSDOS programming in particular.

* [DJGPP VGA access](http://www.delorie.com/djgpp/doc/brennan/brennan_access_vga.html)
* [Fast access to absolute addresses](http://www.delorie.com/djgpp/v2faq/faq18_6.html)
* [Allegro forums](https://www.allegro.cc/forums/index)
* [Allegro 4.4.2 docs](http://liballeg.org/stabledocs/en/allegro.html)
* [How do I use extern to share variables between source files in C? (Stack Overflow)](http://stackoverflow.com/questions/1433204/how-do-i-use-extern-to-share-variables-between-source-files-in-c)


Dependencies
------------

* [argparse](https://github.com/Cofyc/argparse) (4.4)
* [Allegro](http://liballeg.org/)
* [xorshift](https://github.com/WebDrake/xorshift)
