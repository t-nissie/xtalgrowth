/* Xsim.c
   Time-stamp: <2011-10-07 17:04:18 takeshi>
   Author: Takeshi NISHIMATSU
*/
#include <unistd.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "xtalgrowth.h"
#include "Xsim.h"
#include "uni64.h"
#define WIDTH 320
#define MAX_N_TOUCH 3
#define MAX_N_BALL 10000
const double ratio=0.2;
double diameter, diameter3, dxd, radius;
int diameter_dot;
double height;
Display *d;
Window  w;
GC      gc;

void arc(double x, double y)
{
  XFillArc(d, w, gc,
	   (int)(WIDTH*(x-radius)),
	   (int)(WIDTH*(height-y-radius)),
	   diameter_dot, diameter_dot, 0*64, 360*64);
  return;
}

int n_touch(double x, double y, int n_ary,
	    double x_ary[], double y_ary[], /* input */
	    double x_touch[], double y_touch[]) /* output */
{
  int i;
  double xd, yd;
  int n=0;
  for (i=0; i<n_ary; i++) {
    xd = x - x_ary[i];
    yd = y - y_ary[i];
    if (xd*xd+yd*yd <= dxd) {
      x_touch[n] = x_ary[i];
      y_touch[n] = y_ary[i];
      n+=1;
      if (n==MAX_N_TOUCH) return n;
    }
  }
  return n;
}

/* go around to avoid a under ball ((-dx, -dy) direction) */
void go_around(double *x, double *y, double velocity, double dx, double dy)
{
  if (dx>0) {
    *x += velocity*dy/diameter*ratio;
    if (*x>=1.0) *x -= 1.0;
  } else {
    *x -= velocity*dy/diameter*ratio;
    if (*x<0.00) *x += 1.0;
  }
  *y -= velocity*(dx>0 ? dx : -dx)/diameter*ratio;
}

void add_to_result(double x, double y, int *n_fixed,
		  double x_result[], double y_result[])
{
  x_result[(*n_fixed)  ] = x;
  y_result[(*n_fixed)++] = y;
  if (x<=diameter3) {
    x_result[(*n_fixed)  ] = x+1;
    y_result[(*n_fixed)++] = y;
  }
  if (x>=1.0-diameter3) {
    x_result[(*n_fixed)  ] = x-1;
    y_result[(*n_fixed)++] = y;
  }
}

/* Redraw the window if it has been exposed. */
void exposure(const int n_fixed,
	      const double x_result[],
	      const double y_result[])
{
  XEvent event;
  int j;
  if (XCheckTypedEvent(d, Expose, &event)) {
    XClearWindow(d, w);
    for (j=0; j<n_fixed; j++) arc(x_result[j], y_result[j]);
  }
}

int Xsim(struct GrowthParameters *params, /* input */
	 double **x_result, double **y_result)   /* output */
{
  int i, n_substrate, n_fixed, n_touching;
  double x, y, dx, dy, dx1, tmp;
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
    (*x_result)[n_fixed]= x; (*y_result)[n_fixed++]=y; arc(x,y);
  }

  /* Show the initial state on display. The argument of usleep()
     should be enough long micro-second to show the initial state. */
  usleep(2000000);

  /* main loop */
  y = 0.0;
  for (i=0; i<MAX_N_BALL && y<(0.97*height-diameter); i++) {
    x = uni64();
    y = height;
    arc(x, y);
    n_touching = 0;
    while (1) {
      arc(x, y); /* remove the last ball */
      exposure(n_fixed, *x_result, *y_result); /* Redraw the window if it has been exposed. */
      if (n_touching==2) { /* Here, n_touching may be 0, 1, or the spetial case of 2. */
	dy = y - y_touch[0]; /* dx has already been calculated. */
	go_around(&x, &y, params->velocity, dx, dy);
      } else if (n_touching==1 && (dy = y - y_touch[0])>=0.0) {
	dx = x - x_touch[0];
	go_around(&x, &y, params->velocity, dx, dy);
      } else {
	y -= params->velocity;
      }
      arc(x, y); /* draw a new ball */
      XFlush(d);
      n_touching = n_touch(x, y, n_fixed, *x_result, *y_result, x_touch, y_touch);
      if (y<=radius || n_touching>=params->criterion) {
	add_to_result(x, y, &n_fixed, *x_result, *y_result);
	break;
      } else if (n_touching==2) {
	if (y_touch[0] > y_touch[1]) {
	  /* SWAP to let (x,y)_touch[0] is the bottom ball.*/
	  tmp=x_touch[0]; x_touch[0]=x_touch[1]; x_touch[1]=tmp;
	  tmp=y_touch[0]; y_touch[0]=y_touch[1]; y_touch[1]=tmp;
	}
	dx  = x          - x_touch[0];
	dx1 = x_touch[1] - x_touch[0];
	if (dx*dx1>0) {
	  add_to_result(x, y, &n_fixed, *x_result, *y_result);
	  break;
	}
      }
    }
  }

  return n_fixed;
}
