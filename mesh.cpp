#include "mesh.h"
#include <limits>
#include <array>

Mesh::Mesh() {
    mesh = std::vector<Triangle>();
}

void Mesh::add(Triangle t) {
    mesh.push_back(t);
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
    RGB red = RGB(255, 0, 0);
    RGB green = RGB(0, 255, 0);
    RGB blue = RGB(0, 0, 255);
    RGB white = RGB(255, 255, 255);

    // sides
    this->mesh.push_back(Triangle(V4D(0, 0, 0), V4D(0.5, 1, 0.5), V4D(1, 0, 0),
                                  red, white, green));
    this->mesh.push_back(Triangle(V4D(0, 0, 1), V4D(0.5, 1, 0.5), V4D(0, 0, 0),
                                  blue, white, red));
    this->mesh.push_back(Triangle(V4D(1, 0, 1), V4D(0.5, 1, 0.5), V4D(0, 0, 1),
                                  white, white, blue));
    this->mesh.push_back(Triangle(V4D(1, 0, 0), V4D(0.5, 1, 0.5), V4D(1, 0, 1),
                                  green, white, white));

    // bottom
    this->mesh.push_back(Triangle(V4D(0, 0, 0), V4D(1, 0, 0), V4D(0, 0, 1),
                                  red, green, blue));
    this->mesh.push_back(Triangle(V4D(1, 0, 1), V4D(0, 0, 1), V4D(1, 0, 0),
                                  white, blue, green));
}

CubeMesh::CubeMesh() {
    RGB red = RGB(255, 0, 0);
    RGB green = RGB(0, 255, 0);
    RGB blue = RGB(0, 0, 255);
    RGB white = RGB(255, 255, 255);

    // front
    this->mesh.push_back(Triangle(V4D(0, 0, 0), V4D(0, 1, 0), V4D(1, 1, 0),
                                  red, green, blue));
    this->mesh.push_back(Triangle(V4D(0, 0, 0), V4D(1, 1, 0), V4D(1, 0, 0),
                                  red, blue, white));

    // left
    this->mesh.push_back(Triangle(V4D(0, 0, 1), V4D(0, 1, 1), V4D(0, 1, 0),
                                  white, white, green));
    this->mesh.push_back(Triangle(V4D(0, 0, 1), V4D(0, 1, 0), V4D(0, 0, 0),
                                  white, green, red));

    // right
    this->mesh.push_back(Triangle(V4D(1, 0, 0), V4D(1, 1, 0), V4D(1, 1, 1),
                                  white, blue, white));
    this->mesh.push_back(Triangle(V4D(1, 0, 0), V4D(1, 1, 1), V4D(1, 0, 1),
                                  white, white, white));

    // back
    this->mesh.push_back(Triangle(V4D(1, 0, 1), V4D(1, 1, 1), V4D(0, 1, 1),
                                  white, white, white));
    this->mesh.push_back(Triangle(V4D(1, 0, 1), V4D(0, 1, 1), V4D(0, 0, 1),
                                  white, white, white));

    // top
    this->mesh.push_back(Triangle(V4D(0, 1, 0), V4D(0, 1, 1), V4D(1, 1, 1),
                                  green, white, white));
    this->mesh.push_back(Triangle(V4D(0, 1, 0), V4D(1, 1, 1), V4D(1, 1, 0),
                                  green, white, blue));

    // bottom
    this->mesh.push_back(Triangle(V4D(0, 0, 0), V4D(1, 0, 1), V4D(0, 0, 1),
                                  red, white, white));
    this->mesh.push_back(Triangle(V4D(0, 0, 0), V4D(1, 0, 0), V4D(1, 0, 1),
                                  red, white, white));
}
