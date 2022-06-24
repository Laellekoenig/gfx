#ifndef LINALG_H
#define LINALG_H

#include <string.h>
#include <math.h>

typedef struct {
    float f[3];
} V3D;

typedef struct {
    float f[4];
} V4D;

typedef struct {
    float m[4][4];
} Mat4D;

void dehomo(V4D* v, V3D* o) {
    if (v->f[3] != 0) {
        v->f[0] /= v->f[3];
        v->f[1] /= v->f[3];
        v->f[2] /= v->f[3];
    }

    o->f[0] = v->f[0];
    o->f[1] = v->f[1];
    o->f[2] = v->f[2];
}

void translationMat(Mat4D* m, float x, float y, float z) {
    memset(m, 0, sizeof(Mat4D));

    m->m[0][0] = 1;
    m->m[1][1] = 1;
    m->m[2][2] = 1;
    m->m[3][3] = 1;
    m->m[0][3] = x;
    m->m[1][3] = y;
    m->m[2][3] = z;
}

void xRotationMat(Mat4D* m, float theta) {
    memset(m, 0, sizeof(Mat4D));

    float cosTheta = cos(theta);
    float sinTheta = sin(theta);

    m->m[0][0] = 1;
    m->m[1][1] = cosTheta;
    m->m[1][2] = -sinTheta;
    m->m[2][1] = sinTheta;
    m->m[2][2] = cosTheta;
    m->m[3][3] = 1;
}

void yRotationMat(Mat4D* m, float theta) {
    memset(m, 0, sizeof(Mat4D));

    float cosTheta = cos(theta);
    float sinTheta = sin(theta);

    m->m[0][0] = cosTheta;
    m->m[0][2] = -sinTheta;
    m->m[1][1] = 1;
    m->m[2][0] = sinTheta;
    m->m[2][2] = cosTheta;
    m->m[3][3] = 1;
}

void zRotationMat(Mat4D* m, float theta) {
    memset(m, 0, sizeof(Mat4D));

    float cosTheta = cos(theta);
    float sinTheta = sin(theta);

    m->m[0][0] = cosTheta;
    m->m[0][1] = -sinTheta;
    m->m[1][0] = sinTheta;
    m->m[1][1] = cosTheta;
    m->m[2][2] = 1;
    m->m[3][3] = 1;
}

void scalingMat(Mat4D* m, float x, float y, float z) {
    memset(m, 0, sizeof(Mat4D));

    m->m[0][0] = x;
    m->m[1][1] = y;
    m->m[2][2] = z;
}

void projectionMat(Mat4D* m, float width, float height) {
    memset(m, 0, sizeof(Mat4D));

    float fNear = 0.1;
    float fFar = 1000;
    float fov = 90 / 180 * PI;

    float fovTan = 1 / tan(fov * 0.5);

    m->m[0][0] = (height / width) * fovTan;
    m->m[1][1] = fovTan;
    m->m[2][2] = fFar / (fFar - fNear);
    m->m[3][2] = (-fFar * fNear) / (fFar - fNear);
    m->m[2][3] = 1;
}

void multMV4(Mat4D* m, V4D* v, V4D* o) {
    o->f[0] = v->f[0] * m->m[0][0] + v->f[1] * m->m[0][1] + v->f[2] * m->m[0][2] + v->f[3] * m->m[0][3];
    o->f[1] = v->f[0] * m->m[1][0] + v->f[1] * m->m[1][1] + v->f[2] * m->m[1][2] + v->f[3] * m->m[1][3];
    o->f[2] = v->f[0] * m->m[2][0] + v->f[1] * m->m[2][1] + v->f[2] * m->m[2][2] + v->f[3] * m->m[2][3];
    o->f[3] = v->f[0] * m->m[3][0] + v->f[1] * m->m[3][1] + v->f[2] * m->m[3][2] + v->f[3] * m->m[3][3];
}

void multMM4(Mat4D* m, Mat4D* m2, Mat4D* o) {
    Mat4D temp = {0};
    temp.m[0][0] = m->m[0][0] * m2->m[0][0] + m->m[0][1] * m2->m[1][0] + m->m[0][2] * m2->m[2][0] + m->m[0][3] * m2->m[3][0];
    temp.m[0][1] = m->m[0][0] * m2->m[0][1] + m->m[0][1] * m2->m[1][1] + m->m[0][2] * m2->m[2][1] + m->m[0][3] * m2->m[3][1];
    temp.m[0][2] = m->m[0][0] * m2->m[0][2] + m->m[0][1] * m2->m[1][2] + m->m[0][2] * m2->m[2][2] + m->m[0][3] * m2->m[3][2];
    temp.m[0][3] = m->m[0][0] * m2->m[0][3] + m->m[0][1] * m2->m[1][3] + m->m[0][2] * m2->m[2][3] + m->m[0][3] * m2->m[3][3];

    temp.m[1][0] = m->m[1][0] * m2->m[0][0] + m->m[1][1] * m2->m[1][0] + m->m[1][2] * m2->m[2][0] + m->m[1][3] * m2->m[3][0];
    temp.m[1][1] = m->m[1][0] * m2->m[0][1] + m->m[1][1] * m2->m[1][1] + m->m[1][2] * m2->m[2][1] + m->m[1][3] * m2->m[3][1];
    temp.m[1][2] = m->m[1][0] * m2->m[0][2] + m->m[1][1] * m2->m[1][2] + m->m[1][2] * m2->m[2][2] + m->m[1][3] * m2->m[3][2];
    temp.m[1][3] = m->m[1][0] * m2->m[0][3] + m->m[1][1] * m2->m[1][3] + m->m[1][2] * m2->m[2][3] + m->m[1][3] * m2->m[3][3];

    temp.m[2][0] = m->m[2][0] * m2->m[0][0] + m->m[2][1] * m2->m[1][0] + m->m[2][2] * m2->m[2][0] + m->m[2][3] * m2->m[3][0];
    temp.m[2][1] = m->m[2][0] * m2->m[0][1] + m->m[2][1] * m2->m[1][1] + m->m[2][2] * m2->m[2][1] + m->m[2][3] * m2->m[3][1];
    temp.m[2][2] = m->m[2][0] * m2->m[0][2] + m->m[2][1] * m2->m[1][2] + m->m[2][2] * m2->m[2][2] + m->m[2][3] * m2->m[3][2];
    temp.m[2][3] = m->m[2][0] * m2->m[0][3] + m->m[2][1] * m2->m[1][3] + m->m[2][2] * m2->m[2][3] + m->m[2][3] * m2->m[3][3];

    temp.m[3][0] = m->m[3][0] * m2->m[0][0] + m->m[3][1] * m2->m[1][0] + m->m[3][2] * m2->m[2][0] + m->m[3][3] * m2->m[3][0];
    temp.m[3][1] = m->m[3][0] * m2->m[0][1] + m->m[3][1] * m2->m[1][1] + m->m[3][2] * m2->m[2][1] + m->m[3][3] * m2->m[3][1];
    temp.m[3][2] = m->m[3][0] * m2->m[0][2] + m->m[3][1] * m2->m[1][2] + m->m[3][2] * m2->m[2][2] + m->m[3][3] * m2->m[3][2];
    temp.m[3][3] = m->m[3][0] * m2->m[0][3] + m->m[3][1] * m2->m[1][3] + m->m[3][2] * m2->m[2][3] + m->m[3][3] * m2->m[3][3];

    *o = temp;
}

typedef struct {
    float f[2];
} V2D;

typedef struct {
    float m[2][2];
} Mat2D;

void cart2bar(V2D* v1, V2D* v2, V2D* v3, Mat2D* m) {
    m->m[0][0] = v1->f[0] - v3->f[0];
    m->m[0][1] = v2->f[0] - v3->f[0];
    m->m[1][0] = v1->f[1] - v3->f[1];
    m->m[1][1] = v2->f[1] - v3->f[1];
}

float detMat2D(Mat2D* m) {
    return m->m[0][0] * m->m[1][1] - m->m[0][1] * m->m[1][0];
}

void invMat2D(Mat2D* m, Mat2D* o) {
    Mat2D inv = {0};
    float invDet = 1.0 / detMat2D(m);
    inv.m[0][0] = invDet * m->m[1][1];
    inv.m[0][1] = invDet * (-1.0f) * m->m[0][1];
    inv.m[1][0] = invDet * (-1.0f) * m->m[1][0];
    inv.m[1][1] = invDet * m->m[0][0];
    *o = inv;
}

void subV2D(V2D* v1, V2D* v2, V2D* o) {
    o->f[0] = v1->f[0] - v2->f[0];
    o->f[1] = v1->f[1] - v2->f[1];
}

void multM2DV2D(Mat2D* m, V2D* v, V2D* o) {
    o->f[0] = m->m[0][0] * v->f[0] + m->m[0][1] * v->f[1];
    o->f[1] = m->m[1][0] * v->f[0] + m->m[1][1] * v->f[1];
}

#endif /* LINALG_H */
