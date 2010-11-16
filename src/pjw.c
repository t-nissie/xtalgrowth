/* pjw.c tests hashpjw.c */
#include <stdio.h>
#include "hashpjw.h"
int main(int argc, char **argv)
{
  printf("%10d %s\n",hashpjw(argv[1]),argv[1]);
  return 0;
}
/*
Local variables:
  compile-command: "gcc -o pjw pjw.c hashpjw.c && for f in *; do ./pjw $f; done"
End:
*/
