/* WASMsim.c */
#include "canvas.h"
#include "sim_core.h"
#include "uni64.h"
#include "hashpjw.h"
#include <emscripten.h>
#include <stdio.h>
#include <stdlib.h>
static HTMLCanvasElement *canvas;
static CanvasRenderingContext2D *ctx;

#define WIDTH 600
#define MAX_N_TOUCH 3
#define MAX_N_BALL 10000
#define STEPS_PER_FRAME 100

// Simulation parameter
static double diameter  = 0.0499;
static const double height    = 1.2;
static int criterion = 3;
static double velocity = 0.0008;
static double diameter3, dxd, radius, diameter_dot;
static int n_fixed;
static double *x_result = NULL;
static double *y_result = NULL;
static char* guest;

static void arc(const double x, const double y)
{
  double px = WIDTH * (x - radius);
  double py = WIDTH * (height - y - radius);

  ctx->setFillStyle(ctx, "lightgray");
  ctx->beginPath(ctx);
  ctx->arc(ctx, px + radius*WIDTH, py + radius*WIDTH,
           radius * WIDTH, 0, 2.0 * 3.1415926535);
  ctx->fill(ctx);
}

static void clear_and_redraw()
{
  // Clear the canvas
  ctx->clearRect(ctx, 0, 0, canvas->getWidth(canvas), canvas->getHeight(canvas));
  // Redraw
  for (int j = 0; j < n_fixed; j++) arc(x_result[j], y_result[j]);
}

static void fix_and_reset(double *x, double *y)
{
    add_to_result(*x, *y, diameter3, &n_fixed, x_result, y_result);

    if (n_fixed >= MAX_N_BALL || *y >= (0.97 * height - diameter)) {
        clear_and_redraw();
        ctx->setFillStyle(ctx, "black");
        ctx->setFont(ctx, "45px serif");
        ctx->fillText(ctx, "Thank you for your simulation,",
                                  10, 40, -1);
        ctx->fillText(ctx, guest, 10, 90, -1);
        emscripten_cancel_main_loop();
    }

    *y = height;
    *x = uni64();
}

void WASMsim()
{
  static double x_touch[MAX_N_TOUCH], y_touch[MAX_N_TOUCH];
  static double x = -1.0e10;
  static double y = height;
  static int n_touching = 0;
  static double dx=0.0;
  static double dy=0.0;

  if (x < -100.0) x=uni64();

  // Reraw all balls
  clear_and_redraw();
  // Draw the current ball
  arc(x, y);

  for (int inner_step=0; inner_step<STEPS_PER_FRAME; ++inner_step) {
    if (n_touching == 2) {
      dy = y - y_touch[0];
      go_around(&x, &y, velocity, dx, dy, diameter);
    } else if (n_touching == 1 && (dy = y - y_touch[0]) >= 0.0) {
      dx = x - x_touch[0];
      go_around(&x, &y, velocity, dx, dy, diameter);
    } else {
      y -= velocity;
    }
    n_touching = n_touch(dxd, x, y, n_fixed, x_result, y_result, x_touch, y_touch);

    if (y <= radius || n_touching >= criterion) {
      fix_and_reset(&x, &y);
      break;
    } else if (n_touching == 2) {
      if (y_touch[0] > y_touch[1]) {
        swap_double(&x_touch[0], &x_touch[1]);
        swap_double(&y_touch[0], &y_touch[1]);
      }
      double dx  = x - x_touch[0];
      double dx1 = x_touch[1] - x_touch[0];
      if (dx * dx1 > 0) {
        fix_and_reset(&x, &y);
        break;
      }
    }
  }
}

int main(int argc, char** argv)
{
  int seed1   = hashpjw(argv[1]); /* guest */
  guest       =         argv[1] ;
  diameter    =    atof(argv[2]);
  velocity    =    atof(argv[3]);
  criterion   =    atoi(argv[4]);
  int seed2 = 1234567890 ^ seed1;
  fillU(seed1,seed2);

  canvas = createCanvas("xtalCanvas");
  canvas->setWidth( canvas, 600);
  canvas->setHeight(canvas, 720);

  ctx = canvas->getContext(canvas, "2d");

  diameter3   = 3 * diameter;
  dxd         = diameter * diameter;
  radius      = diameter / 2.0;
  diameter_dot = (int)(WIDTH * diameter) + 1;

  x_result = malloc(2 * MAX_N_BALL * sizeof(double));
  y_result = malloc(2 * MAX_N_BALL * sizeof(double));

  // Prepare substrate
  int n_substrate = 1.0 / diameter;
  double dx = 1.0 / n_substrate;
  double y = radius;
  n_fixed = 0;
  for (int i = -2; i < n_substrate + 2; i++) {
    double x = radius + dx * i;
    x_result[n_fixed] = x;
    y_result[n_fixed++] = y;
  }
  clear_and_redraw();
  // Start animation
  emscripten_set_main_loop(WASMsim, 0, 1);

  free(x_result);
  free(y_result);
  freeCanvas(canvas);
  return 0;
}
