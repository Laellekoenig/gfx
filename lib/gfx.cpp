#include "gfx.h"
#include <math.h>

V3D::V3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

V3D::V3D(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void V3D::translate_origin() {
    this->x *= -1;
    this->y *= -1;
    this->x += WIDTH * 0.5;
    this->y += HEIGHT * 0.5;
}

void V3D::operator/=(const float x) {
    this->x /= x;
    this->y /= x;
    this->z /= x;
}

V4D::V4D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = 1;
}

V4D::V4D(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

V3D V4D::dehomo() {
    V3D o = V3D(this->x, this->y, this->z);
    if (this->w != 0) {
        o /= this->w;
    }
    return o;
}

M4D::M4D() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->m[i][j] = 0;
        }
    }
}

V4D M4D::operator*(const V4D& v) const {
    float x = v.x * this->m[0][0] + v.y * this->m[0][1] + v.z * this->m[0][2] + v.w * this->m[0][3];
    float y = v.x * this->m[1][0] + v.y * this->m[1][1] + v.z * this->m[1][2] + v.w * this->m[1][3];
    float z = v.x * this->m[2][0] + v.y * this->m[2][1] + v.z * this->m[2][2] + v.w * this->m[2][3];
    float w = v.x * this->m[3][0] + v.y * this->m[3][1] + v.z * this->m[3][2] + v.w * this->m[3][3];
    return V4D(x, y, z, w);
}

Triangle M4D::operator*(const Triangle& t) const {
    return Triangle(*this * t.a,
                    *this * t.b,
                    *this * t.c,
                    t.ca,
                    t.cb,
                    t.cc);
}

M4D M4D::operator*(const M4D& m) const {
    M4D o = M4D();

    o.m[0][0] = this->m[0][0] * m.m[0][0] + this->m[0][1] * m.m[1][0] + this->m[0][2] * m.m[2][0] + this->m[0][3] * m.m[3][0];
    o.m[0][1] = this->m[0][0] * m.m[0][1] + this->m[0][1] * m.m[1][1] + this->m[0][2] * m.m[2][1] + this->m[0][3] * m.m[3][1];
    o.m[0][2] = this->m[0][0] * m.m[0][2] + this->m[0][1] * m.m[1][2] + this->m[0][2] * m.m[2][2] + this->m[0][3] * m.m[3][2];
    o.m[0][3] = this->m[0][0] * m.m[0][3] + this->m[0][1] * m.m[1][3] + this->m[0][2] * m.m[2][3] + this->m[0][3] * m.m[3][3];

    o.m[1][0] = this->m[1][0] * m.m[0][0] + this->m[1][1] * m.m[1][0] + this->m[1][2] * m.m[2][0] + this->m[1][3] * m.m[3][0];
    o.m[1][1] = this->m[1][0] * m.m[0][1] + this->m[1][1] * m.m[1][1] + this->m[1][2] * m.m[2][1] + this->m[1][3] * m.m[3][1];
    o.m[1][2] = this->m[1][0] * m.m[0][2] + this->m[1][1] * m.m[1][2] + this->m[1][2] * m.m[2][2] + this->m[1][3] * m.m[3][2];
    o.m[1][3] = this->m[1][0] * m.m[0][3] + this->m[1][1] * m.m[1][3] + this->m[1][2] * m.m[2][3] + this->m[1][3] * m.m[3][3];

    o.m[2][0] = this->m[2][0] * m.m[0][0] + this->m[2][1] * m.m[1][0] + this->m[2][2] * m.m[2][0] + this->m[2][3] * m.m[3][0];
    o.m[2][1] = this->m[2][0] * m.m[0][1] + this->m[2][1] * m.m[1][1] + this->m[2][2] * m.m[2][1] + this->m[2][3] * m.m[3][1];
    o.m[2][2] = this->m[2][0] * m.m[0][2] + this->m[2][1] * m.m[1][2] + this->m[2][2] * m.m[2][2] + this->m[2][3] * m.m[3][2];
    o.m[2][3] = this->m[2][0] * m.m[0][3] + this->m[2][1] * m.m[1][3] + this->m[2][2] * m.m[2][3] + this->m[2][3] * m.m[3][3];

    o.m[3][0] = this->m[3][0] * m.m[0][0] + this->m[3][1] * m.m[1][0] + this->m[3][2] * m.m[2][0] + this->m[3][3] * m.m[3][0];
    o.m[3][1] = this->m[3][0] * m.m[0][1] + this->m[3][1] * m.m[1][1] + this->m[3][2] * m.m[2][1] + this->m[3][3] * m.m[3][1];
    o.m[3][2] = this->m[3][0] * m.m[0][2] + this->m[3][1] * m.m[1][2] + this->m[3][2] * m.m[2][2] + this->m[3][3] * m.m[3][2];
    o.m[3][3] = this->m[3][0] * m.m[0][3] + this->m[3][1] * m.m[1][3] + this->m[3][2] * m.m[2][3] + this->m[3][3] * m.m[3][3];

    return o;
}

TranslationM4D::TranslationM4D(float x, float y, float z) {
    this->m[0][0] = 1;
    this->m[1][1] = 1;
    this->m[2][2] = 1;
    this->m[3][3] = 1;
    this->m[0][3] = x;
    this->m[1][3] = y;
    this->m[2][3] = z;
}

ScalingM4D::ScalingM4D(float x, float y, float z) {
    this->m[0][0] = x;
    this->m[1][1] = y;
    this->m[2][2] = z;
}

RotationM4D::RotationM4D(float theta, int dir) {
    float cosTheta = cos(theta);
    float sinTheta = sin(theta);

    if (dir == X) {
        this->m[0][0] = 1;
        this->m[1][1] = cosTheta;
        this->m[1][2] = -sinTheta;
        this->m[2][1] = sinTheta;
        this->m[2][2] = cosTheta;
        this->m[3][3] = 1;

    } else if (dir == Y) {
        this->m[0][0] = cosTheta;
        this->m[0][2] = -sinTheta;
        this->m[1][1] = 1;
        this->m[2][0] = sinTheta;
        this->m[2][2] = cosTheta;
        this->m[3][3] = 1;

    } else if (dir == Z) {
        this->m[0][0] = cosTheta;
        this->m[0][1] = -sinTheta;
        this->m[1][0] = sinTheta;
        this->m[1][1] = cosTheta;
        this->m[2][2] = 1;
        this->m[3][3] = 1;
    }
}

ProjectionM4D::ProjectionM4D() {
    float f_near = 0.1;
    float f_far = 1000.0;
    float f_delta = f_far - f_near;
    float fov = 90.0;
    float fov_tan = 1.0 / tan(fov * 0.5 / 180.0 * PI);

    this->m[0][0] = (HEIGHT / WIDTH) * fov_tan;
    this->m[1][1] = fov_tan;
    this->m[2][2] = f_far / f_delta;
    this->m[3][2] = (-f_far * f_near) / f_delta;
    this->m[2][3] = 1;
    this->m[3][3] = 0;
}

Triangle::Triangle(V4D a, V4D b, V4D c) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->ca = (Color) {255, 255, 255, 255};
    this->cb = (Color) {255, 255, 255, 255};
    this->cc = (Color) {255, 255, 255, 255};
}

Triangle::Triangle(V4D a, V4D b, V4D c, Color ca, Color cb, Color cc) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->ca = ca;
    this->cb = cb;
    this->cc = cc;
}

void Triangle::render() {
    V3D a = this->a.dehomo();
    V3D b = this->b.dehomo();
    V3D c = this->c.dehomo();

    a.translate_origin();
    b.translate_origin();
    c.translate_origin();

    Color white = {255, 255, 255, 255};
    DrawLine(a.x, a.y, b.x, b.y, white);
    DrawLine(b.x, b.y, c.x, c.y, white);
    DrawLine(c.x, c.y, a.x, a.y, white);
}

void Triangle::render_projection() {
    M4D proj = ProjectionM4D();

    V4D a_proj = proj * this->a;
    V4D b_proj = proj * this->b;
    V4D c_proj = proj * this->c;

    V3D a = V3D(a_proj.x, a_proj.y, a_proj.z);
    V3D b = V3D(b_proj.x, b_proj.y, b_proj.z);
    V3D c = V3D(c_proj.x, c_proj.y, c_proj.z);

    a.translate_origin();
    b.translate_origin();
    c.translate_origin();

    Color white = {255, 255, 255, 255};
    DrawLine(a.x, a.y, b.x, b.y, white);
    DrawLine(b.x, b.y, c.x, c.y, white);
    DrawLine(c.x, c.y, a.x, a.y, white);
}

