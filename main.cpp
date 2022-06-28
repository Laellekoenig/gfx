#include <raylib.h>
#include "lib/mesh.h"
#include <iostream>

PyramidMesh mesh;
float theta = 0.015;
M4D rotate;

void init() {
    mesh = PyramidMesh();
    M4D transform = ScalingM4D(200, 200, 200) * TranslationM4D(-0.5, -0.5, -0.5);
    mesh *= transform;
    rotate = RotationM4D(theta, Y);
}

void update() {
    mesh *= rotate;
}

void render() {
    BeginDrawing();
    ClearBackground((Color) {0, 0, 0, 255});
    mesh.render();
    DrawFPS(0, 0);
    EndDrawing();
}

void destroy() {

}

int main(int argc, char* argv[]) {
    InitWindow(WIDTH, HEIGHT, "gfx++");
    SetTargetFPS(60);

    init();

    while (!WindowShouldClose()) {
        update();
        render();
    }

    CloseWindow();
    destroy();

    return 0;
}
