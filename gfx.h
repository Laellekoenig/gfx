#ifndef GFX_H
#define GFX_H

#include "linalg.h"
#include "mesh.h"
#include "shapes.h"
#include <math.h>
#include <float.h>

#define WIDTH 400
#define HEIGHT 400

void translateOrigin(V3D* v) {
    v->f[0] *= -1;
    v->f[1] *= -1;

    v->f[0] += WIDTH * 0.5;
    v->f[1] += HEIGHT * 0.5;
}

V3D toBarycentric(V2D* p1, V2D* p2, V2D* p3, V2D* x) {
    V2D r = {{x->f[0] - p3->f[0], x->f[1] - p3->f[1]}};
    Mat2D t = {};
    cart2bar(p1, p2, p3, &t);
    invMat2D(&t, &t);

    // check for NAN values (division from inverse)
    if (t.m[0][0] != t.m[0][0]) return (V3D) {{-1, -1, -1}};

    V2D lambdas = {};
    multM2DV2D(&t, &r, &lambdas);
    
    float l1 = lambdas.f[0];
    float l2 = lambdas.f[1];
    float l3 = 1 - l1 - l2;

    return (V3D) {{l1, l2, l3}};
}

void draw2DTri(HomoTri* tri, Color (*img)[WIDTH], float (*zBuff)[WIDTH]) {
    V3D v[3] = {};
    for (int i = 0; i < 3; i++) {
        dehomo(&tri->v[i], &v[i]);
        translateOrigin(&v[i]);
    }

    float avgZ = (v[0].f[2] + v[1].f[2] + v[2].f[2]) / 3.0f;

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

    //DrawLine(v[0].f[0], v[0].f[1], v[1].f[0], v[1].f[1], RED);
    //DrawLine(v[1].f[0], v[1].f[1], v[2].f[0], v[2].f[1], RED);
    //DrawLine(v[2].f[0], v[2].f[1], v[0].f[0], v[0].f[1], RED);

    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {

            // transform point to barycentric coordinates
            V2D point = {{x, y}};
            V3D bar = toBarycentric((V2D*) &v[0],
                                    (V2D*) &v[1],
                                    (V2D*) &v[2],
                                    &point);

            // check if point is in triangle
            if (bar.f[0] < 0 || bar.f[1] < 0 || bar.f[2] < 0) continue;

            // z buffer
            float z = bar.f[0] * v[0].f[2] + bar.f[1] * v[1].f[2] + bar.f[2] * v[2].f[2];
            if (z > zBuff[x][y]) continue;
            zBuff[x][y] = z;

            // interpolate and set color
            V3D col = {{255, 255, 255}};
            multElementV3D(&bar, &col, &col);
            img[x][y] = (Color) {col.f[0], col.f[1], col.f[2], 255};
        }
    }
}

void drawImg(Color (*img)[WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            DrawPixel(x, y, img[x][y]);
        }
    }
}

void drawMesh(VoidMesh* mesh) {
    Color img[HEIGHT][WIDTH] = {0};
    float zBuff[HEIGHT][WIDTH] = {};
    // TODO: improve this
    memset(zBuff, 100, sizeof(float) * HEIGHT * WIDTH);

    VoidEntry* current = mesh->head;
    while (current != NULL) {
        draw2DTri((HomoTri*) current->item, img, zBuff);
        current = current->next;
    }

    drawImg(img);
}

#endif /* GFX_H */
