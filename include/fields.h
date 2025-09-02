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



class GaugeField {
public:
    GaugeField(int Nx, int Ny, double e);

    int Nx, Ny;
    double e; // gauge coupling
    std::vector<std::complex<double>> Ux; // link in x-direction
    std::vector<std::complex<double>> Uy; // link in y-direction

    void initializeUniform(double Ax, double Ay); // background field
    std::complex<double> linkX(int i, int j) const;
    std::complex<double> linkY(int i, int j) const;
};
