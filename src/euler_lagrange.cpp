#include "euler_lagrange.h"
#include <vector>

Simulation::Simulation(int Nx, int Ny, double dt_, double dx_, double e)
: field(Nx,Ny), gauge(Nx,Ny,e), dt(dt_), dx(dx_) {
    gauge.initializeUniform(0.05, 0.0); // weak background Ax
}

void Simulation::covariantLaplacian(Field &f, std::vector<std::complex<double>> &out) {
    int Nx = f.Nx, Ny = f.Ny;
    out.assign(Nx*Ny, {0.0,0.0});

    for (int i=1; i<Nx-1; i++) {
        for (int j=1; j<Ny-1; j++) {
            int idx = i*Ny+j;

            // Forward/backward neighbors with gauge links
            auto phi_ij = f.phi[idx];

            // X direction
            auto Ux = gauge.linkX(i,j);
            auto Umx = std::conj(gauge.linkX(i-1,j));
            auto termX = Ux*f.phi[(i+1)*Ny+j] + Umx*f.phi[(i-1)*Ny+j] - 2.0*phi_ij;

            // Y direction
            auto Uy = gauge.linkY(i,j);
            auto Umy = std::conj(gauge.linkY(i,j-1));
            auto termY = Uy*f.phi[i*Ny+(j+1)] + Umy*f.phi[i*Ny+(j-1)] - 2.0*phi_ij;

            out[idx] = (termX + termY) / (dx*dx);
        }
    }
}

void Simulation::step() {
    int Nx = field.Nx, Ny = field.Ny;
    std::vector<std::complex<double>> lap;
    covariantLaplacian(field, lap);

    for (int i=0; i<Nx*Ny; i++) {
        auto acc = lap[i]; // gauge-covariant wave equation
        field.phiDot[i] += dt * acc;
        field.phi[i]    += dt * field.phiDot[i];
    }
}
