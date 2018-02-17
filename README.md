xtalgrowth
==========
xtalgrowth is an X application which simulate crystal
growth of 2-dimensional hard spheres.

## Please read webpages:

* http://loto.sourceforge.net/xtalgrowth/index.en.html (English)
* http://loto.sourceforge.net/xtalgrowth/index.es.html (Spanish)
* http://loto.sourceforge.net/xtalgrowth/index.ja.html (Japanese)

## Compilation and installation
Requirements are

* C compiler (gcc)
* X11 libraries and their include files (apt-get install libx11-dev or yum install libX11-devel)
* popt libraries and their include files (apt-get install libpopt-dev or yum install popt-devel or see http://rpm5.org/files/popt/ )

If you have all of them, You can generate src/xtalgrowth with

    $ tar zxf xtalgrowth-X.Y.Z.tar.gz
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

In some 64 bit systems, you may get link errors like

    /usr/bin/ld: skipping incompatible /usr/X11R6/lib/libX11.so when searching for -lX11

In this case, give some LDFLAGS in the configure step

    $ ./configure LDFLAGS="-L/usr/local/lib -L/usr/X11R6/lib64"

For macOS into which XQuartz was installed and popt was installed via MacPorsts, use

    $ ./configure CPPFLAGS='-I/opt/X11/include -I/opt/local/include' LDFLAGS='-L/opt/X11/lib -L/opt/local/lib'

to set CPPFLAGS and LDFLAGS.

## Compilation with cmake
You can compile xtalgrowth with cmake, too.

    $ tar zxf xtalgrowth-X.Y.Z.tar.gz
    $ mkdir xtalgrowth-X.Y.Z/build
    $ cd $_
    $ cmake -G Ninja ..
    $ ninja
    $ sudo ninja install
