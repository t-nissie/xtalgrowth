/* marsaglia.c tests uni64.c
   Time-stamp: <2010-11-16 19:44:58 takeshi>
*/
#include <stdio.h>
#include "uni64.h"
int main()
{
 double x;
 int i;
 fillU(123456789,987654321);
 for (i=1;i<=10000000;i++) x=uni64();
 for(i=1;i<=5;i++) printf("%18.0f \n",uni64()*9007199254740992.0);
 return 0;
}
/* The correct output:
   5534819329886631
   7222984478804879
   3591084909746267
   6938004922860200
   3518398318353033

Local variables:
  compile-command: "gcc -O0 -Wall -g -o marsaglia marsaglia.c uni64.c && ./marsaglia"
End:
*/
