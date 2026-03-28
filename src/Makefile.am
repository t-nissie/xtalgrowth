# -*-Makefile-*- for xtalgrowth
# Time-stamp: <2026-03-29 07:45:16 takeshi>
# Author: Takeshi NISHIMATSU
##
bin_PROGRAMS = xtalgrowth
EXTRA_PROGRAMS = xtalgrowth_cocoa marsaglia marsaglia2d
xtalgrowth_SOURCES = PostScript.c PostScript_eps.c PostScript_memo.c Xsim.c uni64.c hashpjw.c parse_opt.c xtalgrowth.c sim_core.c
noinst_HEADERS = PostScript.h PostScript_eps.h PostScript_memo.h Xsim.h uni64.h hashpjw.h parse_opt.h\
                 GrowthParameters.h sim_core.h
EXTRA_DIST = marsaglia2d.gp pjw.c certification.eps againagain.sh\
                     meson.build.in\
                     meson.build\
                     CMakeLists.txt.in\
                     CMakeLists.txt FindPOPT.cmake
xtalgrowth_cocoa_SOURCES = xtalgrowth_cocoa.m
marsaglia_SOURCES = marsaglia.c uni64.c
marsaglia2d_SOURCES = marsaglia2d.c uni64.c
TESTS = marsaglia marsaglia2d marsaglia2d.gp xtalgrowth
CLEANFILES = marsaglia2d.dat marsaglia2d.eps marsaglia2d.pdf $(EXTRA_PROGRAMS)\
             xtalgrowth.html xtalgrowth.js xtalgrowth.wasm

clean-local:
	-rm -rf *.dSYM

xtalgrowth_cocoa$(EXEEXT): xtalgrowth_cocoa.o
	$(OBJCLD) $(AM_OBJCFLAGS) $(OBJCFLAGS) $^ -o $@ $(OBJCFRAMEWORKS)

.c.ps:
	a2ps --header=`date +%Y-%m-%d` --left-title='xtalgrowth' --right-title='Takeshi Nishimatsu'\
	 --left-footer='' --prologue=color --portrait --columns=1 --margin=3 --borders=off -f 11.5 \
	 --pretty-print=c -o $@ $<
