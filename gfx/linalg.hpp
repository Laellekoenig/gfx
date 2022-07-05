#ifndef LINALG_H
#define LINALG_H

#include "pch.hpp"

// Triangle in gfx.h
class Triangle;

class V2D {
    public:
        float x;
        float y;

        V2D() : x{0}, y{0} {};
        V2D(const float x, const float y) : x{x}, y{y} {};
};

class V3D {
    public:
        float x;
        float y;
        float z;

        V3D() : x{0}, y{0}, z{0} {};
        V3D(const float x, const float y, const float z) : x{x}, y{y}, z{z} {};
        V3D& translate_origin(const int width, const int height);
        V3D operator/(const float c) const;
        V3D& operator/=(const float c);
        void operator=(const V3D& other);
};

class V4D {
    public:
        float x;
        float y;
        float z;
        float w;

        V4D() : x{0}, y{0}, z{0}, w{1} {};
        V4D(const float x,
            const float y,
            const float z,
            const float w = 1) : x{x}, y{y}, z{z}, w{w} {};
        V4D& dehomo();
        V4D& translate_origin(const int width, const int height);
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
        M2D(const float a,
            const float b,
            const float c,
            const float d) : a{a}, b{b}, c{c}, d{d} {};
        float det() const;
        M2D& inv();
        V2D operator*(const V2D& v) const;
};

#endif // LINALG_H
