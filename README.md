xtalgrowth
==========
xtalgrowth is an X application which can simulate crystal
growth of 2-dimensional hard spheres.

The latest .tar.gz package (xtalgrowth-X.Y.Z.tar.gz) can be downloaded from
https://sourceforge.net/projects/loto/files/xtalgrowth/ .

<!-- xtalgrowth is under continuous integration at Travis CI: [![Build Status](https://travis-ci.com/t-nissie/xtalgrowth.svg?branch=master)](https://travis-ci.com/github/t-nissie/xtalgrowth) -->

xtalgrowth is under continuous integration at GitHub Actions:
[![CI](https://github.com/t-nissie/xtalgrowth/workflows/CI/badge.svg)](https://github.com/t-nissie/xtalgrowth/actions)

## Please read webpages:
https://t-nissie.github.io/xtalgrowth/ or
https://loto.sourceforge.net/xtalgrowth/

index.en.html, index.es.html and index.ja.html are also included in the source package
and will be installed into PREFIX/share/doc/xtalgrowth/.

You can also ask DeepWiki: [![Ask DeepWiki](https://deepwiki.com/badge.svg)](https://deepwiki.com/t-nissie/xtalgrowth)

## Compilation and installation
Requirements are

* C compiler (gcc)
* X11 libraries and their include files (`apt install libx11-dev` or `yum install libX11-devel`)
* popt libraries and their include files (`apt install libpopt-dev` or `yum install popt-devel` or see https://ftp.rpm.org/popt/ )

If you have all of them, You can generate src/xtalgrowth with

    $ tar xf xtalgrowth-X.Y.Z.tar.gz
    $ cd xtalgrowth-X.Y.Z
    $ ./configure --help
    $ ./configure
    $ make -j9
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

For macOS into which XQuartz was installed and popt was installed via HomeBrew, try

    $ ./configure CPPFLAGS='-I/opt/X11/include -I/opt/homebrew/include' LDFLAGS='-L/opt/X11/lib -L/opt/homebrew/lib'

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


## Development of WebAssembly（WASM) version of xtalgrowth
WebAssembly（WASM) version of xtalgrowth is under development now!
Here, I explain step-by-step procedure.

### Setup Emscripten SDK
Emscripten SDK: https://github.com/emscripten-core/emsdk

```shell
clone https://github.com/emscripten-core/emsdk.git
cd emsdk/
./emsdk install latest
./emsdk activate latest
```

Add `source SOMEWHERE/wasm/emsdk/emsdk_env.sh` to `$HOME/.profile`.

### Test the "Hello World" example in wasm-canvas
wasm-canvas: https://github.com/alextyner/wasm-canvas

Prepare Makefile, hello.c and template.html in hello/ directory.

```Makefile
#-*-Makefile-*- for the "Hello World" example in https://github.com/alextyner/wasm-canvas
##
CC=emcc
index.html: template.html hello.o canvas.o
	emcc --shell-file $^ -o $@
clean:
	rm -f canvas.o hello.o index.html index.js index.wasm
```

Make symlinks of canvas.c and canvas.h into the hello/ directory.
After you `make index.html`, you need to test it with `emrun` locally.

    git clone https://github.com/alextyner/wasm-canvas.git
    mkdir hello
    cd hello          # Put Makefile, hello.c and template.html in this hello/ directory.
    ln -s ../wasm-canvas/src/canvas.c .
    ln -s ../wasm-canvas/src/canvas.h .
    make  index.html
    emrun index.html

### My wasm-canvas examples
* Draw an arc:        https://gist.github.com/t-nissie/8fb6c7b521227634cbcfed8f72f6c7d7
* Animation:          https://gist.github.com/t-nissie/0ff20f2de652b16acc72ef4b01893998
* Get URL parameters: https://gist.github.com/t-nissie/1bc52a3cbb64475860989feff201ab0f

### Emacs setting for wasm-canvas development
See the output of `source SOMEWHERE/wasm/emsdk/emsdk_env.sh`.

```elisp
(setenv "PATH"
	(concat "SOMEWHERE/wasm/emsdk:SOMEWHERE/wasm/emsdk/upstream/emscripten:SOMEWHERE/wasm/emsdk/node/22.16.0_64bit/bin" (getenv "PATH")))
(setenv "EMSDK" "SOMEWHERE/wasm/emsdk")
(setenv "EMSDK_NODE" "SOMEWHERE/wasm/emsdk/node/22.16.0_64bit/bin/node")
(setenv "EMSDK_PYTHON" "SOMEWHERE/wasm/emsdk/python/3.13.3_64bit/bin/python3")
(setenv "SSL_CERT_FILE" "SOMEWHERE/wasm/emsdk/python/3.13.3_64bit/lib/python3.13/site-packages/certifi/cacert.pem")
```

### How to compile Emscripten/WebAssembly/wasm-canvas version of xtalgrowth
To test generated `xtalgrowth.html` locally, you need to `emrun` it.

    cd src/
    make -f WASMMakefile
    emrun xtalgrowth.html

See also https://github.com/t-nissie/xtalgrowth/blob/master/.github/workflows/pages.yml
for the details of deployment of xtalgrowth.html.

### Examples of URL parameters for xtalgrowth.html
You can execute xtalgrowth.html as:

* https://t-nissie.github.io/xtalgrowth/xtalgrowth.html
* https://t-nissie.github.io/xtalgrowth/xtalgrowth.html?guest=Dr%2e%20Takeshi%20Nishimatsu&diameter=0.0495&velocity=0.0008&criterion=3
* https://t-nissie.github.io/xtalgrowth/xtalgrowth.html?guest=Miss%20Crystal%20Growth&diameter=0.024&velocity=0.001&criterion=1
