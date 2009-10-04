dnl -*-Autoconf-*-
dnl configure.ac for xtalgrowth
dnl Time-stamp: <2009-10-04 19:59:04 takeshi>
dnl Author: Takeshi NISHIMATSU

## Initialize.
AC_PREREQ(2.61)
AC_INIT([xtalgrowth by Takeshi NISHIMATSU],[0.2.0],[t-nissie{at}imr.tohoku.ac.jp],[xtalgrowth])
AC_CONFIG_SRCDIR(src/xtalgrowth.c)
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])

## Some OS does not see /usr/local/lib.
LDFLAGS="$LDFLAGS -L/usr/local/lib -L/usr/X11R6/lib"

## Checks for some libraries
AC_CHECK_LIB(X11, main)
AC_CHECK_LIB(popt, poptGetContext)

## Checks for some headers
AC_CHECK_HEADERS([popt.h])

## Checks for some programs.
AC_PROG_INSTALL

## Finalize.
AC_SUBST(CPPFLAGS)
AC_CONFIG_FILES([Makefile
             src/Makefile])
AC_OUTPUT
