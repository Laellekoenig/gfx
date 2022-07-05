#include "mesh.hpp"
#include "gfx.hpp"

Mesh::Mesh() {
    mesh = std::vector<Triangle>();
}

void Mesh::add(Triangle t) {
    mesh.emplace_back(t);
}

void Mesh::render(Image& img) {
    for (Triangle t : mesh)
        t.render(img);
}

void Mesh::render_threaded(Image& img) {
    std::vector<std::thread> pool(10);

    for (uint i = 0; i < mesh.size(); i++)
        pool.emplace_back(std::thread(&Triangle::render, mesh[i], std::ref(img)));

    for (auto& th : pool)
        if (th.joinable())
            th.join();
}

void Mesh::apply(const M4D& m) {
    for (Triangle& t : mesh) t = m * t;
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
