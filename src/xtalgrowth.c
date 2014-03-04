/* xtalgrowth.c
   Time-stamp: <2014-03-04 13:33:47 takeshi>
   Author: NISHIMATSU Takeshi */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined HAVE_CONFIG_H
#  include "config.h"
#endif

#include "GrowthParameters.h"
#include "parse_opt.h"
#include "Xsim.h"
#include "PostScript.h"
#include "uni64.h"
#include "hashpjw.h"

int main(int argc, char **argv)
{
  double *x;
  double *y;
  struct GrowthParameters *params;
  int n_fixed;
  int seed1, seed2;
  char buffer[1024]="Additional string for seed2 ";

  params = malloc(sizeof(struct GrowthParameters));
  /* Default values */
  params->diameter = DEFAULT_DIAMETER;
  params->height = DEFAULT_HEIGHT;
  params->criterion = 3;
  params->velocity = DEFAULT_VELOCITY;
  params->guest = "Ms. Crystal Growth";

  parse_opt(argc, argv, params);
  fprintf(stderr, "velocity=%.6f, diameter=%.6f, height=%.3f, criterion=%1d, guest=%s\n",
          params->velocity, params->diameter, params->height, params->criterion, params->guest);

  /* Make seed1 and seed2 from params->guest */
  strcat(buffer,params->guest);
  strcat(buffer," More additional string for seed2");
  seed1=hashpjw(params->guest);
  seed2=hashpjw(buffer);
  fprintf(stderr, "seed1=%d, seed2=%d\n", seed1, seed2);
  fillU(seed1,seed2);

  /* Simulation */
  n_fixed = Xsim(params, &x, &y);

  /* Generate a PostScript file */
  PostScript_generate(params, n_fixed, x, y);

  free(x);
  free(y);
  free(params);
  return 0;
}
