/* uni64.c
   Random Number Generator
   Time-stamp: <2010-11-17 11:49:16 takeshi>
   References:
     George Marsaglia and Wai Wan Tsang: "The 64-bit universal RNG",
     Statistics & Probability Letters, Vol.66, pp.183-187 (15 January 2004),
     doi:10.1016/j.spl.2003.11.001. Note that a part of code in the bottom
     of p.186, "y=(8888*x)%65579;" should be replaced by "y=(8888*y)%65579;".
     Consequently, 5 values of "The correct output" in p.187 are incorrect.
     See http://sci4um.com/about16220-asc.html .
*/
#include "uni64.h"

static double U[98];

void fillU(int seed1,int seed2)
{
  double s,t;
  int x,y,i,j;
  x=seed1;
  y=seed2;
  for (i=1;i<98;i++) {
    s=0.0;
    t=0.5;
    for (j=1;j<54;j++) {
      x=(6969*x)%65543;
      y=(8888*y)%65579;
      if (((x^y)&32)>0) s=s+t;
      t=.5*t;
    }
    U[i]=s;
  }
}

double uni64()
{
  const double r=9007199254740881.0/9007199254740992.0;
  const double d=    362436069876.0/9007199254740992.0;
  static double c=0;
  static int i=97;
  static int j=33;
  double x;
  x=U[i]-U[j];
  if (x<0.0) x=x+1.0;
  U[i]=x;
  if (--i == 0) i=97;
  if (--j == 0) j=97;
  c=c-d;
  if (c<0.0) c=c+r;
  x=x-c;
  if(x<0.0) return (x+1.0);
  return x;
}
