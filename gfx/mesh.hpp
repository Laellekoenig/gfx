#ifndef MESH_H
#define MESH_H

#include "../sdl2/SDL2/SDL.h"
#include "pch.hpp"
#include "gfx.hpp"

class Mesh {
    public:
        std::vector<Triangle> mesh;

        Mesh();
        void add(Triangle t);
        void render(Image& img);
        void render_threaded(Image& img);
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
