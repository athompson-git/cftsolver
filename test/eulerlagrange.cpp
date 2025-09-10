// eulerlagrange.cpp
#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <complex>

#include "fields.cpp"


// Give EL a box of data, it will tell you what the Push rules are

// Class 1: EulerLagrange
//
// Class 2: EulerLagrangeScalarYukawa
// takes in dt, m, M, g, n_grid
// sets up 3 fields with uniform grid density
// has a single push method

class EulerLagrange {
public:
    EulerLagrange() {}

    void PushFreeMassiveScalar(RealScalarField &Phi);
    void PushScalarYukawa(RealScalarField &Phi,
                          ComplexScalarField &Psi,
                          ComplexScalarField &PsiStar);

};

void EulerLagrange::PushFreeMassiveScalar(RealScalarField &Phi) {

    for (int i=0; i<Phi.n; i++) {
        for (int j=0; j<Phi.n; j++) {

            // Push with the Klein-Gordon equation for Phi
            // Using 2nd order central for d'Alembertian on phi
            float kg_push = 2 * Phi.Get(i,j) - Phi.GetPast(i,j)
                            + (Phi.Del2X(i,j) + Phi.Del2Y(i,j)
                            -Phi.mass * Phi.mass * Phi.Get(i,j)) * (Phi.dt*Phi.dt);

            Phi.Push(i,j,kg_push);
        }
}

    Phi.RotatePlanes();

}


class ELScalarYukawa {
public:
    ELScalarYukawa();
    ELScalarYukawa(int grid_size, float time_step,
                   float rscalar_mass, float cscalar_mass,
                   float coupling);

    RealScalarField Phi;
    ComplexScalarField Psi;
    ComplexScalarField PsiStar;

    float coupling;

    void PushScalarYukawa();

    float GetEnergy();

    float GetCharge();

private:
    int grid_size;
    float dt;
};


ELScalarYukawa::ELScalarYukawa(int grid_size, float time_step,
                               float rscalar_mass, float cscalar_mass,
                               float coupling)
    : Phi(grid_size, time_step, rscalar_mass),
    Psi(grid_size, time_step, cscalar_mass),
    PsiStar(grid_size, time_step, cscalar_mass),
    dt(time_step) {

    this->coupling = coupling;
    this->grid_size = grid_size;
}

float ELScalarYukawa::GetEnergy() {

    float energy = 0.0;

    for (int i=0; i<grid_size; i++) {
        for (int j=0; j<grid_size; j++) {
            energy += 0.0;
            // TODO: need to get time derivative
            // need to implement GetFuture()
        }
    }

    return 0.f;
}

void ELScalarYukawa::PushScalarYukawa() {
    // push the 3 EoM's for scalar yukawa theory
    for (int i=0; i<grid_size; i++) {
        for (int j=0; j<grid_size; j++) {

            // Push with the Klein-Gordon equation for Phi
            // Using 2nd order central for d'Alembertian on phi
            float kg_push = 2.f * Phi.Get(i,j) - Phi.GetPast(i,j)
                + (Phi.Del2X(i,j) + Phi.Del2Y(i,j)
                - Phi.mass * Phi.mass * Phi.Get(i,j)) * dt * dt;

            complex<float> kg_push_psi = 2.f * Psi.Get(i,j) - Psi.GetPast(i,j)
                + (Psi.Del2X(i,j) + Psi.Del2Y(i,j)
                -Psi.mass * Psi.mass * Psi.Get(i,j)) * dt * dt;

            complex<float> kg_push_psi_star = 2.f * PsiStar.Get(i,j) - PsiStar.GetPast(i,j)
                + (PsiStar.Del2X(i,j) + PsiStar.Del2Y(i,j)
                -PsiStar.mass * PsiStar.mass * PsiStar.Get(i,j)) * dt * dt;

            // define push from interaction terms
            float int_push_phi = -coupling*(PsiStar.Get(i,j)*Psi.Get(i,j)).real();
            complex<float> int_push_psi = -coupling * Phi.Get(i,j) * Psi.Get(i,j);
            complex<float> int_push_psi_star = -coupling * Phi.Get(i,j) * PsiStar.Get(i,j);


            Phi.Push(i,j,kg_push + int_push_phi);
            Psi.Push(i,j,kg_push_psi + int_push_psi);
            PsiStar.Push(i,j,kg_push_psi_star + int_push_psi_star);
        }
    }

    Phi.RotatePlanes();
    Psi.RotatePlanes();
    PsiStar.RotatePlanes();
}



