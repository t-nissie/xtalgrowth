#include "canvas.h"
#include "sim_core.h"
#include "uni64.h"

#define WIDTH 600
#define MAX_N_TOUCH 3
#define MAX_N_BALL 10000

static double height;
static CanvasRenderingContext2D *ctx;

static void arc(double x, double y, double radius, int diameter_dot) {
  double px = WIDTH * (x - radius);
  double py = WIDTH * (height - y - radius);

  ctx->beginPath(ctx);
  ctx->arc(ctx, px + radius*WIDTH, py + radius*WIDTH,
           radius * WIDTH, 0, 2.0 * 3.1415926535);
  ctx->fill(ctx);
}

static void redraw(const int n_fixed,
                   const double x_result[],
                   const double y_result[],
                   const double radius,
                   const int diameter_dot)
{
  ctx->clearRect(ctx, 0, 0, WIDTH, (int)(WIDTH * height));
  for (int j = 0; j < n_fixed; j++) {
    arc(x_result[j], y_result[j], radius, diameter_dot);
  }
}

int WASMsim(double **x_result, double **y_result)
{
  int i, n_substrate, n_fixed, n_touching;
  double x, y, dx, dy, dx1, tmp;
  double diameter, diameter3, dxd, radius;
  int diameter_dot;
  double x_touch[MAX_N_TOUCH], y_touch[MAX_N_TOUCH];

  // 固定パラメータ
  diameter  = 0.04999;
  height    = 1.2;
  int criterion = 3;
  double velocity = 0.0008;

  diameter3   = 3 * diameter;
  dxd         = diameter * diameter;
  radius      = diameter / 2.0;
  diameter_dot = (int)(WIDTH * diameter) + 1;

  *x_result = malloc(2 * MAX_N_BALL * sizeof(double));
  *y_result = malloc(2 * MAX_N_BALL * sizeof(double));

  // 初期状態
  n_substrate = 1.0 / diameter;
  dx = 1.0 / n_substrate;
  y = radius;
  n_fixed = 0;
  for (i = -2; i < n_substrate + 2; i++) {
    x = radius + dx * i;
    (*x_result)[n_fixed] = x;
    (*y_result)[n_fixed++] = y;
  }
  redraw(n_fixed, *x_result, *y_result, radius, diameter_dot);

  // メインループ
  y = 0.0;
  for (i = 0; i < MAX_N_BALL && y < (0.97 * height - diameter); i++) {
    x = uni64();
    y = height;
    n_touching = 0;

    while (1) {
      redraw(n_fixed, *x_result, *y_result, radius, diameter_dot);
      arc(x, y, radius, diameter_dot);

      if (n_touching == 2) {
        dy = y - y_touch[0];
        go_around(&x, &y, velocity, dx, dy, diameter);
      } else if (n_touching == 1 && (dy = y - y_touch[0]) >= 0.0) {
        dx = x - x_touch[0];
        go_around(&x, &y, velocity, dx, dy, diameter);
      } else {
        y -= velocity;
      }

      redraw(n_fixed, *x_result, *y_result, radius, diameter_dot);
      arc(x, y, radius, diameter_dot);

      n_touching = n_touch(dxd, x, y, n_fixed,
                           *x_result, *y_result,
                           x_touch, y_touch);

      if (y <= radius || n_touching > criterion) {
        add_to_result(x, y, diameter3, &n_fixed,
                      *x_result, *y_result);
        break;
      } else if (n_touching == 2) {
        if (y_touch[0] > y_touch[1]) {
          tmp = x_touch[0]; x_touch[0] = x_touch[1]; x_touch[1] = tmp;
          tmp = y_touch[0]; y_touch[0] = y_touch[1]; y_touch[1] = tmp;
        }
        dx  = x - x_touch[0];
        dx1 = x_touch[1] - x_touch[0];
        if (dx * dx1 > 0) {
          add_to_result(x, y, diameter3, &n_fixed,
                        *x_result, *y_result);
          break;
        }
      }
    }
  }
  return n_fixed;
}

int main(void)
{
  const int seed1=12345678;
  const int seed2=87654321;
  fillU(seed1,seed2);

  HTMLCanvasElement *canvas = createCanvas("xtalCanvas");
  ctx = canvas->getContext(canvas, "2d");

  ctx->setFillStyle(ctx, "black");  // 背景色など必要なら
  double *x_result = NULL, *y_result = NULL;
  WASMsim(&x_result, &y_result);

  // 必要なら結果を何かに使う
  free(x_result);
  free(y_result);
  freeCanvas(canvas);
  return 0;
}
