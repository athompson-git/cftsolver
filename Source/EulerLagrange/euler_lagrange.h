#pragma once
#include "fields.h"

class Simulation {
public:
    Simulation(int Nx, int Ny, double dt, double dx, double e);

    void step();
    Field field;
    GaugeField gauge;

private:
    double dt, dx;
    void covariantLaplacian(Field &f, std::vector<std::complex<double>> &out);
};
