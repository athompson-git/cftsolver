#include "fields.h"
#include <cmath>

ComplexScalarField::InitializeField(int Nx_, int Ny_) : Nx(Nx_), Ny(Ny_) {
    phi.resize(Nx*Ny, {0.0, 0.0});
    phiDot.resize(Nx*Ny, {0.0, 0.0});
}

void ComplexScalarField::initializeGaussian(double x0, double y0, double sigma) {
    for (int i=0; i<Nx; i++) {
        for (int j=0; j<Ny; j++) {
            double dx = i - x0;
            double dy = j - y0;
            double r2 = dx*dx + dy*dy;
            phi[i*Ny + j] = std::exp(-r2 / (2.0*sigma*sigma));
        }
    }
}

double ComplexScalarField::magnitude2(int i, int j) const {
    auto val = phi[i*Ny + j];
    return std::norm(val);
}


/*

GaugeField::GaugeField(int Nx_, int Ny_, double e_)
: Nx(Nx_), Ny(Ny_), e(e_) {
    Ux.resize(Nx*Ny, {1.0, 0.0});
    Uy.resize(Nx*Ny, {1.0, 0.0});
}

void GaugeField::initializeUniform(double Ax, double Ay) {
    // Ax, Ay = background gauge potential
    for (int i=0; i<Nx; i++) {
        for (int j=0; j<Ny; j++) {
            double phaseX = e * Ax;
            double phaseY = e * Ay;
            Ux[i*Ny+j] = std::exp(std::complex<double>(0.0, phaseX));
            Uy[i*Ny+j] = std::exp(std::complex<double>(0.0, phaseY));
        }
    }
}

std::complex<double> GaugeField::linkX(int i, int j) const {
    return Ux[i*Ny+j];
}

std::complex<double> GaugeField::linkY(int i, int j) const {
    return Uy[i*Ny+j];
}


*/
