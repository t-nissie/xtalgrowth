/* PostScript_memo.c
   Time-stamp: <2026-02-10 04:45:41 takeshi>
   Author: Takeshi NISHIMATSU
*/
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "GrowthParameters.h"
#include "PostScript_memo.h"
void PostScript_memo(struct GrowthParameters *params)
{
  struct timeval tv;
  struct tm *today;

  if (gettimeofday(&tv, 0) < 0) exit(1);
  today = localtime(&tv.tv_sec);

  printf("%%---Define local procedures------\n"
	 "/Bond\n"
	 "{newpath  0         2.5 mm moveto  0          6.5 mm lineto stroke\n"
	 " newpath  0        -2.5 mm moveto  0         -6.5 mm lineto stroke\n"
	 " newpath  7.794 mm -2.0 mm moveto  7.794 mm   2.0 mm lineto stroke\n"
	 " newpath -7.794 mm -2.0 mm moveto -7.794 mm   2.0 mm lineto stroke} def\n"
	 "\n"
	 "/imrMark\n"
	 "{\n"
	 "  gsave\n"
	 "  0.34 0.34 1.0 setrgbcolor\n"
	 "  newpath\n"
	 "   0         0      1.45 mm 0 360 arc fill\n"
	 "   0         9   mm 1.45 mm 0 360 arc fill\n"
	 "   0        -9   mm 1.45 mm 0 360 arc fill\n"
	 "   7.794 mm  4.5 mm 1.45 mm 0 360 arc fill\n"
	 "   7.794 mm -4.5 mm 1.45 mm 0 360 arc fill\n"
	 "  -7.794 mm  4.5 mm 1.45 mm 0 360 arc fill\n"
	 "  -7.794 mm -4.5 mm 1.45 mm 0 360 arc fill\n"
	 "  0.85 mm setlinewidth 1 setlinecap\n"
	 "  Bond\n"
	 "  60 rotate Bond\n"
	 "  60 rotate Bond\n"
	 " grestore\n"
	 "} def\n"
	 "%%---End of local definition------\n"
	 "\n"
	 "15 mm 15 mm translate\n"
	 "0.6 dup scale\n"
	 "imrMark\n"
	 "1.0 0.6 div dup scale\n"
	 "-15 mm -15 mm translate\n"
	 "\n"
	 "195 mm 15 mm translate\n"
	 "0.6 dup scale\n"
	 "imrMark\n"
	 "1.0 0.6 div dup scale\n"
	 "-195 mm -15 mm translate\n"
	 "\n"
	 "195 mm 282 mm translate\n"
	 "0.6 dup scale\n"
	 "imrMark\n"
	 "1.0 0.6 div dup scale\n"
	 "-195 mm -282 mm translate\n"
	 "\n"
	 "15 mm 282 mm translate\n"
	 "0.6 dup scale\n"
	 "imrMark\n"
	 "1.0 0.6 div dup scale\n"
	 "-15 mm -282 mm translate\n"
	 "\n"
	 "gsave\n"
	 "0.34 0.34 1.0 setrgbcolor\n"
	 "1.5 mm setlinewidth 0 setlinecap\n"
	 "newpath  15 mm  25 mm moveto  15 mm 272 mm lineto stroke\n"
	 "newpath 195 mm  25 mm moveto 195 mm 272 mm lineto stroke\n"
	 "newpath  25 mm  15 mm moveto 185 mm  15 mm lineto stroke\n"
	 "newpath  25 mm 282 mm moveto 185 mm 282 mm lineto stroke\n"
	 "grestore\n"
	 "\n"
	 "\n"
	 "/Times-Roman findfont 36 scalefont setfont\n"
	 "105 mm 230 mm moveto\n"
	 "(%s) centershow\n"
	 "\n"
	 "/Times-Roman findfont 30 scalefont setfont\n"
	 "195 mm 191 mm moveto\n"
	 "(%4d-%2.2d-%2.2d    ) rightshow\n"
	 "/Courier findfont 12 scalefont setfont\n"
	 "185 mm 18 mm moveto\n"
	 "(https://t-nissie.github.io/xtalgrowth/) rightshow\n"
	 "\n", params->guest, today->tm_year + 1900, today->tm_mon+1, today->tm_mday);
}
