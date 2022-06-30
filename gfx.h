#ifndef GFX_H
#define GFX_H

#include <SDL2/SDL.h>
#include <array>

#define HEIGHT 600
#define WIDTH 600
#define X 0
#define Y 1
#define Z 2

class Triangle;

class RGB {
    public:
        unsigned char r;
        unsigned char g;
        unsigned char b;

        RGB();
        RGB(unsigned char r, unsigned char g, unsigned char b);
        RGB operator*(const float& x) const;
        RGB operator+(const RGB& other) const;
};

class V2D {
    public:
        float x;
        float y;

        V2D();
        V2D(float x, float y);
};

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
        void dehomo();
        void translate_origin();
};

class M2D {
    public:
        float a;
        float b;
        float c;
        float d;

        M2D();
        M2D(float a, float b, float c, float d);
        float det();
        void inv();
        V2D operator*(const V2D& v) const;
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
        RGB ca;
        RGB cb;
        RGB cc;

        Triangle(V4D a, V4D b, V4D c);
        Triangle(V4D a, V4D b, V4D c, RGB ca, RGB cb, RGB cc);
        void render(SDL_Renderer* renderer, std::array<float, WIDTH * HEIGHT>& z_buffer);
        V3D to_barycentric(const V2D& p) const;
};

V3D to_barycentric(const V3D& a, const V3D& b, const V3D& c, const V2D& p);

#endif // GFX_H
