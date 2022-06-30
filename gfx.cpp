#include "gfx.h"
#include <math.h>
#include <limits.h>

RGB::RGB() {
    this->r = 0xFF;
    this->g = 0xFF;
    this->b = 0xFF;
}

RGB::RGB(unsigned char r, unsigned char g, unsigned char b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

RGB RGB::operator*(const float& x) const {
    return RGB(this->r * x,
               this->g * x,
               this->b * x);
}

RGB RGB::operator+(const RGB& other) const {
    return RGB(this->r + other.r,
               this->g + other.g,
               this->b + other.b);
}

V2D::V2D() {
    this->x = 0;
    this->y = 0;
}

V2D::V2D(float x, float y) {
    this->x = x;
    this->y = y;
}

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

void V4D::dehomo() {
    if (this->w != 0) {
        this->x /= this->w;
        this->y /= this->w;
        this->z /= this->w;
    }
}

void V4D::translate_origin() {
    this->x *= -1;
    this->y *= -1;
    this->x += WIDTH * 0.5;
    this->y += HEIGHT * 0.5;
}

M2D::M2D() {
    this->a = 0;
    this->b = 0;
    this->c = 0;
    this->d = 0;
}

M2D::M2D(float a, float b, float c, float d) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}

float M2D::det() {
    return this->a * this->d - this->b * this->c;
}

void M2D::inv() {
    float det = this->det();

    if (det == 0) {
        this->a = NAN;
        this->b = NAN;
        this->c = NAN;
        this->d = NAN;
        return;
    }

    det = 1.0 / det;
    *this = M2D(det * this->d, -1 * det * this->b,
                -1 * det * this->c, det * this->a);
}

V2D M2D::operator*(const V2D& v) const {
    return V2D(this->a * v.x + this->b * v.y,
               this->c * v.x + this->d * v.y);
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
    float fov_tan = 1.0 / tan(fov * 0.5 / 180.0 * M_PI);

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
    this->ca = RGB(255, 255, 255);
    this->cb = RGB(255, 255, 255);
    this->cc = RGB(255, 255, 255);
}

Triangle::Triangle(V4D a, V4D b, V4D c, RGB ca, RGB cb, RGB cc) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->ca = ca;
    this->cb = cb;
    this->cc = cc;
}

void Triangle::render(SDL_Renderer* renderer,
                      std::array<float, WIDTH * HEIGHT>& z_buffer) {
    this->a.dehomo();
    this->b.dehomo();
    this->c.dehomo();

    this->a.translate_origin();
    this->b.translate_origin();
    this->c.translate_origin();

    float min_x = fmin(this->a.x, fmin(this->b.x, this->c.x));
    float max_x = fmax(this->a.x, fmax(this->b.x, this->c.x));
    float min_y = fmin(this->a.y, fmin(this->b.y, this->c.y));
    float max_y = fmax(this->a.y, fmax(this->b.y, this->c.y));

    for (int y = min_y; y <= max_y; y++) {
        for (int x = min_x; x <= max_x; x++) {
            V3D bar = this->to_barycentric(V2D(x, y));
            if (bar.x < 0 || bar.y < 0 || bar.z < 0) continue;
            RGB color = this->ca * bar.x + this->cb * bar.y + this->cc * bar.z;
            float z = this->a.z * bar.x + this->b.z * bar.y + this->c.z * bar.z;
            if (z < z_buffer[x + y * WIDTH]) {
                z_buffer[x + y * WIDTH] = z;
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}

V3D Triangle::to_barycentric(const V2D& p) const {
    V2D r = V2D(p.x - this->c.x, p.y - this->c.y);
    M2D cart2bar = M2D(this->a.x - this->c.x, this->b.x - this->c.x,
                       this->a.y - this->c.y, this->b.y - this->c.y);
    cart2bar.inv();

    if (isnan(cart2bar.a)) return V3D(-1, -1, -1);
    V2D lambdas = cart2bar * r;
    return V3D(lambdas.x, lambdas.y, 1 - lambdas.x - lambdas.y);
}

V3D to_barycentric(const V3D& a, const V3D& b, const V3D& c, const V2D& p) {
    V2D r = V2D(p.x - c.x, p.y - c.y);
    M2D cart2bar = M2D(a.x - c.x, b.x - c.x,
                       a.y - c.y, b.y - c.y);
    cart2bar.inv();

    // check if matrix contains NAN (due to inverse)
    if (isnan(cart2bar.a)) {
        return V3D(-1, -1, -1);
    }

    V2D lambdas = cart2bar * r;
    return V3D(lambdas.x, lambdas.y, 1.0 - lambdas.x - lambdas.y);
}
