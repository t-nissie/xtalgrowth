# -*-Makefile-*- for xtalgrowth
# Time-stamp: <2010-11-17 11:48:30 takeshi>
# Author: Takeshi NISHIMATSU
##
bin_PROGRAMS = xtalgrowth
xtalgrowth_SOURCES = PostScript.c PostScript_eps.c PostScript_memo.c Xsim.c rand_ary.c uni64.c hashpjw.c xtalgrowth.c
EXTRA_DIST         = PostScript.h PostScript_eps.h PostScript_memo.h Xsim.h rand_ary.h uni64.h hashpjw.h xtalgrowth.h\
                     makefile.c pjw.c certification.eps againagain.sh

.c.ps:
	a2ps --header=`date +%Y-%m-%d` --left-title='xtalgrowth' --right-title='Takeshi Nishimatsu'\
	 --left-footer='' --prologue=color --portrait --columns=1 --margin=3 --borders=off -f 11.5 \
	 --pretty-print=c -o $@ $<
