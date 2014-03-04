/* PostScript.c */
#include <stdio.h>
#include "GrowthParameters.h"
#include "PostScript.h"
#include "PostScript_eps.h"
#include "PostScript_memo.h"

void PostScript_generate(struct GrowthParameters *params, int n_fixed, double *x, double *y)
{
  FILE *fp;
  fp = fopen("certification.eps", "r");
  if (fp==NULL) {
    fprintf(stderr, "%s:%d: cannot open file \"certification.eps\". Certification letter will not be output from STDOUT.\n", __FILE__, __LINE__);
  } else {
    PostScript_header();
    PostScript_eps(fp);
    PostScript_memo(params);
    PostScript_show_xtal(params, n_fixed, x, y);
    fclose(fp);
  }
}

void PostScript_header()
{
  puts("%!PS-Adobe-3.0\n"
       "%%Title: xtalgrowth\n"
       "%%DocumentPaperSizes: A4\n"
       "%%EndComments\n"
       "/setpagedevice where\n"
       "{ pop 1 dict\n"
       "  dup /PageSize [ 595 842 ] put\n"
       "  setpagedevice\n"
       "} if\n"
       "\n"
       "%---Units------------------------\n"
       "/mm {2.834646 mul} def\n"
       "\n"
       "%---Define procedures------------\n"
       "/centershow\n"
       " {dup stringwidth pop   %% get length of string\n"
       "  2 div neg\n"
       "  0 rmoveto\n"
       "  show} def\n"
       "\n"
       "/rightshow\n"
       " {dup stringwidth pop   %% get length of string\n"
       "  neg\n"
       "  0 rmoveto\n"
       "  show} def\n"
       "%---End of Definition------------\n");
}

void PostScript_show_xtal(struct GrowthParameters *params, int n_fixed_balls, double *x, double *y)
{
  static const double paper_width = 210.0; /* mm */
  static const double fig_width = 120.0; /* mm */
  static const double fig_bottom_margin = 27.0; /* mm */
  const double fig_left_margin = (paper_width-fig_width)/2;
  int i;

  printf("\n"
	 "%.5g mm %.5g mm translate\n"
	 "%.5g mm dup scale\n", fig_left_margin, fig_bottom_margin, fig_width);

  printf("newpath\n");
  printf("0.4 setgray\n");
  for (i=0; i<n_fixed_balls; i++) {
    printf("  %.5g %.5g %.5g 0 360 arc fill\n", x[i], y[i], params->diameter/2);
  }
  printf("0.0 setgray\n");

  printf("0.0035 setlinewidth 1 setlinecap\n");
  printf("newpath 0 %.5g moveto\n", params->height);
  printf("0 %.5g rlineto\n", -params->height);
  printf("1 0 rlineto\n");
  printf("0 %.5g rlineto\n",  params->height);
  printf("stroke\n");

  printf("1.0 %.5g mm div dup scale\n"
	 "%.5g mm %.5g mm translate\n", fig_width, -fig_left_margin, -fig_bottom_margin);

  printf("\n"
	 "showpage\n"
	 "%%\n");
}
