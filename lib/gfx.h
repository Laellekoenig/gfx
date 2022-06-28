#ifndef GFX_H
#define GFX_H

#include "raylib.h"

#define HEIGHT 600
#define WIDTH 600
#define X 0
#define Y 1
#define Z 2

class Triangle;

class V3D {
    public:
        float x;
        float y;
        float z;

        V3D();
        V3D(float x, float y, float z);
        void translate_origin();
        void operator/=(const float x);
};

class V4D {
    public:
        float x;
        float y;
        float z;
        float w;

        V4D();
        V4D(float x, float y, float z, float w = 1);
        V3D dehomo();
};

class M4D {
    public:
        float m[4][4];

        M4D();
        V4D operator*(const V4D& v) const;
        Triangle operator*(const Triangle& v) const;
        M4D operator*(const M4D& m) const;
};

class TranslationM4D: public M4D {
    public:
        TranslationM4D(float x, float y, float z);
};

class ScalingM4D: public M4D {
    public:
        ScalingM4D(float x, float y, float z);
};

class RotationM4D: public M4D {
    public:
        RotationM4D(float theta, int dir = 0);
};

class ProjectionM4D: public M4D {
    public:
        ProjectionM4D();
};

class Triangle {
    public:
        V4D a;
        V4D b;
        V4D c;
        Color ca;
        Color cb;
        Color cc;

        Triangle(V4D a, V4D b, V4D c);
        Triangle(V4D a, V4D b, V4D c, Color ca, Color cb, Color cc);
        void render();
        void render_projection();
};

#endif // GFX_H

