#ifndef SHAPES_H
#define SHAPES_H

#include <stdlib.h>
#include "mesh.h"

void pyramidMesh(VoidMesh* mesh) {
    // sides
    HomoTri* a = malloc(sizeof(HomoTri));
    *a = (HomoTri) {{{0, 0, 0, 1}, {0.5, 1, 0.5, 1}, {1, 0, 0, 1}},
                    {RED, WHITE, GREEN}};

    HomoTri* b = malloc(sizeof(HomoTri));
    *b = (HomoTri) {{{0, 0, 1, 1}, {0.5, 1, 0.5, 1}, {0, 0, 0, 1}},
                    {WHITE, WHITE, RED}};

    HomoTri* c = malloc(sizeof(HomoTri));
    *c = (HomoTri) {{{1, 0, 1, 1}, {0.5, 1, 0.5, 1}, {0, 0, 1, 1}},
                    {BLUE, WHITE, WHITE}};

    HomoTri* d = malloc(sizeof(HomoTri));
    *d = (HomoTri) {{{1, 0, 0, 1}, {0.5, 1, 0.5, 1}, {1, 0, 1, 1}},
                    {GREEN, WHITE, BLUE}};

    //base
    HomoTri* e = malloc(sizeof(HomoTri));
    *e = (HomoTri) {{{0, 0, 0, 1}, {1, 0, 0, 1}, {0, 0, 1, 1}},
                    {RED, GREEN, WHITE}};

    HomoTri* f = malloc(sizeof(HomoTri));
    *f = (HomoTri) {{{1, 0, 1, 1}, {0, 0, 1, 1}, {1, 0, 0, 1}},
                    {BLUE, WHITE, GREEN}};

    add2Mesh(mesh, (void*) a);
    add2Mesh(mesh, (void*) b);
    add2Mesh(mesh, (void*) c);
    add2Mesh(mesh, (void*) d);
    add2Mesh(mesh, (void*) e);
    add2Mesh(mesh, (void*) f);
}

#endif /* SHAPES_H */
