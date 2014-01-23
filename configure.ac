dnl -*-Autoconf-*-
dnl configure.ac for xtalgrowth
dnl Time-stamp: <2014-01-23 18:55:01 takeshi>
dnl Author: Takeshi NISHIMATSU

## Initialize.
AC_PREREQ(2.61)
AC_INIT([xtalgrowth by Takeshi NISHIMATSU],[0.7.0],[t-nissie{at}imr.tohoku.ac.jp],[xtalgrowth])
AC_CONFIG_SRCDIR(src/xtalgrowth.c)
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])

## Check for install
AC_PROG_INSTALL

## Check for C compiler
CFLAGS_PRESERVE=$CFLAGS
AC_PROG_CC([gcc cl cc])
CFLAGS=$CFLAGS_PRESERVE
test -n  "$CFLAGS" || CFLAGS="-g -Wall -O3"
test -n "$LDFLAGS" || LDFLAGS="-L/usr/local/lib -L/usr/X11R6/lib"


## Check for Objective-C compiler
# Here, add "if OS==Darwin" etc.
# For GNUstep, see http://blog.lyxite.com/2008/01/compile-objective-c-programs-using-gcc.html .
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

## Finalize.
AC_SUBST(CPPFLAGS)
AC_SUBST(OBJCFLAGS)
AC_SUBST(OBJCFRAMEWORKS)
AC_CONFIG_FILES([Makefile
             src/Makefile])
AC_OUTPUT
