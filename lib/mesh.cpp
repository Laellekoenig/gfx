#include "mesh.h"

TriMesh::TriMesh() {
    this->mesh = std::vector<Triangle>();
}

void TriMesh::add(Triangle t) {
    this->mesh.push_back(t);
}

void TriMesh::render() {
    for (std::vector<Triangle>::iterator it = this->mesh.begin();
            it != this->mesh.end(); ++it) {
        it->render();
    }
}

void TriMesh::render_projection() {
    for (std::vector<Triangle>::iterator it = this->mesh.begin();
            it != this->mesh.end(); ++it) {
        it->render_projection();
    }
}

void TriMesh::operator*=(const M4D& m) {
    for (std::vector<Triangle>::iterator it = this->mesh.begin();
            it != this->mesh.end(); ++it) {
        *it = m * (*it);
    }
}

PyramidMesh::PyramidMesh() {
    Color white = {255, 255, 255, 255};

    // sides
    this->mesh.push_back(Triangle(V4D(0, 0, 0), V4D(0.5, 1, 0.5), V4D(1, 0, 0),
                                  white, white, white));
    this->mesh.push_back(Triangle(V4D(0, 0, 1), V4D(0.5, 1, 0.5), V4D(0, 0, 0),
                                  white, white, white));
    this->mesh.push_back(Triangle(V4D(1, 0, 1), V4D(0.5, 1, 0.5), V4D(0, 0, 1),
                                  white, white, white));
    this->mesh.push_back(Triangle(V4D(1, 0, 0), V4D(0.5, 1, 0.5), V4D(1, 0, 1),
                                  white, white, white));

    // bottom
    this->mesh.push_back(Triangle(V4D(0, 0, 0), V4D(1, 0, 0), V4D(0, 0, 1),
                                  white, white, white));
    this->mesh.push_back(Triangle(V4D(1, 0, 1), V4D(0, 0, 1), V4D(1, 0, 0),
                                  white, white, white));
}

CubeMesh::CubeMesh() {
    Color white = {255, 255, 255, 255};

    // front
    this->mesh.push_back(Triangle(V4D(0, 0, 0), V4D(0, 1, 0), V4D(1, 1, 0),
                                  white, white, white));
    this->mesh.push_back(Triangle(V4D(0, 0, 0), V4D(1, 1, 0), V4D(1, 0, 0),
                                  white, white, white));

    // left
    this->mesh.push_back(Triangle(V4D(0, 0, 1), V4D(0, 1, 1), V4D(0, 1, 0),
                                  white, white, white));
    this->mesh.push_back(Triangle(V4D(0, 0, 1), V4D(0, 1, 0), V4D(0, 0, 0),
                                  white, white, white));

    // right
    this->mesh.push_back(Triangle(V4D(1, 0, 0), V4D(1, 1, 0), V4D(1, 1, 1),
                                  white, white, white));
    this->mesh.push_back(Triangle(V4D(1, 0, 0), V4D(1, 1, 1), V4D(1, 0, 1),
                                  white, white, white));

    // back
    this->mesh.push_back(Triangle(V4D(1, 0, 1), V4D(1, 1, 1), V4D(0, 1, 1),
                                  white, white, white));
    this->mesh.push_back(Triangle(V4D(1, 0, 1), V4D(0, 1, 1), V4D(0, 0, 1),
                                  white, white, white));

    // top
    this->mesh.push_back(Triangle(V4D(0, 1, 0), V4D(0, 1, 1), V4D(1, 1, 1),
                                  white, white, white));
    this->mesh.push_back(Triangle(V4D(0, 1, 0), V4D(1, 1, 1), V4D(1, 1, 0),
                                  white, white, white));

    // bottom
    this->mesh.push_back(Triangle(V4D(0, 0, 0), V4D(1, 0, 1), V4D(0, 0, 1),
                                  white, white, white));
    this->mesh.push_back(Triangle(V4D(0, 0, 0), V4D(1, 0, 0), V4D(1, 0, 1),
                                  white, white, white));
}
