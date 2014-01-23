# -*-Makefile-*- for xtalgrowth
# Time-stamp: <2014-01-23 18:40:09 takeshi>
# Author: Takeshi NISHIMATSU
##
bin_PROGRAMS = xtalgrowth xtalgrowth_cocoa
xtalgrowth_SOURCES = PostScript.c PostScript_eps.c PostScript_memo.c Xsim.c uni64.c hashpjw.c xtalgrowth.c
EXTRA_DIST         = PostScript.h PostScript_eps.h PostScript_memo.h Xsim.h uni64.h hashpjw.h xtalgrowth.h\
                     marsaglia.c\
                     marsaglia2d.c\
                     marsaglia2d.gp pjw.c certification.eps againagain.sh
xtalgrowth_cocoa_SOURCES = xtalgrowth_cocoa.m

xtalgrowth_cocoa$(EXEEXT): xtalgrowth_cocoa.o
	$(OBJCLD) $(AM_OBJCFLAGS) $(OBJCFLAGS) $^ -o $@ $(OBJCFRAMEWORKS)

.c.ps:
	a2ps --header=`date +%Y-%m-%d` --left-title='xtalgrowth' --right-title='Takeshi Nishimatsu'\
	 --left-footer='' --prologue=color --portrait --columns=1 --margin=3 --borders=off -f 11.5 \
	 --pretty-print=c -o $@ $<
