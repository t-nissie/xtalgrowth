/* hashpjw.c

   P. J. Weinberger's hash function from the Dragon Book
   (Alfred V. Aho, Ravi Sethi, and Jeffrey D. Ullman:
   "Compilers: Principles, Techniques, and Tools" (1986),
   ISBN:0-201-10088-6, Addison Wesley).

   Time-stamp: <2010-11-19 11:23:27 takeshi>
*/
#include "hashpjw.h"
#define PRIME 268435399
/* The largest prime number bigger than 0x0fffffff=268435455. */
int hashpjw(char *s)
{
  char *p;
  unsigned h = 0;
  unsigned g;
  for (p=s; *p; p++) {
    h = (h<<4) + (*p);
    if (g = h&0xf0000000) {
      h = h^(g>>24);
      h = h^g;
    }
  }
  return h%PRIME;
}
