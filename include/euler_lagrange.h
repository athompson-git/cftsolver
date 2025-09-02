#pragma once
#include "fields.h"

class Simulation {
public:
    Simulation(int Nx, int Ny, double dt, double dx);

    void step(); // evolve one timestep
    Field field;

private:
    double dt, dx;
    void laplacian(Field &f, std::vector<std::complex<double>> &out);
};
