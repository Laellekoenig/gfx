#include <SDL2/SDL.h>
#include "gfx.h"
#include "mesh.h"
#include <math.h>

#define INTERVAL 16 // ~60 FPS

SDL_Renderer* renderer;
SDL_Window* window;
unsigned int next_tick;
Mesh pyramid;
float theta;

void init() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    theta = 0;
}

void update() {
    pyramid = PyramidMesh();
    M4D transform = ScalingM4D(200, 200, 200) *
                    RotationM4D(theta, Direction::Y) *
                    TranslationM4D(-0.5, -0.5, -0.5);
    pyramid.apply(transform);
    theta += 0.025;
    if (theta > 2 * M_PI) theta = 0;
}

void render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    pyramid.render(renderer);
    SDL_RenderPresent(renderer);
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
