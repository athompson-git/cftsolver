// Lattice Class: Stores N + 1 dimensional lattice points with field content


#include <math.h>
#include <iostream>
#include <vector>
#include <array>
#include <cstddef>


using namespace std;

namespace CFTSolver {


struct {
  float x0y1;
  float x1y1;
  float x2y1;
  float x1y0;
  float x1y2;
} Stencil2D;


// 2 space + 1 Time spacetime lattice
class Lattice3D {        // The class
  public:          // Access specifier
    const int GRID_DEPTH = 50;
    const int N_POINTS = GRID_DEPTH * GRID_DEPTH;

    double deltaX;
    double deltaY;
    double deltaT;

    // Allocate memory for 3d lattice array of size latticeSize^3
    float* latticeThen = new float[N_POINTS];
    float* latticeNow = new float[N_POINTS];
    float* latticeNext = new float[N_POINTS];

    Lattice3D(); // default constructor
    Lattice3D(double dt, double dx); // Constructor declaration

  
  // Member functions
  private:
    int get_index(int i, int j);
    void update();
    float d2dx2(int i, int j, int k);
};

// Default constructor
Lattice3D::Lattice3D() {
  deltaX = 0.1;
  deltaY = 0.1;
  deltaT = 0.1;

  for (int i = 0; i < N_POINTS; i++) {
    latticeThen[i] = 0.0;
    latticeNow[i] = 0.0;
    latticeNext[i] = 0.0;
  }
}

// Constructor definition outside the class
Lattice3D::Lattice3D(double dt, double dx) {
  deltaX = dx;
  deltaY = dx;
  deltaT = dt;

  for (int i = 0; i < N_POINTS; i++) {
    latticeThen[i] = 0.0;
    latticeNow[i] = 0.0;
    latticeNext[i] = 0.0;
  }
}

int Lattice3D::get_index(int i, int j) {
  return i + j * GRID_DEPTH;
}

void Lattice3D::update() {
  // Loop over lattice points
  // TODO(me): convert to for_each to parallelize or something
  for (int i = 1; i < GRID_DEPTH - 1; i++) {
    for (int j = 1; j < GRID_DEPTH - 1; j++) {

      // Get the stencil at each lattice point
      int idx_01 = get_index(i-1, j);
      int idx_11 = get_index(i, j);
      int idx_21 = get_index(i+1, j);
      int idx_10 = get_index(i, j-1);
      int idx_12 = get_index(i, j+1);

      // t0 timestep (Then)
      float phi01_0 = latticeThen[idx_01];
      float phi11_0 = latticeThen[idx_11];
      float phi21_0 = latticeThen[idx_21];
      float phi10_0 = latticeThen[idx_10];
      float phi12_0 = latticeThen[idx_12];

      // t1 timestep (Now)
      float phi01_1 = latticeNow[idx_01];
      float phi11_1 = latticeNow[idx_11];
      float phi21_1 = latticeNow[idx_21];
      float phi10_1 = latticeNow[idx_10];
      float phi12_1 = latticeNow[idx_12];

      // Get update rules for phi##_2


      // point latticeThen --> latticeNow
      // point latticeNow --> latticeNext
      // can leave latticeNext as is, will get rewritten each iteration
    }
  }
}

float Lattice3D::d2dx2(int i, int j, int k) {
  return 0.0;
}


} // end namespace CFTSolver





int main() {

  CFTSolver::Lattice3D l4d;

  return 0;
}



