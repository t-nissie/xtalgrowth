/* PostScript_eps */
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "xtalgrowth.h"
#include "PostScript_eps.h"

void read_and_write_eps()
{
  FILE *fp;
  char *fname = "certification.eps";
  char s[500] ="";

  fp = fopen( fname, "r" );
  if( fp == NULL ){
    fprintf(stderr, "%s:%d: cannot open file \"%s\"\n", __FILE__, __LINE__, fname );
    exit(1);
  }

  while( fgets( s, 500, fp ) != NULL ){
    printf( "%s", s );
  }

  fclose( fp );
}

void PostScript_eps()
{
  puts(
"%---For EPS File-----------------\n"
"%% BeginEPSF and EndEPSF are cited from [Red book].\n"
"/BeginEPSF {\n"
"   /b4_Inc_state save def		% Save state for cleanup\n"
"   /dict_count countdictstack def	% Count objects on dict stack\n"
"   /op_count count 1 sub def		% Count objects on operand stack\n"
"   /epsf_transfer { currenttransfer } bind def	% initial transfer function\n"
"   userdict begin			% Push userdict on dict stack\n"
"   /showpage { } def			% Redefine showpage\n"
"   0 setgray 0 setlinecap		% Prepare graphics state\n"
"   1 setlinewidth 0 setlinejoin\n"
"   10 setmiterlimit [ ] 0 setdash newpath\n"
"   /languagelevel where	{		% If level not equal to 1 then\n"
"      pop languagelevel			% set strokeadjust and\n"
"      1 ne {				% overprint to their defaults\n"
"         false setstrokeadjust false setoverprint\n"
"      } if\n"
"   } if\n"
"} bind def\n"
"\n"
"/EndEPSF{ %%def\n"
"  count op_count sub {pop} repeat     %% Clean up stacks\n"
"  countdictstack dict_count sub {end} repeat\n"
"  b4_Inc_state restore\n"
"} bind def");

  puts("BeginEPSF\n"
  "12 mm 190 mm translate\n"
  "0.89 0.89 scale");
  read_and_write_eps();
  puts("EndEPSF\n");

}
