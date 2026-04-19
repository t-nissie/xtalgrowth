/* sim_core.c
   Author: Takeshi NISHIMATSU
*/
#include "sim_core.h"

void swap_double(double *a, double *b)
{
  double t = *a;
  *a = *b;
  *b = t;
}

int n_touch(double dxd, double x, double y, int n_ary,
            double x_ary[], double y_ary[], /* input */
            double x_touch[], double y_touch[]) /* output */
{
  const int MAX_N_TOUCH=3;
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
void go_around(double *x, double *y, double velocity, double dx, double dy, double diameter)
{
  const double ratio=0.2;
  if (dx>0) {
    *x += velocity*dy/diameter*ratio;
    if (*x>=1.0) *x -= 1.0;
  } else {
    *x -= velocity*dy/diameter*ratio;
    if (*x<0.00) *x += 1.0;
  }
  *y -= velocity*(dx>0 ? dx : -dx)/diameter*ratio;
}

void add_to_result(double x, double y, double diameter3, int *n_fixed,
                   double x_result[], double y_result[])
{
  x_result[(*n_fixed)  ] = x;
  y_result[(*n_fixed)++] = y;
  if (x<=diameter3) {      /* periodic boundary condition +x */
    x_result[(*n_fixed)  ] = x+1;
    y_result[(*n_fixed)++] = y;
  }
  if (x>=1.0-diameter3) {  /* periodic boundary condition -x */
    x_result[(*n_fixed)  ] = x-1;
    y_result[(*n_fixed)++] = y;
  }
}
