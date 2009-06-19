# -*-Makefile-*- for xtalgrowth
# Time-stamp: <2009-06-19 16:07:19 takeshi>
# Author: Takeshi NISHIMATSU
##
CC = gcc
LIBS = -lX11 -lpopt
MAKEDEPEND_DEFINE = -DHAVE_POPT_H
CFLAGS = -Wall -O2 -g $(MAKEDEPEND_DEFINE)

all: xtalgrowth

xtalgrowth: xtalgrowth.o rand_ary.o Xsim.o PostScript.o PostScript_memo.o PostScript_eps.o
	$(CC) $(CFLAGS) -L/usr/X11R6/lib -o $@ $^ $(LIBS)

#dep: depend
#depend:
#	makedepend -Y. $(MAKEDEPEND_DEFINE) *.c

clean:
	rm -f *.o core xtalgrowth a.out
