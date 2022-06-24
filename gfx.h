#ifndef GFX_H
#define GFX_H

#include "linalg.h"
#include "mesh.h"
#include "shapes.h"
#include <math.h>

#define WIDTH 400
#define HEIGHT 400

void translateOrigin(V3D* v) {
    v->f[0] *= -1;
    v->f[1] *= -1;

    v->f[0] += WIDTH * 0.5;
    v->f[1] += HEIGHT * 0.5;
}

int pointInTriangle(V2D* p1, V2D* p2, V2D* p3, int x, int y) {
    V2D r = {{x - p3->f[0], y - p3->f[1]}};
    Mat2D t = {};
    cart2bar(p1, p2, p3, &t);
    invMat2D(&t, &t);

    V2D lambdas = {};
    multM2DV2D(&t, &r, &lambdas);
    
    float l1 = lambdas.f[0];
    if (l1 < 0) return 0;
    float l2 = lambdas.f[1];
    if (l2 < 0) return 0;
    float l3 = 1 - l1 - l2;
    if (l3 < 0) return 0;

    return 1;
}

void draw2DTri(HomoTri* tri) {
    V3D v[3] = {};
    for (int i = 0; i < 3; i++) {
        dehomo(&tri->v[i], &v[i]);
        translateOrigin(&v[i]);
    }

    // find bounding box
    float minX = v[0].f[0];
    if (minX > v[1].f[0]) minX = v[1].f[0];
    if (minX > v[2].f[0]) minX = v[2].f[0];

    float maxX = v[0].f[0];
    if (maxX < v[1].f[0]) maxX = v[1].f[0];
    if (maxX < v[2].f[0]) maxX = v[2].f[0];

    float minY = v[0].f[1];
    if (minY > v[1].f[1]) minY = v[1].f[1];
    if (minY > v[2].f[1]) minY = v[2].f[1];

    float maxY = v[0].f[1];
    if (maxY < v[1].f[1]) maxY = v[1].f[1];
    if (maxY < v[2].f[1]) maxY = v[2].f[1];

    DrawLine(v[0].f[0], v[0].f[1], v[1].f[0], v[1].f[1], RED);
    DrawLine(v[1].f[0], v[1].f[1], v[2].f[0], v[2].f[1], RED);
    DrawLine(v[2].f[0], v[2].f[1], v[0].f[0], v[0].f[1], RED);

    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            if (pointInTriangle((V2D*) &v[0], (V2D*) &v[1], (V2D*) &v[2], x, y)) {
                DrawPixel(x, y, WHITE);
            }
        }
    }
}

void drawMesh(VoidMesh* mesh) {
    VoidEntry* current = mesh->head;
    while (current != NULL) {
        draw2DTri((HomoTri*) current->item);
        current = current->next;
    }
}

#endif /* GFX_H */
