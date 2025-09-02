#include "fields.h"
#include <cmath>

Field::Field(int Nx_, int Ny_) : Nx(Nx_), Ny(Ny_) {
    phi.resize(Nx*Ny, {0.0, 0.0});
    phiDot.resize(Nx*Ny, {0.0, 0.0});
}

void Field::initializeGaussian(double x0, double y0, double sigma) {
    for (int i=0; i<Nx; i++) {
        for (int j=0; j<Ny; j++) {
            double dx = i - x0;
            double dy = j - y0;
            double r2 = dx*dx + dy*dy;
            phi[i*Ny + j] = std::exp(-r2 / (2.0*sigma*sigma));
        }
    }
}

double Field::magnitude2(int i, int j) const {
    auto val = phi[i*Ny + j];
    return std::norm(val);
}
