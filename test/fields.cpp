// fields.cpp
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <complex>
#include <GLFW/glfw3.h>

using namespace std;



// Overview plan
// RealScalarField class
// ComplexScalarField class
// EulerLagrange class
// --> contains specific field update rules
// --> accesses fields with Push methods


// Fields:
// to avoid minimal rewriting and mem alloc, establish 3 layers:
// ------ top layer  <--- future
// ------ mid layer  <--- current present
// ------ bottom layer <---- past

// when we push an update, it goes to the top layer always.
// but after that, the bottom layer gets moved to the top
// as the next one to be rewritten with future data.
// The mid becomes the past, and the top becomes the present.
// This way we minimzie the # of copies of the field data we have to make.
// Consider an index that updates which is which after every Push

//  --future--- <--|  i+1
//  --present--    ^  i
//  ---past---- -->|  i-1

// This way we never have to save the full history. We can send data
// to OpenGL or write images later for viz.

// The space complexity is N^2 * 3 * N_fields

class RealScalarField {
    public:
        const int n;
        const float dl;
        const float dt;

        RealScalarField();
        RealScalarField(int grid_size, float time_step);

        void InitWavePacket(float omega, float kx, float ky, \
                            float sigma_x, float sigma_y, \
                            float x0, float y0);

        float GetX(int i) {
            return dl*(static_cast<float>(i) - static_cast<float>(n)/2);
        }

        float GetY(int i) {
            return dl*(static_cast<float>(i) - static_cast<float>(n)/2);
        }

        float Get(int i, int j) {

            if (i >= n) return 0.0;
            if (i <= 0) return 0.0;
            if (j >= n) return 0.0;
            if (j <= 0) return 0.0;

            // can enforce torus topology here
            auto *p = GetPlane(present);
            return (*p)[i][j];
        }

        float GetPast(int i, int j) {
            // can enforce torus topology here

            if (i >= n) return 0.0;
            if (i <= 0) return 0.0;
            if (j >= n) return 0.0;
            if (j <= 0) return 0.0;

            auto *p = GetPlane(past);
            return (*p)[i][j];
        }

        void Push(int i, int j, float new_value) {
            auto *p = GetPlane(future);
            (*p)[i][j] = new_value;
        }

        float Del2X(int i, int j); // second derivatives
        float Del2Y(int i, int j);

        // rotate layers once per time step
        void RotatePlanes() {
            int tmp = past;
            past = present;
            present = future;
            future = tmp;
        }

    private:
        vector<vector<float>> phi_top;
        vector<vector<float>> phi_mid;
        vector<vector<float>> phi_bottom;

        int past, present, future;
        
        vector<vector<float>>* GetPlane(int idx) {
            switch (idx) {
                case 0: return &phi_bottom;
                case 1: return &phi_mid;
                case 2: return &phi_top;
                default: return nullptr;
            }
        }

};

RealScalarField::RealScalarField(int grid_size, float time_step)
    : n(grid_size), dt(time_step),
    dl(1.0 / static_cast<float>(grid_size)),
    phi_top(grid_size, vector<float>(grid_size,0.0)),
    phi_mid(grid_size, vector<float>(grid_size,0.0)),
    phi_bottom(grid_size, vector<float>(grid_size,0.0)),
    past(0), present(1), future(2) {}

void RealScalarField::InitWavePacket(float omega, float kx, float ky,
                                    float sigma_x, float sigma_y,
                                    float x0, float y0) {
    
    auto *past_plane = GetPlane(past);
    auto *present_plane = GetPlane(present);

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            float x = GetX(i);
            float y = GetY(j);
            (*past_plane)[i][j] = cos(kx*x)*cos(ky*y)
                                * exp(-pow(x-x0, 2) / pow(sigma_x, 2))
                                * exp(-pow(y-y0,2) / pow(sigma_y, 2));
            (*present_plane)[i][j] = cos(kx*x)*cos(ky*y)
                                   * exp(-pow(x-x0, 2) / pow(sigma_x, 2))
                                   * exp(-pow(y-y0, 2) / pow(sigma_y, 2));
        }
    }
}

float RealScalarField::Del2X(int i, int j) {
    // central difference formula
    // TODO(AT): find better boundary condition, maybe include torus geometry

    if (i >= n) return 0.0;
    if (i <= 0) return 0.0;
    if (j >= n) return 0.0;
    if (j <= 0) return 0.0;

    return (Get(i+1,j) - 2.0 * Get(i,j) + Get(i-1,j))/(dl*dl);

}

float RealScalarField::Del2Y(int i, int j) {
    // central difference formula
    // TODO(AT): find better boundary condition, maybe include torus geometry

    if (i >= n) return 0.0;
    if (i <= 0) return 0.0;
    if (j >= n) return 0.0;
    if (j <= 0) return 0.0;

    return (Get(i,j+1) - 2.0 * Get(i,j) + Get(i,j-1))/(dl*dl);

}




// Complex Scalar Field
class ComplexScalarField {
    public:
        const int n;
        const float dl;
        const float dt;

        ComplexScalarField();
        ComplexScalarField(int grid_size, float time_step);

        void InitWavePacket(float omega, float kx, float ky, \
                            float sigma_x, float sigma_y, \
                            float x0, float y0);

        float GetX(int i) {
            return dl*(static_cast<float>(i) - static_cast<float>(n)/2);
        }

        float GetY(int i) {
            return dl*(static_cast<float>(i) - static_cast<float>(n)/2);
        }

        complex<float> Get(int i, int j) {

            if (i >= n) return 0.0;
            if (i <= 0) return 0.0;
            if (j >= n) return 0.0;
            if (j <= 0) return 0.0;

            // can enforce torus topology here
            auto *p = GetPlane(present);
            return (*p)[i][j];
        }

        complex<float> GetPast(int i, int j) {
            // can enforce torus topology here

            if (i >= n) return 0.0;
            if (i <= 0) return 0.0;
            if (j >= n) return 0.0;
            if (j <= 0) return 0.0;

            auto *p = GetPlane(past);
            return (*p)[i][j];
        }

        void Push(int i, int j, float new_value) {
            auto *p = GetPlane(future);
            (*p)[i][j] = new_value;
        }

        complex<float> Del2X(int i, int j); // second derivatives
        complex<float> Del2Y(int i, int j);

        // rotate layers once per time step
        void RotatePlanes() {
            int tmp = past;
            past = present;
            present = future;
            future = tmp;
        }

    private:
        vector<vector<complex<float>>> phi_top;
        vector<vector<complex<float>>> phi_mid;
        vector<vector<complex<float>>> phi_bottom;

        int past, present, future;
        
        vector<vector<complex<float>>>* GetPlane(int idx) {
            switch (idx) {
                case 0: return &phi_bottom;
                case 1: return &phi_mid;
                case 2: return &phi_top;
                default: return nullptr;
            }
        }

};

ComplexScalarField::ComplexScalarField(int grid_size, float time_step)
    : n(grid_size), dt(time_step),
    dl(1.0 / static_cast<float>(grid_size)),
    phi_top(grid_size, vector<complex<float>>(grid_size,0.0)),
    phi_mid(grid_size, vector<complex<float>>(grid_size,0.0)),
    phi_bottom(grid_size, vector<complex<float>>(grid_size,0.0)),
    past(0), present(1), future(2) {
}

void ComplexScalarField::InitWavePacket(float omega, float kx, float ky,
                                    float sigma_x, float sigma_y,
                                    float x0, float y0) {
    
    auto *past_plane = GetPlane(past);
    auto *present_plane = GetPlane(present);

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            float x = GetX(i);
            float y = GetY(j);
            (*past_plane)[i][j] = cos(kx*x)*cos(ky*y)
                                * exp(-pow(x-x0, 2) / pow(sigma_x, 2))
                                * exp(-pow(y-y0,2) / pow(sigma_y, 2));
            (*present_plane)[i][j] = cos(kx*x)*cos(ky*y)
                                   * exp(-pow(x-x0, 2) / pow(sigma_x, 2))
                                   * exp(-pow(y-y0, 2) / pow(sigma_y, 2));
        }
    }
}

complex<float> ComplexScalarField::Del2X(int i, int j) {
    // central difference formula
    // TODO(AT): find better boundary condition, maybe include torus geometry

    if (i >= n) return 0.0;
    if (i <= 0) return 0.0;
    if (j >= n) return 0.0;
    if (j <= 0) return 0.0;

    return (Get(i+1,j) - static_cast<complex<float>>(2.0) * Get(i,j) + Get(i-1,j))/(dl*dl);

}

complex<float> ComplexScalarField::Del2Y(int i, int j) {
    // central difference formula
    // TODO(AT): find better boundary condition, maybe include torus geometry

    if (i >= n) return 0.0;
    if (i <= 0) return 0.0;
    if (j >= n) return 0.0;
    if (j <= 0) return 0.0;

    return (Get(i,j+1) - static_cast<complex<float>>(2.0) * Get(i,j) + Get(i,j-1))/(dl*dl);

}




