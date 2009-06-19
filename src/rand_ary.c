/* rand_ary.c
   Time-stamp: <2009-06-19 14:17:25 takeshi>
   Author: Takeshi NISHIMATSU
*/
#include <stdlib.h>
#include <sys/time.h>

/* generate a malloc()ated array of random numbers 0<=r<1 */
double *rand_ary(int n)
{
  struct timeval tv;
  double *ary;
  double d;
  int i;
  ary = malloc(n*sizeof(double));
  if (gettimeofday(&tv, 0) < 0) exit(2);
  srand((unsigned int)tv.tv_usec);
  d = 1.0 / (RAND_MAX + 1.0);
  for (i=0;i<n;i++) ary[i]=d*rand();
  return ary;
}
