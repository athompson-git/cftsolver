#pragma once
#include <vector>
#include <complex>

class Field {
public:
    Field(int Nx, int Ny);

    int Nx, Ny;
    std::vector<std::complex<double>> phi;   // scalar field
    std::vector<std::complex<double>> phiDot; // time derivative

    void initializeGaussian(double x0, double y0, double sigma);
    double magnitude2(int i, int j) const;
};
