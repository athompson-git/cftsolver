#include "euler_lagrange.h"
#include <vector>

Simulation::Simulation(int Nx, int Ny, double dt_, double dx_)
: field(Nx,Ny), dt(dt_), dx(dx_) {}

void Simulation::laplacian(Field &f, std::vector<std::complex<double>> &out) {
    int Nx = f.Nx, Ny = f.Ny;
    out.assign(Nx*Ny, {0.0,0.0});

    for (int i=1; i<Nx-1; i++) {
        for (int j=1; j<Ny-1; j++) {
            out[i*Ny+j] = (f.phi[(i+1)*Ny+j] + f.phi[(i-1)*Ny+j]
                          + f.phi[i*Ny+(j+1)] + f.phi[i*Ny+(j-1)]
                          - 4.0*f.phi[i*Ny+j]) / (dx*dx);
        }
    }
}

void Simulation::step() {
    int Nx = field.Nx, Ny = field.Ny;
    std::vector<std::complex<double>> lap;
    laplacian(field, lap);

    for (int i=0; i<Nx*Ny; i++) {
        auto acc = lap[i]; // wave equation: φ̈ = ∇² φ
        field.phiDot[i] += dt * acc;
        field.phi[i]    += dt * field.phiDot[i];
    }
}
