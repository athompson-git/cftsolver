#pragma once
#include <cmath>


namespace fields {

constexpr float pi = 3.14159265358979323846;


// Periodic boundary waves and gaussian

float wrapped_gaussian(float x, float mu, float sigma) {
    return (1 / sigma / sqrt(2*pi)) \
            * ( exp(-pow(x - mu - 4*pi, 2) / (2 * pow(sigma, 2))) \
                + exp(-pow(x - mu - 2*pi, 2) / (2 * pow(sigma, 2))) \
                + exp(-pow(x - mu, 2) / (2 * pow(sigma, 2))) \
                + exp(-pow(x - mu + 2*pi, 2) / (2 * pow(sigma, 2))) \
                + exp(-pow(x - mu + 4*pi, 2) / (2 * pow(sigma, 2))) );
}

float cos_wave(float x, float mu, int kx, float l) {
    return cos(2 * kx * pi * (x - mu) / l);
}

float sin_wave(float x, float mu, int kx, float l) {
    return sin(2 * kx * pi * (x - mu) / l);
}

int mod(int idx, int grid_max) {
    int r = (idx % grid_max);
    return (r < 0) ? (r + grid_max) : r;
}

}  // end namespace fields





