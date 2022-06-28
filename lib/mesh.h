#ifndef MESH_H
#define MESH_H

#include <vector>
#include "gfx.h"

class TriMesh {
    public:
        std::vector<Triangle> mesh;

        TriMesh();
        void add(Triangle t);
        void render();
        void render_projection();
        void operator*=(const M4D& m);
};

class PyramidMesh: public TriMesh {
    public:
        PyramidMesh();
};

class CubeMesh: public TriMesh {
    public:
        CubeMesh();
};

#endif // MESH_H
