xtalgrowth
==========
xtalgrowth is an X application which can simulate crystal
growth of 2-dimensional hard spheres.

The latest .tar.gz package (xtalgrowth-X.Y.Z.tar.gz) can be downloaded from
http://sourceforge.net/projects/loto/files/xtalgrowth/ .

<!-- xtalgrowth is under continuous integration at Travis CI: [![Build Status](https://travis-ci.com/t-nissie/xtalgrowth.svg?branch=master)](https://travis-ci.com/github/t-nissie/xtalgrowth) -->

xtalgrowth is under continuous integration at GitHub Actions:
[![CI](https://github.com/t-nissie/xtalgrowth/workflows/CI/badge.svg)](https://github.com/t-nissie/xtalgrowth/actions)

## Please read webpages:

* http://loto.sourceforge.net/xtalgrowth/index.en.html (English)
* http://loto.sourceforge.net/xtalgrowth/index.es.html (Spanish)
* http://loto.sourceforge.net/xtalgrowth/index.ja.html (Japanese)

index.en.html, index.es.html and index.ja.html are also included in the source package.

## Compilation and installation
Requirements are

* C compiler (gcc)
* X11 libraries and their include files (`apt install libx11-dev` or `yum install libX11-devel`)
* popt libraries and their include files (`apt install libpopt-dev` or `yum install popt-devel` or see http://ftp.rpm.org/popt/ )

If you have all of them, You can generate src/xtalgrowth with

    $ tar xf xtalgrowth-X.Y.Z.tar.gz
    $ cd xtalgrowth-X.Y.Z
    $ ./configure --help
    $ ./configure
    $ make -j3
    $ make check

Test the executable

    $ cd src
    $ ./xtalgrowth --help
    $ ./xtalgrowth > aaa.ps
    $ evince aaa.ps   # Or use other previewers.
    $ cd ..

If you want to install /usr/local/bin/xtalgrowth,

    $ sudo make install
    $ make installcheck
    $ man xtalgrowth

For macOS into which XQuartz was installed and popt was installed via MacPorsts, use

    $ ./configure CPPFLAGS='-I/opt/X11/include -I/opt/local/include' LDFLAGS='-L/opt/X11/lib -L/opt/local/lib'

to set CPPFLAGS and LDFLAGS.

## Compilation with cmake
You can compile xtalgrowth with cmake.

    $ tar xf xtalgrowth-X.Y.Z.tar.gz
    $ mkdir xtalgrowth-X.Y.Z/build
    $ cd $_
    $ cmake -G Ninja ..
    $ ninja
    $ ninja test
    $ sudo ninja install

If you want to install xtalgrowth into other than /usr/local,

    $ cmake -G Ninja -DCMAKE_INSTALL_PREFIX=/somewhere/you/want ..

## Install/uninstall xtalgrowth with Meson Build and Ninja
From version 1.1.3, you can compile xtalgrowth with Meson Build and Ninja.

    $ tar xf xtalgrowth-X.Y.Z.tar.gz
    $ cd xtalgrowth-X.Y.Z
    $ meson setup --help
    $ meson setup mesonbuilddir/ --prefix=/somewhere/you/want --buildtype=debugoptimized
    $ cd mesonbuilddir/
    $ ninja --help
    $ ninja --verbose
    $ ninja test
    $ sudo ninja install
    $ sudo ninja uninstall


## Git repository
The latest source code of xtalgrowth is in https://github.com/t-nissie/xtalgrowth .
You can clone it with

    $ git clone https://github.com/t-nissie/xtalgrowth.git

## Development of xtalgrowth
Developers need Autotools.

* autoconf (version 2.61 or higher)
* automake (version 1.16.5 or higher)

Developers can:

    $ git clone https://github.com/t-nissie/xtalgrowth.git
    $ cd xtalgrowth
    $ autoreconf -v
    $ automake --add-missing
    $ autoreconf -v            ###*###
    $ ./configure
    $ make -j9                 # Do development.
    $ make check               # Do some tests.
    $ make distclean           # Clean up Makefile, etc.
    $ ./configure
    $ make distcheck           # Check and make a distribution package, xtalgrowth-X.Y.Z.tar.gz.
                               # Give options in DISTCHECK_CONFIGURE_FLAGS.
    
    $ make clean
    $ cmake -G Ninja .         # You can also use CMake.
    $ cmake -LA .
    $ ninja
    $ ninja test

Go back to `###*###`, when you edit configure.ac, Makefile.am, src/Makefile.am, etc.
`make Makefile` may be enough sometimes.
Note that `src/CMakeLists.txt` is made from `src/CMakeLists.txt.in` by `configure`.

### Development with macOS, Homebrew and Meson Build
Run the setup command as `meson setup mesonbuilddir [options]`.
Just `meson mesonbuilddir [options]` without `setup` is ambiguous and deprecated.

    $ ./configure CPPFLAGS='-I/opt/X11/include -I/opt/homebrew/include' LDFLAGS='-L/opt/X11/lib -L/opt/homebrew/lib'
    $ rm -rf build/ && meson setup build/ && cd build/ && ninja && ninja test && src/xtalgrowth --help && cd ..
