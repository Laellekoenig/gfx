#ifndef LINALG_H
#define LINALG_H

#include <array>

// Triangle in gfx.h
class Triangle;

class V2D {
    public:
        float x;
        float y;

        V2D();
        V2D(const float x, const float y);
};

class V3D {
    public:
        float x;
        float y;
        float z;

        V3D();
        V3D(const float x, const float y, const float z);
        void translate_origin(const int width, const int height);
        V3D operator/(const float c);
        void operator/=(const float c);
        void operator=(const V3D& other);
};

class V4D {
    public:
        float x;
        float y;
        float z;
        float w;

        V4D();
        V4D(const float x, const float y, const float z, const float w = 1);
        V4D& dehomo();
        void translate_origin(const int width, const int height);
};

class M4D {
    public:
        std::array<float, 16> data;
        M4D();
        V4D operator*(const V4D& v) const;
        Triangle operator*(const Triangle& v) const;
        M4D operator*(const M4D& m) const;
        float operator()(const int i, const int j) const;
};

class M2D {
    public:
        float a;
        float b;
        float c;
        float d;

        M2D() : a{0}, b{0}, c{0}, d{0} {};
        M2D(const float a, const float b, const float c, const float d) : a{a}, b{b}, c{c}, d{d} {};
        float det() const;
        M2D& inv();
        V2D operator*(const V2D& v) const;
};

#endif // LINALG_H
