/* xtalgrowth.c */
/* 2003,01,05   NISHIMATSU Takeshi */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef HAVE_POPT_H
#  include <popt.h>
#else
#  include <unistd.h>
#endif

#include "xtalgrowth.h"
#include "Xsim.h"
#include "PostScript.h"
#include "PostScript_memo.h"
#include "PostScript_eps.h"
#include "uni64.h"
#include "hashpjw.h"
#define DEFAULT_DIAMETER 0.0499999999999
#define DEFAULT_HEIGHT   1.2
#define DEFAULT_VELOCITY 0.0008
#define TMP_LEN 200

void parse_opt(int argc, char **argv, struct GrowthParameters *params);

int main(int argc, char **argv)
{
  double *x;
  double *y;
  struct GrowthParameters *params;
  int n_fixed;
  int seed1, seed2;
  char tmp[TMP_LEN]="abcdef";

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

  /* Make seed1 adn seed2 from params->guest */
  strlcat(tmp,params->guest,TMP_LEN);
  strlcat(tmp,"uvwxyz",     TMP_LEN);
  seed1=hashpjw(params->guest);
  seed2=hashpjw(tmp);
  fillU(seed1,seed2);

  /* Simulation */
  n_fixed = Xsim(params, &x, &y);

  /* Generate a PostScript file */
  PostScript_header();
  PostScript_eps();
  PostScript_memo(params);
  PostScript_show_xtal(params, n_fixed, x, y);

  free(x);
  free(y);
  free(params);
  return 0;
}

void parse_opt(int argc, char **argv, struct GrowthParameters *params)
{
#ifdef HAVE_POPT_H
  char *cDiameter = NULL;
  char *cHeight = NULL;
  char *cVelocity = NULL;
  int ierr;
  poptContext optCon;
  struct poptOption optionsTable[] = {
    {"diameter", 'd', POPT_ARG_STRING, &cDiameter,          0 , "Diameter of a ball, r/width",   "0.nnn"  },
    {"height",   'h', POPT_ARG_STRING, &cHeight,            0 , "Height of the system, h/width", "1.nnn"  },
    {"criterion",'c', POPT_ARG_INT,    &(params->criterion),0 , "Criterion, 1=<n=<3",            "n"      },
    {"velocity", 'v', POPT_ARG_STRING, &cVelocity,          0 , "Falling Velocity par step",     "0.00n"  },
    {"guest",    'g', POPT_ARG_STRING, &(params->guest),    0 , "Name of the guest",            "'String'"},
    {"help",     'H', POPT_ARG_NONE,   NULL,               'H', "Print Usage",                    NULL    },
    {"usage",    'u', POPT_ARG_NONE,   NULL,               'u', "Print Usage",                    NULL    },
    { NULL,       0 , 0,               NULL,                0 , NULL,                             NULL    }
  };
  optCon = poptGetContext("xtalgrowth", argc, (const char **)argv, optionsTable, 0);

  ierr=poptGetNextOpt(optCon);
  if (ierr < -1 || ierr >= 0) {
    poptPrintHelp(optCon, stderr, 0);
    exit(0);
  }

  if (cDiameter!=NULL) {
    params->diameter = atof(cDiameter);
    if (params->diameter<=0.0) params->diameter = DEFAULT_DIAMETER;
  }

  if (cHeight!=NULL) {
    params->height = atof(cHeight);
    if (params->height<=0.0) params->diameter = DEFAULT_HEIGHT;
  }

  if (params->criterion < 1 || 3 < params->criterion) {
    params->criterion = 3;
  }

  if (cVelocity!=NULL) {
    params->velocity = atof(cVelocity);
    if (params->velocity<=0.0) params->velocity = DEFAULT_VELOCITY;
  }
#else /* HAVE_POPT_H */
  int c;
  extern char *optarg;
  while ((c = getopt(argc, argv, "v:d:n:c:g:")) != -1) {
    switch (c) {
    case 'v':
      params->velocity = atof(optarg);
      if (params->velocity <= 0.0) params->velocity = DEFAULT_VELOCITY;
      break;
    case 'd':
      params->diameter = atof(optarg);
      if (params->diameter <= 0.0) params->diameter = DEFAULT_DIAMETER;
      break;
    case 'h':
      params->height = atof(optarg);
      if (params->height <= 0.0) params->height = DEFAULT_HEIGHT;
      break;
    case 'c':
      params->criterion = atoi(optarg);
      if (params->criterion < 1 || 3 < params->criterion) {
        params->criterion = 3;
      }
      break;
    case 'g':
      params->guest = optarg;
      break;
    default:
      exit(3);
      break;
    }
  }
#endif /* HAVE_POPT_H */

  return;
}
