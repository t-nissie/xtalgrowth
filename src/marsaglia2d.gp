#!/usr/bin/env gnuplot
# marsaglia2d.gp
# Author: Takeshi Nishimatsu
# Time-stamp: <2016-06-07 17:08:27 takeshi>
##
set terminal postscript eps enhanced color solid 22
set output 'marsaglia2d.eps'
set size square
set xtics 0.2
set ytics 0.2
set nogrid
set nokey
set notitle
plot 'marsaglia2d.dat' with dots
set output
!epstopdf marsaglia2d.eps
# Local variables:
#  compile-command: "gnuplot marsaglia2d.gp"
# End:
