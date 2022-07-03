#ifndef GFX_H
#define GFX_H

#include <SDL2/SDL.h>
#include <array>
#include "linalg.h"

#define HEIGHT 600
#define WIDTH 600

#define WHITE RGB(255, 255, 255)
#define BLACK RGB(0, 0, 0)
#define RED RGB(255, 0, 0)
#define GREEN RGB(0, 255, 0)
#define BLUE RGB(0, 0, 255)

enum Direction {X, Y, Z};

class Triangle;

class RGB {
    public:
        unsigned char r;
        unsigned char g;
        unsigned char b;

        RGB() : r{255}, g{255}, b{255} {};
        RGB(const unsigned char r, const unsigned char g, const unsigned char b) : r{r}, g{g}, b{b} {};
        RGB operator*(const float& c) const;
        RGB operator+(const RGB& other) const;
        RGB& operator+=(const RGB& other);
};

class TranslationM4D: public M4D {
    public:
        TranslationM4D(const float x, const float y, const float z);
};

class ScalingM4D: public M4D {
    public:
        ScalingM4D(const float x, const float y, const float z);
};

class RotationM4D: public M4D {
    public:
        RotationM4D(const float theta, const Direction dir = Direction::X);
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
