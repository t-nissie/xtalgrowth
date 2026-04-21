/* Xsim.c
   Time-stamp: <2026-04-21 23:00:49 takeshi>
   Author: Takeshi NISHIMATSU
*/
#include <unistd.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "GrowthParameters.h"
#include "sim_core.h"
#include "Xsim.h"
#include "uni64.h"
#define WIDTH 600
#define MAX_N_TOUCH 3
#define MAX_N_BALL 10000
double height;
Display *d;
Window  w;
GC      gc;
void arc(double x, double y, double radius, int diameter_dot)
{
  XFillArc(d, w, gc,
           (int)(WIDTH*(x-radius)),
           (int)(WIDTH*(height-y-radius)),
           diameter_dot, diameter_dot, 0*64, 360*64);
  return;
}

/* Redraw the window if it has been exposed. */
void exposure(const int n_fixed,
              const double x_result[],
              const double y_result[], const double radius, const int diameter_dot)
{
  XEvent event;
  int j;
  if (XCheckTypedEvent(d, Expose, &event)) {
    XClearWindow(d, w);
    for (j=0; j<n_fixed; j++) arc(x_result[j], y_result[j], radius, diameter_dot);
  }
}

int Xsim(struct GrowthParameters *params, /* input */
         double **x_result, double **y_result)   /* output */
{
  int i, n_substrate, n_fixed, n_touching;
  double x, y, dx, dy, dx1;
  double diameter, diameter3, dxd, radius;
  int diameter_dot;
  double x_touch[MAX_N_TOUCH], y_touch[MAX_N_TOUCH];

  *x_result = malloc(2*MAX_N_BALL*sizeof(double));
  *y_result = malloc(2*MAX_N_BALL*sizeof(double));

  /* Set global arguments in this file */
  diameter = params->diameter;
  diameter3 = 3*diameter;
  dxd = diameter*diameter;
  radius = diameter/2;
  diameter_dot = (int)(WIDTH*diameter) + 1;  /* You can remove this `+1'. */
  height = params->height;

  d = XOpenDisplay (NULL);
  w = XCreateSimpleWindow( d, RootWindow(d,0),
                           400,   2,
                           WIDTH, (int)(WIDTH*height),
                           1,
                           BlackPixel(d,0),
                           WhitePixel(d,0));
  XSelectInput(d, w, ExposureMask);
  XMapWindow(d, w);

  gc = XCreateGC(d, w, 0, 0);
  XSetFunction(d, gc, GXxor);
  XSetForeground(d, gc, WhitePixel(d,0));

  XFlush(d);

  /* prepare the initial state */
  n_substrate = 1.0/diameter;
  dx = 1.0/n_substrate;
  y = radius;
  n_fixed=0;
  for (i=-2; i<n_substrate+2; i++) {
    x = radius+dx*i;
    (*x_result)[n_fixed]= x; (*y_result)[n_fixed++]=y; arc(x,y, radius, diameter_dot);
  }

  /* Show the initial state on display. The argument of usleep()
     should be enough long micro-second to show the initial state. */
  usleep(2000000);

  /* main loop */
  y = 0.0;
  for (i=0; i<MAX_N_BALL && y<(0.97*height-diameter); i++) {
    x = uni64();
    y = height;
    arc(x, y, radius, diameter_dot);
    n_touching = 0;
    while (1) {
          arc(x, y, radius, diameter_dot); /* remove the last ball */
      exposure(n_fixed, *x_result, *y_result, radius, diameter_dot); /* Redraw the window if it has been exposed. */
      if (n_touching==2) { /* Here, n_touching may be 0, 1, or the spetial case of 2. */
        dy = y - y_touch[0]; /* dx has already been calculated. */
        go_around(&x, &y, params->velocity, dx, dy, diameter);
      } else if (n_touching==1 && (dy = y - y_touch[0])>=0.0) {
        dx = x - x_touch[0];
        go_around(&x, &y, params->velocity, dx, dy, diameter);
      } else {
        y -= params->velocity;
      }
      arc(x, y, radius, diameter_dot); /* draw a new ball */
      XFlush(d);
      n_touching = n_touch(dxd, x, y, n_fixed, *x_result, *y_result, x_touch, y_touch);
      if (y<=radius || n_touching>=params->criterion) {
        add_to_result(x, y, diameter3, &n_fixed, *x_result, *y_result);
        break;
      } else if (n_touching==2) {
        if (y_touch[0] > y_touch[1]) {
          swap_double(&x_touch[0], &x_touch[1]);
          swap_double(&y_touch[0], &y_touch[1]);
        }
        dx  = x          - x_touch[0];
        dx1 = x_touch[1] - x_touch[0];
        if (dx*dx1>0) {
          add_to_result(x, y, diameter3, &n_fixed, *x_result, *y_result);
          break;
        }
      }
    }
  }

  return n_fixed;
}
