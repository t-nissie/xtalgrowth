#include "canvas.h"

int main(void) {
    HTMLCanvasElement *canvas = createCanvas("myCanvas");
    CanvasRenderingContext2D *ctx = canvas->getContext(canvas, "2d");
    ctx->setFont(ctx, "48px serif");
    ctx->fillText(ctx, "Hello World", 0, 150, -1);
    freeCanvas(canvas);
    return 0;
}
