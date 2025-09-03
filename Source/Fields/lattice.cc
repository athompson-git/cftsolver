// Lattice Class: Stores N + 1 dimensional lattice points with field content


#include <math.h>
#include <iostream>
#include <vector>
#include <array>
#include <cstddef>


using namespace std;

namespace CFTSolver {

class Lattice2D {        // The class
  public:          // Access specifier
    const int GRID_DEPTH = 50;
    double deltaX;
    double deltaT;

    // Set pointer for lattice array
    float* lattice = new float[GRID_DEPTH];

    Lattice2D(); // default constructor
    Lattice2D(double dt, double dx); // Constructor declaration

    // Member functions
    void update();
    double get_field(int i, int j);
};

// Default constructor
Lattice2D::Lattice2D() {
  deltaX = 0.1;
  deltaT = 0.1;

  for (int i = 0; i < GRID_DEPTH; i++) {
    lattice[i] = 0.0;
  }
}

// Constructor definition outside the class
Lattice2D::Lattice2D(double dt, double dx) {
  deltaX = dx;
  deltaT = dt;

  for (int i = 0; i < GRID_DEPTH; i++) {
    lattice[i] = 0.0;
  }
}




// Member functions
void Lattice2D::update() {
}

double Lattice2D::get_field(int i, int j) {
  return 0.0;
}





// 4D spacetime lattice
class Lattice4D {        // The class
  public:          // Access specifier
    const int GRID_DEPTH = 50;
    const int N_POINTS = GRID_DEPTH * GRID_DEPTH * GRID_DEPTH;

    double deltaX;
    double deltaY;
    double deltaZ;
    double deltaT;

    // Allocate memory for 3d lattice array of size latticeSize^3
    float* latticeThen = new float[N_POINTS];
    float* latticeNow = new float[N_POINTS];
    float* latticeNext = new float[N_POINTS];

    Lattice4D(); // default constructor
    Lattice4D(double dt, double dx); // Constructor declaration

  
  // Member functions
  private:
    int get_index(int i, int j, int k);
    void update();
    float d2dx2(int i, int j, int k);

};

// Default constructor
Lattice4D::Lattice4D() {
  deltaX = 0.1;
  deltaY = 0.1;
  deltaZ = 0.1;
  deltaT = 0.1;

  for (int i = 0; i < N_POINTS; i++) {
    latticeThen[i] = 0.0;
    latticeNow[i] = 0.0;
    latticeNext[i] = 0.0;
  }
}

// Constructor definition outside the class
Lattice4D::Lattice4D(double dt, double dx) {
  deltaX = dx;
  deltaY = dx;
  deltaZ = dx;
  deltaT = dt;

  for (int i = 0; i < N_POINTS; i++) {
    latticeThen[i] = 0.0;
    latticeNow[i] = 0.0;
    latticeNext[i] = 0.0;
  }
}

int Lattice4D::get_index(int i, int j, int k) {
  return i + j * GRID_DEPTH + k * GRID_DEPTH * GRID_DEPTH;
}

void Lattice4D::update() {}

float Lattice4D::d2dx2(int i, int j, int k) {
  return 0.0;
}


} // end namespace CFTSolver





int main() {

  CFTSolver::Lattice4D l4d;

  return 0;
}



