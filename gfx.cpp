#include "gfx.h"
#include <math.h>
#include <limits.h>

RGB RGB::operator*(const float& c) const {
    return RGB(r * c, g * c, b * c);
}

RGB RGB::operator+(const RGB& other) const {
    return RGB(r + other.r, g + other.g, b + other.b);
}

RGB& RGB::operator+=(const RGB& other) {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
}

TranslationM4D::TranslationM4D(const float x, const float y, const float z) {
    data[0] = 1;
    data[3] = x;
    data[5] = 1;
    data[7] = y;
    data[10] = 1;
    data[11] = z;
    data[15] = 1;
}

ScalingM4D::ScalingM4D(const float x, const float y, const float z) {
    data[0] = x;
    data[5] = y;
    data[10] = z;
}

RotationM4D::RotationM4D(const float theta, const Direction dir) {
    float cosTheta = cos(theta);
    float sinTheta = sin(theta);

    if (dir == Direction::X) {
        data[0] = 1;
        data[5] = cosTheta;
        data[6] = -sinTheta;
        data[9] = sinTheta;
        data[10] = cosTheta;
        data[15] = 1;

    } else if (dir == Direction::Y) {
        data[0] = cosTheta;
        data[2] = -sinTheta;
        data[5] = 1;
        data[8] = sinTheta;
        data[10] = cosTheta;
        data[15] = 1;

    } else if (dir == Direction::Z) {
        data[0] = cosTheta;
        data[1] = -sinTheta;
        data[4] = sinTheta;
        data[5] = cosTheta;
        data[10] = 1;
        data[15] = 1;
    }
}

ProjectionM4D::ProjectionM4D() {
    float f_near = 0.1;
    float f_far = 1000.0;
    float f_delta = f_far - f_near;
    float fov = 90.0;
    float fov_tan = 1.0 / tan(fov * 0.5 / 180.0 * M_PI);

    data[0] = (HEIGHT / WIDTH) * fov_tan;
    data[5] = fov_tan;
    data[10] = f_far / f_delta;
    data[14] = (-f_far * f_near) / f_delta;
    data[11] = 1;
    data[15] = 0;
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

    this->a.translate_origin(WIDTH, HEIGHT);
    this->b.translate_origin(WIDTH, HEIGHT);
    this->c.translate_origin(WIDTH, HEIGHT);

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
