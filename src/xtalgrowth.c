/* xtalgrowth.c
   Time-stamp: <2026-05-11 22:23:22 takeshi>
   Author: NISHIMATSU Takeshi */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GrowthParameters.h"
#include "parse_opt.h"
#include "Xsim.h"
#include "PostScript.h"
#include "uni64.h"
#include "hashpjw.h"

int main(int argc, char **argv)
{
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
  n_fixed = Xsim(params);

  /* Generate a PostScript file */
  PostScript_generate(params, n_fixed);

  free(params->x_results);
  free(params->y_results);
  free(params);
  return 0;
}
