#!/usr/bin/env gnuplot
# marsaglia2d.gp
# Author: Takeshi Nishimatsu
# Time-stamp: <2010-11-21 13:18:08 takeshi>
##
set terminal postscript portrait enhanced color solid 22
set output 'marsaglia2d.eps'

set size square
set xtics 0.2
set ytics 0.2
set nogrid
set nokey

set notitle
plot 'marsaglia2d.dat' with dots

# Local variables:
#  compile-command: "gnuplot marsaglia2d.gp"
# End:
