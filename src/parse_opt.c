/* parse_opt.c
   Time-stamp: <2014-03-05 13:32:01 takeshi>
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
  char *cDiameter = NULL;
  char *cHeight = NULL;
  char *cVelocity = NULL;
  int ierr;
  poptContext optCon;
  struct poptOption optionsTable[] = {
    {"diameter", 'd', POPT_ARG_STRING, &cDiameter,          0 , "Diameter of a ball, d/width",   "0.nnn"  },
    {"height",   'h', POPT_ARG_STRING, &cHeight,            0 , "Height of the system, h/width", "1.nnn"  },
    {"criterion",'c', POPT_ARG_INT,    &(params->criterion),0 , "Criterion, 1=<n=<3",            "n"      },
    {"velocity", 'v', POPT_ARG_STRING, &cVelocity,          0 , "Falling Velocity par step",     "0.000n" },
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
