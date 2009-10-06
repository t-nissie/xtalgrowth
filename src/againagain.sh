#!/bin/sh
until [ ] ; do
  ./xtalgrowth -d 0.033333 -c 3 -n  800 > /dev/null
  ./xtalgrowth -d 0.033    -c 3 -n  800 > /dev/null
  ./xtalgrowth -d 0.033    -c 2 -n  800 > /dev/null
  ./xtalgrowth -d 0.033    -c 1 -n  400 > /dev/null
  ./xtalgrowth -d 0.015    -c 1 -n 2000 > /dev/null
done
