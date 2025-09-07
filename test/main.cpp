// main.cpp
// call the fields classes and euler lagrange
// run and send to openGL calls, visualize
#include <iostream>
#include <GLFW/glfw3.h>
#include "fields.cpp"
#include "eulerlagrange.cpp"

using namespace std;



void run_free_scalar() {
    RealScalarField phi(200, 0.001);
    phi.InitWavePacket(0.00001, 0.5, -0.2, 0.2, 0.2, 0.0, 0.0);

    for (int i = 0; i < phi.n - 1; i++){
        cout << phi.Get(i,8) << endl;
    }

    EulerLagrange el;

    int max_timesteps = 100;

    int l = 0;
    while(l < max_timesteps) {
        cout << "On timestamp = " << l << endl;
        el.PushFreeMassiveScalar(phi,20.0);
        l++;
        cout << phi.Get(10,10) << endl;
    }

}


int main() {

    run_free_scalar();

    return 0;
}


