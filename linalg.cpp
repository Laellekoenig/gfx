#include "linalg.h"
#include "gfx.h"

V2D::V2D() {
    this->x = 0;
    this->y = 0;
}

V2D::V2D(const float x, const float y) {
    this->x = x;
    this->y = y;
}

V3D::V3D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

V3D::V3D(const float x, const float y, const float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

void V3D::translate_origin(const int width, const int height) {
    this->x = this->x * -1 + width * 0.5;
    this->y = this->y * -1 + height * 0.5;
}

V3D V3D::operator/(const float c) {
    return V3D(this->x / c, this->y / c, this->z / z);
}

void V3D::operator/=(const float c) {
    *this = *this / c;
}

void V3D::operator=(const V3D& other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}

V4D::V4D() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = 1;
}

V4D::V4D(const float x, const float y, const float z, const float w) {
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

void V4D::translate_origin(const int height, const int width) {
    this->x = this->x * -1 + width * 0.5;
    this->y = this->y * -1 + height * 0.5;
}

M4D::M4D() {
    this->data.fill(0);
}

V4D M4D::operator*(const V4D& v) const {
    float x = v.x * this->data[0] + v.y * this->data[1] + v.z * this->data[2] + v.w * this->data[3];
    float y = v.x * this->data[4] + v.y * this->data[5] + v.z * this->data[6] + v.w * this->data[7];
    float z = v.x * this->data[8] + v.y * this->data[9] + v.z * this->data[10] + v.w * this->data[11];
    float w = v.x * this->data[12] + v.y * this->data[13] + v.z * this->data[14] + v.w * this->data[15];
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

    o.data[0] =  this->data[0] * m.data[0] + this->data[1] * m.data[4] + this->data[2] * m.data[8] + this->data[3] * m.data[12];
    o.data[1] =  this->data[0] * m.data[1] + this->data[1] * m.data[5] + this->data[2] * m.data[9] + this->data[3] * m.data[13];
    o.data[2] =  this->data[0] * m.data[2] + this->data[1] * m.data[6] + this->data[2] * m.data[10] + this->data[3] * m.data[14];
    o.data[3] =  this->data[0] * m.data[3] + this->data[1] * m.data[7] + this->data[2] * m.data[11] + this->data[3] * m.data[15];

    o.data[4] =  this->data[4] * m.data[0] + this->data[5] * m.data[4] + this->data[6] * m.data[8] + this->data[7] * m.data[12];
    o.data[5] =  this->data[4] * m.data[1] + this->data[5] * m.data[5] + this->data[6] * m.data[9] + this->data[7] * m.data[13];
    o.data[6] =  this->data[4] * m.data[2] + this->data[5] * m.data[6] + this->data[6] * m.data[10] + this->data[7] * m.data[14];
    o.data[7] =  this->data[4] * m.data[3] + this->data[5] * m.data[7] + this->data[6] * m.data[11] + this->data[7] * m.data[15];

    o.data[8] =  this->data[8] * m.data[0] + this->data[9] * m.data[4] + this->data[10] * m.data[8] + this->data[11] * m.data[12];
    o.data[9] =  this->data[8] * m.data[1] + this->data[9] * m.data[5] + this->data[10] * m.data[9] + this->data[11] * m.data[13];
    o.data[10] = this->data[8] * m.data[2] + this->data[9] * m.data[6] + this->data[10] * m.data[10] + this->data[11] * m.data[14];
    o.data[11] = this->data[8] * m.data[3] + this->data[9] * m.data[7] + this->data[10] * m.data[11] + this->data[11] * m.data[15];

    o.data[12] = this->data[12] * m.data[0] + this->data[13] * m.data[4] + this->data[14] * m.data[8] + this->data[15] * m.data[12];
    o.data[13] = this->data[12] * m.data[1] + this->data[13] * m.data[5] + this->data[14] * m.data[9] + this->data[15] * m.data[13];
    o.data[14] = this->data[12] * m.data[2] + this->data[13] * m.data[6] + this->data[14] * m.data[10] + this->data[15] * m.data[14];
    o.data[15] = this->data[12] * m.data[3] + this->data[13] * m.data[7] + this->data[14] * m.data[11] + this->data[15] * m.data[15];

    return o;
}

float M4D::operator()(const int i, const int j) const {
    if (i < 0 || i > 3 || j < 0 || j > 3) return NAN;
    return this->data[i * 3 + j];
}

M2D::M2D() {
    this->a = 0;
    this->b = 0;
    this->c = 0;
    this->d = 0;
}

M2D::M2D(const float a, const float b, const float c, const float d) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}

float M2D::det() const {
    return a * d - b * c;
}

void M2D::inv() {
    float det = this->det();

    if (det == 0) {
        a = NAN;
        b = NAN;
        c = NAN;
        d = NAN;
        return;
    }

    det = 1.0 / det;
    float temp = a;

    a = det * d;
    b *= -1 * det;
    c *= -1 * det;
    d = det * temp;
    //*this = M2D(det * this->d, -1 * det * this->b,
                //-1 * det * this->c, det * this->a);
}

V2D M2D::operator*(const V2D& v) const {
    return V2D(this->a * v.x + this->b * v.y,
               this->c * v.x + this->d * v.y);
}
