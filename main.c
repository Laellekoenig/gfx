#include <raylib.h>
#include <math.h>
#include "gfx.h"

#define HEIGHT 400
#define WIDTH 400
#define FPS 60

float theta;

void init() {
    theta = 0;
}

void destroy() {
}

void update() {
    theta += 0.025;
    if (theta > 2 * PI) theta -= 2 * PI;
}

void render() {
    BeginDrawing();
    ClearBackground(BLACK);

    // pyramid
    VoidMesh mesh = {};
    pyramidMesh(&mesh);

    // transforms
    Mat4D translate, scale, rotate, rotate2 = {0};
    translationMat(&translate, -0.5, -0.5, -0.5);
    scalingMat(&scale, 100, 100, 100);
    yRotationMat(&rotate, theta);
    /*xRotationMat(&rotate2, PI / 8);*/

    multMM4(&scale, &rotate, &scale);
    /*multMM4(&scale, &rotate2, &scale);*/
    multMM4(&scale, &translate, &scale);

    // apply to mesh
    matMulMesh(&mesh, &scale);

    // render
    drawMesh(&mesh);

    // free allocated memory
    clearMesh(&mesh);

    DrawFPS(0, 0);
    EndDrawing();
}

int main() {
    init();
    InitWindow(WIDTH, HEIGHT, "gfx");
    SetTargetFPS(FPS);

    while(!WindowShouldClose()) {
        update();
        render();
    }

    CloseWindow();
    destroy();
}
