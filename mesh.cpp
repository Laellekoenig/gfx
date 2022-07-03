#include "mesh.h"
#include <limits>
#include <array>

Mesh::Mesh() {
    mesh = std::vector<Triangle>();
}

void Mesh::add(Triangle t) {
    mesh.emplace_back(t);
}

void Mesh::render(SDL_Renderer* renderer) {
    std::array<float, WIDTH * HEIGHT> z_buffer;
    z_buffer.fill(FLT_MAX);

    for (Triangle t : mesh) {
        t.render(renderer, z_buffer);
    }
}

void Mesh::apply(const M4D& m) {
    for (std::vector<Triangle>::iterator it = mesh.begin(); it != mesh.end(); it++) {
        *it = m * (*it);
    }
}

PyramidMesh::PyramidMesh() {
    mesh.reserve(6);

    // sides
    mesh.emplace_back(Triangle(V4D(0, 0, 0), V4D(0.5, 1, 0.5), V4D(1, 0, 0),
                               RED, WHITE, GREEN));
    mesh.emplace_back(Triangle(V4D(0, 0, 1), V4D(0.5, 1, 0.5), V4D(0, 0, 0),
                               BLUE, WHITE, RED));
    mesh.emplace_back(Triangle(V4D(1, 0, 1), V4D(0.5, 1, 0.5), V4D(0, 0, 1),
                               WHITE, WHITE, BLUE));
    mesh.emplace_back(Triangle(V4D(1, 0, 0), V4D(0.5, 1, 0.5), V4D(1, 0, 1),
                               GREEN, WHITE, WHITE));

    // bottom
    mesh.emplace_back(Triangle(V4D(0, 0, 0), V4D(1, 0, 0), V4D(0, 0, 1),
                               RED, GREEN, BLUE));
    mesh.emplace_back(Triangle(V4D(1, 0, 1), V4D(0, 0, 1), V4D(1, 0, 0),
                               WHITE, BLUE, GREEN));
}

CubeMesh::CubeMesh() {
    mesh.reserve(12);

    // front
    mesh.emplace_back(Triangle(V4D(0, 0, 0), V4D(0, 1, 0), V4D(1, 1, 0),
                               RED, GREEN, BLUE));
    mesh.emplace_back(Triangle(V4D(0, 0, 0), V4D(1, 1, 0), V4D(1, 0, 0),
                               RED, BLUE, WHITE));

    // left
    mesh.emplace_back(Triangle(V4D(0, 0, 1), V4D(0, 1, 1), V4D(0, 1, 0),
                               WHITE, WHITE, GREEN));
    mesh.emplace_back(Triangle(V4D(0, 0, 1), V4D(0, 1, 0), V4D(0, 0, 0),
                               WHITE, GREEN, RED));

    // right
    mesh.emplace_back(Triangle(V4D(1, 0, 0), V4D(1, 1, 0), V4D(1, 1, 1),
                               WHITE, BLUE, WHITE));
    mesh.emplace_back(Triangle(V4D(1, 0, 0), V4D(1, 1, 1), V4D(1, 0, 1),
                               WHITE, WHITE, WHITE));

    // back
    mesh.emplace_back(Triangle(V4D(1, 0, 1), V4D(1, 1, 1), V4D(0, 1, 1),
                               WHITE, WHITE, WHITE));
    mesh.emplace_back(Triangle(V4D(1, 0, 1), V4D(0, 1, 1), V4D(0, 0, 1),
                               WHITE, WHITE, WHITE));

    // top
    mesh.emplace_back(Triangle(V4D(0, 1, 0), V4D(0, 1, 1), V4D(1, 1, 1),
                               GREEN, WHITE, WHITE));
    mesh.emplace_back(Triangle(V4D(0, 1, 0), V4D(1, 1, 1), V4D(1, 1, 0),
                               GREEN, WHITE, BLUE));

    // bottom
    mesh.emplace_back(Triangle(V4D(0, 0, 0), V4D(1, 0, 1), V4D(0, 0, 1),
                               RED, WHITE, WHITE));
    mesh.emplace_back(Triangle(V4D(0, 0, 0), V4D(1, 0, 0), V4D(1, 0, 1),
                               RED, WHITE, WHITE));
}
