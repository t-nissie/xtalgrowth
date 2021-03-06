/* marsaglia2d.c tests uni64.c
   Time-stamp: <2014-03-04 12:10:50 takeshi>
*/
#include <stdio.h>
#include "uni64.h"
int main()
{
 FILE *fp;
 int i;
 fp = fopen("marsaglia2d.dat", "w");
 fillU(123456789,987654321);
 for (i=1;i<=500000;i++) fprintf(fp,"%20.16f %20.16f\n",uni64(),uni64());
 fclose(fp);
 return 0;
}
/*
Local variables:
  compile-command: "gcc -O0 -Wall -g -o marsaglia2d marsaglia2d.c uni64.c && ./marsaglia2d && gnuplot marsaglia2d.gp"
End:
*/
