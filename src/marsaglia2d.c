/* marsaglia2d.c tests uni64.c
   Time-stamp: <2010-11-21 13:14:36 takeshi>
*/
#include <stdio.h>
#include "uni64.h"
int main()
{
 int i;
 fillU(123456789,987654321);
 for (i=1;i<=500000;i++) printf("%20.16f %20.16f\n",uni64(),uni64());
 return 0;
}
/*
Local variables:
  compile-command: "gcc -O0 -Wall -g -o marsaglia2d marsaglia2d.c uni64.c && ./marsaglia2d > marsaglia2d.dat && gnuplot marsaglia2d.gp"
End:
*/
