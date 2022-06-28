#include <raylib.h>
#include "lib/mesh.h"

TriMesh mesh;
float theta = 0.015;
M4D rotate_x;
M4D rotate_y;

void init() {
    //mesh = PyramidMesh();
    mesh = CubeMesh();
    M4D transform = ScalingM4D(200, 200, 200) * TranslationM4D(-0.5, -0.5, -0.5);
    mesh *= transform;

    rotate_x = RotationM4D(0.5 * theta, X);
    rotate_y = RotationM4D(theta, Y);
}

void update() {
    mesh *= rotate_x * rotate_y;
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
