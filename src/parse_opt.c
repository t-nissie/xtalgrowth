/* parse_opt.c
   Time-stamp: <2017-05-23 06:26:43 takeshi>
   Author: Takeshi NISHIMATSU
*/
#include <stdlib.h>

#if defined HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef HAVE_POPT_H
#  include <popt.h>
#else
#  include <unistd.h>
#endif

#include "GrowthParameters.h"
#include "parse_opt.h"

void parse_opt(int argc, char **argv, struct GrowthParameters *params)
{
#ifdef HAVE_POPT_H
  int ierr;
  poptContext optCon;
  struct poptOption optionsTable[] = {
    {"diameter", 'd', POPT_ARG_DOUBLE, &(params->diameter), 0 , "Diameter of a ball, d/width",   "0.4999" },
    {"height",   'h', POPT_ARG_DOUBLE, &(params->height),   0 , "Height of the system, h/width", "1.2"    },
    {"criterion",'c', POPT_ARG_INT,    &(params->criterion),0 , "Criterion, 1=<n=<3",            "n"      },
    {"velocity", 'v', POPT_ARG_DOUBLE, &(params->velocity), 0 , "Falling Velocity par step",     "0.0008" },
    {"guest",    'g', POPT_ARG_STRING, &(params->guest),    0 , "Name of the guest",            "'String'"},
    POPT_AUTOHELP
    POPT_TABLEEND
  };
  optCon = poptGetContext("xtalgrowth", argc, (const char **)argv, optionsTable, 0);
  poptSetOtherOptionHelp(optCon, "[OPTIONS...] > result.ps");

  ierr=poptGetNextOpt(optCon);
  if (ierr < -1) {
    fprintf(stderr, "%s: %s\n", poptBadOption(optCon, POPT_BADOPTION_NOALIAS), poptStrerror(ierr));
    poptPrintHelp(optCon, stderr, 0);
    exit(0);
  }

  if (params->criterion < 1 || 3 < params->criterion) {
    params->criterion = 3;
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
