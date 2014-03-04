/* marsaglia.c tests uni64.c
   Time-stamp: <2014-03-04 12:22:45 takeshi>
*/
#include <stdio.h>
#include <stdlib.h>
#include "uni64.h"
int main()
{
 double x;
 int i;
 static double a[5] = {
   5534819329886631.0,
   7222984478804879.0,
   3591084909746267.0,
   6938004922860200.0,
   3518398318353033.0 };
 fillU(123456789,987654321);
 for (i=0;i<10000000;i++) x=uni64();
 for (i=0;i<5;i++) {
   x = uni64();
   if (x*9007199254740992.0 != a[i]) exit(i+1);
 }
 return 0;
}
/*
Local variables:
  compile-command: "gcc -O0 -Wall -g -o marsaglia marsaglia.c uni64.c && ./marsaglia"
End:
*/
