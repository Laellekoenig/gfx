#ifndef MESH_H
#define MESH_H

#include <vector>
#include <SDL2/SDL.h>
#include "gfx.h"

class Mesh {
    public:
        std::vector<Triangle> mesh;

        Mesh();
        void add(Triangle t);
        void render(SDL_Renderer* renderer);
        void apply(const M4D& m);
};

class PyramidMesh: public Mesh {
    public:
        PyramidMesh();
};

class CubeMesh: public Mesh {
    public:
        CubeMesh();
};

#endif // MESH_H
