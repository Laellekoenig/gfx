#include "linalg.hpp"
#include "gfx.hpp"

V3D& V3D::translate_origin(const int width, const int height) {
    x = x * -1 + width * 0.5;
    y = y * -1 + height * 0.5;
    return *this;
}

V3D V3D::operator/(const float c) const {
    return V3D(x / c, y / c, z / z);
}

V3D& V3D::operator/=(const float c) {
    x /= c;
    y /= c;
    z /= c;
    return *this;
}

void V3D::operator=(const V3D& other) {
    x = other.x;
    y = other.y;
    z = other.z;
}

V3D& V3D::normalize() {
    float len = sqrtf(x * x + y * y + z * z);
    x /= len;
    y /= len;
    z /= len;

    return *this;
}

float V3D::dot(const V3D& other) const {
    return x * other.x + y * other.y + z * other.z;
}

V4D& V4D::dehomo() {
    if (w != 0) {
        x /= w;
        y /= w;
        z /= w;
        w = 1.0f;
    }
    return *this;
}

V4D& V4D::translate_origin(const int height, const int width) {
    x = x * -1 + width * 0.5;
    y = y * -1 + height * 0.5;
    return *this;
}

V4D V4D::operator-(const V4D& other) const {
    return V4D(x - other.x,
               y - other.y,
               z - other.z,
               w - other.w);
}

M4D::M4D() {
    data.fill(0);
}

V4D M4D::operator*(const V4D& v) const {
    float x = v.x * data[0] + v.y * data[1] + v.z * data[2] + v.w * data[3];
    float y = v.x * data[4] + v.y * data[5] + v.z * data[6] + v.w * data[7];
    float z = v.x * data[8] + v.y * data[9] + v.z * data[10] + v.w * data[11];
    float w = v.x * data[12] + v.y * data[13] + v.z * data[14] + v.w * data[15];
    return V4D(x, y, z, w);
}

Triangle M4D::operator*(const Triangle& t) const {
    return Triangle(*this * t.a, *this * t.b, *this * t.c,
                    t.ca, t.cb, t.cc);
}

M4D M4D::operator*(const M4D& m) const {
    M4D o = M4D();

    o.data[0] =  data[0] * m.data[0] + data[1] * m.data[4] + data[2] * m.data[8] + data[3] * m.data[12];
    o.data[1] =  data[0] * m.data[1] + data[1] * m.data[5] + data[2] * m.data[9] + data[3] * m.data[13];
    o.data[2] =  data[0] * m.data[2] + data[1] * m.data[6] + data[2] * m.data[10] + data[3] * m.data[14];
    o.data[3] =  data[0] * m.data[3] + data[1] * m.data[7] + data[2] * m.data[11] + data[3] * m.data[15];

    o.data[4] =  data[4] * m.data[0] + data[5] * m.data[4] + data[6] * m.data[8] + data[7] * m.data[12];
    o.data[5] =  data[4] * m.data[1] + data[5] * m.data[5] + data[6] * m.data[9] + data[7] * m.data[13];
    o.data[6] =  data[4] * m.data[2] + data[5] * m.data[6] + data[6] * m.data[10] + data[7] * m.data[14];
    o.data[7] =  data[4] * m.data[3] + data[5] * m.data[7] + data[6] * m.data[11] + data[7] * m.data[15];

    o.data[8] =  data[8] * m.data[0] + data[9] * m.data[4] + data[10] * m.data[8] + data[11] * m.data[12];
    o.data[9] =  data[8] * m.data[1] + data[9] * m.data[5] + data[10] * m.data[9] + data[11] * m.data[13];
    o.data[10] = data[8] * m.data[2] + data[9] * m.data[6] + data[10] * m.data[10] + data[11] * m.data[14];
    o.data[11] = data[8] * m.data[3] + data[9] * m.data[7] + data[10] * m.data[11] + data[11] * m.data[15];

    o.data[12] = data[12] * m.data[0] + data[13] * m.data[4] + data[14] * m.data[8] + data[15] * m.data[12];
    o.data[13] = data[12] * m.data[1] + data[13] * m.data[5] + data[14] * m.data[9] + data[15] * m.data[13];
    o.data[14] = data[12] * m.data[2] + data[13] * m.data[6] + data[14] * m.data[10] + data[15] * m.data[14];
    o.data[15] = data[12] * m.data[3] + data[13] * m.data[7] + data[14] * m.data[11] + data[15] * m.data[15];

    return o;
}

float M4D::operator()(const int i, const int j) const {
    if (i < 0 || i > 3 || j < 0 || j > 3) return NAN;
    return data[i * 3 + j];
}

float M2D::det() const {
    return a * d - b * c;
}

M2D& M2D::inv() {
    float det = this->det();

    if (det == 0) {
        a = b = c = d = NAN;
        return *this;
    }

    std::swap(a, d);
    a /= det;
    b /= -det;
    c /= -det;
    d /= det;

    return *this;
}

V2D M2D::operator*(const V2D& v) const {
    return V2D(a * v.x + b * v.y,
               c * v.x + d * v.y);
}
