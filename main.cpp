#include "gfx/linalg.hpp"
#include "sdl2/SDL2/SDL.h"
#include "gfx/pch.hpp"
#include "gfx/gfx.hpp"
#include "gfx/mesh.hpp"
#include <cfloat>

#define INTERVAL 16 // ~60 FPS

SDL_Renderer* renderer;
SDL_Window* window;
unsigned int next_tick;
Mesh pyramid;
Mesh cube;
float theta;
float theta2;
Image img;

void init() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    theta = theta2 = 0;
}

void update() {
    pyramid = PyramidMesh();
    M4D transform = ScalingM4D(200, 200, 200) *
                    RotationM4D(theta, Direction::Y) *
                    RotationM4D(theta2, Direction::X) *
                    TranslationM4D(-0.5, -0.5, -0.5);
    pyramid.apply(transform);
    theta += 0.025;
    theta2 += 0.0125;
    if (theta > 2 * M_PI) theta = 0;
    if (theta2 > 2 * M_PI) theta2 = 0;

    cube = CubeMesh();
    M4D transform2 = ScalingM4D(50, 50, 50) *
                     RotationM4D(theta, Direction::Y) *
                     TranslationM4D(2, 2, 0);
    cube.apply(transform2);
}

void render(SDL_Renderer* renderer) {

    cube.render(img);
    pyramid.render(img);
    //pyramid.render_threaded(img);

    // display
    img.draw(renderer);

    // reset image
    img.reset();
}

unsigned int time_left() {
    int now = SDL_GetTicks();
    if (next_tick <= now) return 0;
    return next_tick - now;
}

int main(int argc, char* argv[]) {
    init();

    SDL_Event event;
    next_tick = SDL_GetTicks() + INTERVAL;
    while (true) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT) break;
        update();
        render(renderer);
        SDL_Delay(time_left());
        next_tick += INTERVAL;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
