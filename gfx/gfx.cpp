#include "gfx.hpp"
#include "linalg.hpp"
#include <cfloat>
#include <iostream>

// 2D coordinates to 1D array index
#define TO_INDEX(X, Y) (X + Y * WIDTH)

RGB RGB::operator*(const float c) const {
    return RGB(r * c, g * c, b * c);
}

RGB& RGB::operator*=(const float c) {
    r *= c;
    g *= c;
    b *= c;
    return *this;
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

uint RGB::to_int() const {
    return (r << 16) + (g << 8) + b;
}

Image::Image() {
    z_buffer.fill(FLT_MAX);
    img.fill(BLACK);
}

void Image::draw(SDL_Renderer* renderer) const {
    SDL_Surface* surf = SDL_CreateRGBSurface(0, HEIGHT, WIDTH, 32, 0, 0, 0, 0);
    uint* pixels = (uint*) surf->pixels;

    for (uint i = 0; i < img.size(); i++) {
        RGB color = img[i];
        pixels[i] = color.to_int();
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    SDL_Rect screen_rect = {0, 0, WIDTH, HEIGHT};

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, tex, nullptr, &screen_rect);
    SDL_RenderPresent(renderer);
}

std::mutex Image::image_mutex;

void Image::set_pixel(uint x, uint y, float z, RGB& c) {
    std::lock_guard<std::mutex> guard(image_mutex);
    uint idx = x + WIDTH * y;
    z_buffer[idx] = z;
    img[idx] = c;
}

float Image::check_depth(uint x, uint y) {
    std::lock_guard<std::mutex> guard(image_mutex);
    return z_buffer[x + WIDTH * y];
}

void Image::reset() {
    std::lock_guard<std::mutex> guard(image_mutex);
    img.fill(BLACK);
    z_buffer.fill(FLT_MAX);
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

    data[0] = ((float) HEIGHT / WIDTH) * fov_tan;
    data[5] = fov_tan;
    data[10] = f_far / f_delta;
    data[14] = (-f_far * f_near) / f_delta;
    data[11] = 1;
    data[15] = 0;
}

V3D Triangle::to_barycentric(const V2D& p) const {
    V2D r(p.x - c.x, p.y - c.y);
    M2D cart2bar(a.x - c.x, b.x - c.x,
                 a.y - c.y, b.y - c.y);
    cart2bar.inv();

    if (isnan(cart2bar.a)) return V3D(-1, -1, -1);
    V2D lambdas = cart2bar * r;
    return V3D(lambdas.x, lambdas.y, 1 - lambdas.x - lambdas.y);
}

void Triangle::render(Image& img) {
    // get pixel coordinates
    a.dehomo();
    b.dehomo();
    c.dehomo();

    a.translate_origin(WIDTH, HEIGHT);
    b.translate_origin(WIDTH, HEIGHT);
    c.translate_origin(WIDTH, HEIGHT);

    // find bounding box
    float min_x = fmin(a.x, fmin(b.x, c.x));
    float max_x = fmax(a.x, fmax(b.x, c.x));
    float min_y = fmin(a.y, fmin(b.y, c.y));
    float max_y = fmax(a.y, fmax(b.y, c.y));

    for (int y = min_y; y <= max_y; y++) {
        for (int x = min_x; x <= max_x; x++) {
            // check if point is in triangle
            V3D bar = this->to_barycentric(V2D(x, y));
            if (bar.x < 0 || bar.y < 0 || bar.z < 0) continue;

            // check z buffer
            float z = a.z * bar.x + b.z * bar.y + c.z * bar.z;
            if (z < img.check_depth(x, y)) {

                // interpolate color
                RGB color = ca * bar.x + cb * bar.y + cc * bar.z;

                // get triangle normal and calculate lighting
                // TODO: make light direction a parameter of function
                V3D normal = this->get_normal();
                float light_product = normal.dot(V3D(0, 0, -1).normalize());
                color *= light_product;

                // draw
                img.set_pixel(x, y, z, color);
            }
        }
    }
}

V3D Triangle::get_normal() const {
    V4D u = b - a;
    V4D v = c - a;

    // cross product u x v
    return V3D(u.y * v.z - u.z * v.y,
               u.z * v.x - u.x * v.z,
               u.x * v.y - u.y * v.x).normalize();
}
