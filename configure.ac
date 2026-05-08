dnl configure.ac for xtalgrowth
dnl Author: Takeshi NISHIMATSU

## Initialize.
AC_PREREQ(2.61)
AC_INIT([xtalgrowth by Takeshi NISHIMATSU],[1.1.4],[t_nissie{at}yahoo.co.jp],[xtalgrowth])
AC_CONFIG_SRCDIR(src/xtalgrowth.c)
AM_INIT_AUTOMAKE([foreign std-options])
AC_CONFIG_HEADERS([config.h])

## Check for install
AC_PROG_INSTALL

## Check for C compiler
CFLAGS_PRESERVE=$CFLAGS
AC_PROG_CC([gcc cc])
CFLAGS=$CFLAGS_PRESERVE
test -n  "$CFLAGS" || CFLAGS="-g -Wall -O3"
test -n "$LDFLAGS" || LDFLAGS="-L/usr/local/lib -L/usr/X11R6/lib"

## Checks for some libraries
AC_CHECK_LIB(X11, main)
AC_CHECK_LIB(popt, poptGetContext)

## Checks for some headers
AC_CHECK_HEADERS([popt.h])
AC_CHECK_HEADERS([X11/Xlib.h],,[AC_MSG_ERROR([You need header files for X11 libraries. See config.log.])])

## Finalize.
AC_SUBST(CPPFLAGS)
AC_CONFIG_FILES([Makefile
             xtalgrowth.1
             meson.build
             src/meson.build
             src/CMakeLists.txt
             src/Makefile])
AC_OUTPUT
