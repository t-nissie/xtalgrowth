/* hashpjw.c
   Time-stamp: <2010-11-13 21:15:18 takeshi>
   Author: Takeshi NISHIMATSU
   Reference:
*/
#define PRIME 211
int hashpjw(char *s)
{
  char *p;
  unsigned h = 0;
  unsigned g;
  for (p=s; *p; p++) {
    h = (h<<4) + (*p);
    if (g=h & 0xf0000000) {
      h = h^(g>>24);
      h = h^g;
    }
  }
  return h % PRIME;
}
