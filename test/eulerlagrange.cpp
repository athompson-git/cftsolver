// eulerlagrange.cpp
#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <complex>

#include "fields.cpp"


// Give EL a box of data, it will tell you what the Push rules are
class EulerLagrange {
    public:
        EulerLagrange() {}

        void PushFreeMassiveScalar(RealScalarField &Phi, float m);

};

void EulerLagrange::PushFreeMassiveScalar(RealScalarField &Phi, float m) {

    for (int i=0; i<Phi.n; i++) {
        for (int j=0; j<Phi.n; j++) {

            // Push with the Klein-Gordon equation for Phi
            // Using 2nd order central for d'Alembertian on phi
            float kg_push = 2 * Phi.Get(i,j) - Phi.GetPast(i,j)
                            + (Phi.Del2X(i,j) + Phi.Del2Y(i,j)
                            -m*m*Phi.Get(i,j)) * Phi.dt * Phi.dt;

            Phi.Push(i,j,kg_push);
        }
    }

    Phi.RotatePlanes();

}






