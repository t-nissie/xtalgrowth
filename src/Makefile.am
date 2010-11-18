# -*-Makefile-*- for xtalgrowth
# Time-stamp: <2010-11-18 17:30:52 takeshi>
# Author: Takeshi NISHIMATSU
##
bin_PROGRAMS = xtalgrowth
xtalgrowth_SOURCES = PostScript.c PostScript_eps.c PostScript_memo.c Xsim.c uni64.c hashpjw.c xtalgrowth.c
EXTRA_DIST         = PostScript.h PostScript_eps.h PostScript_memo.h Xsim.h uni64.h hashpjw.h xtalgrowth.h\
                     marsaglia.c pjw.c certification.eps againagain.sh

.c.ps:
	a2ps --header=`date +%Y-%m-%d` --left-title='xtalgrowth' --right-title='Takeshi Nishimatsu'\
	 --left-footer='' --prologue=color --portrait --columns=1 --margin=3 --borders=off -f 11.5 \
	 --pretty-print=c -o $@ $<
