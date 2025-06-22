dnl -*-Autoconf-*-
dnl configure.ac for xtalgrowth
dnl Time-stamp: <2025-06-22 23:50:10 takeshi>
dnl Author: Takeshi NISHIMATSU

## Initialize.
AC_PREREQ(2.61)
AC_INIT([xtalgrowth by Takeshi NISHIMATSU],[1.1.3],[t_nissie{at}yahoo.co.jp],[xtalgrowth])
AC_CONFIG_SRCDIR(src/xtalgrowth.c)
AM_INIT_AUTOMAKE([foreign std-options])
AC_CONFIG_HEADERS([config.h])

## Check for install
AC_PROG_INSTALL

## Check for C compiler
CFLAGS_PRESERVE=$CFLAGS
AC_PROG_CC([gcc cl cc])
CFLAGS=$CFLAGS_PRESERVE
test -n  "$CFLAGS" || CFLAGS="-g -Wall -Wno-parentheses -O3"
test -n "$LDFLAGS" || LDFLAGS="-L/usr/local/lib -L/usr/X11R6/lib"


## Check for Objective-C compiler
dnl Here, add "if OS==Darwin" etc.
dnl For GNUstep, see http://blog.lyxite.com/2008/01/compile-objective-c-programs-using-gcc.html ,
dnl http://stackoverflow.com/questions/11358000/how-to-compile-objective-c-code-in-ubuntu and
dnl `gnustep-config --help`.
OBJCFLAGS_PRESERVE=$OBJCFLAGS
AC_PROG_OBJC([gcc objcc objc])
OBJCFLAGS=$OBJCFLAGS_PRESERVE
test -n      "$OBJCFLAGS" || OBJCFLAGS="-g -O3 -Wall"
test -n "$OBJCFRAMEWORKS" || OBJCFRAMEWORKS="-framework Foundation -framework Cocoa -framework AppKit"

## Checks for some libraries
AC_CHECK_LIB(X11, main)
AC_CHECK_LIB(popt, poptGetContext)

## Checks for some headers
AC_CHECK_HEADERS([popt.h])
AC_CHECK_HEADERS([X11/Xlib.h],,[AC_MSG_ERROR([You need header files for X11 libraries. See config.log.])])

## Finalize.
AC_SUBST(CPPFLAGS)
AC_SUBST(OBJCFLAGS)
AC_SUBST(OBJCFRAMEWORKS)
AC_CONFIG_FILES([Makefile
             xtalgrowth.1
             meson.build
             src/meson.build
             src/CMakeLists.txt
             src/Makefile])
AC_OUTPUT
