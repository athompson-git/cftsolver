#include <iostream>
#include <vector>
#include <string>
#include <map>

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

// This way we never have to save the full history. We can send data
// to OpenGL or write images later for viz.

class RealScalarField {
    private:
        vector<vector<float>> phi_top;
        vector<vector<float>> phi_mid;
        vector<vector<float>> phi_bottom;

        std::map<string, int> layer_map;
    public:
        int n;
        int dl;

        RealScalarField(int grid_size);

        void InitGauss(float x0, float y0, float sigma);
        void InitWavePacket(float omega, float kx, float ky, float sigma);

        void Push(int i, int j, float new_value);
        float Get(int i, int j);
        float GetPast(int i, int j);

        float Del2X(int i, int j); // second derivatives
        float Del2Y(int i, int j);

};

RealScalarField::RealScalarField(int grid_size)
    : n(grid_size),
    phi_top(grid_size, vector<float>(grid_size,0.0)),
    phi_mid(grid_size, vector<float>(grid_size,0.0)),
    phi_bottom(grid_size, vector<float>(grid_size,0.0)) {

    layer_map["past"] = 2;
    layer_map["present"] = 1;
    layer_map["future"] = 0;
    dl = 1.0 / static_cast<float>(grid_size);

}

float RealScalarField::Get(int i, int j) {
    // can enforce torus topology here
    if (layer_map["present"] == 2) {
        return phi_top[i][j];
    } else if (layer_map["present"] == 1) {
        return phi_mid[i][j];
    } else {
        return phi_bottom[i][j];
    }
    
}

float RealScalarField::GetPast(int i, int j) {
    // can enforce torus topology here
    if (layer_map["past"] == 2) {
        return phi_top[i][j];
    } else if (layer_map["past"] == 1) {
        return phi_mid[i][j];
    } else {
        return phi_bottom[i][j];
    }
}

void RealScalarField::Push(int i, int j, float new_value) {
    if (layer_map["future"] == 2) {
        phi_top[i][j] = new_value;
    } else if (layer_map["future"] == 1) {
        phi_mid[i][j] = new_value;
    } else {
        phi_bottom[i][j] = new_value;
    }

    // Cycle the layer map
    layer_map["future"] = (layer_map["future"] + 1) % 3;
    layer_map["present"] = (layer_map["present"] + 1) % 3;
    layer_map["past"] = (layer_map["past"] + 1) % 3;
}

float RealScalarField::Del2X(int i, int j) {
    // central difference formula
    // TODO(AT): find better boundary condition, maybe include torus geometry

    if (i == n) return 0.0;
    if (i == 0) return 0.0;
    if (j == n) return 0.0;
    if (j == 0) return 0.0;

    return Get(i+1,j) - 2*Get(i,j) + Get(i-1,j);

}

float RealScalarField::Del2Y(int i, int j) {
    // central difference formula
    // TODO(AT): find better boundary condition, maybe include torus geometry

    if (i == n) return 0.0;
    if (i == 0) return 0.0;
    if (j == n) return 0.0;
    if (j == 0) return 0.0;

    return Get(i,j+1) - 2*Get(i,j) + Get(i,j-1);

}




// Give EL a box of data, it will tell you what the Push rules are
class EulerLagrange {
    public:
        EulerLagrange() {}

        void PushFreeMassiveScalar(RealScalarField Phi, float m);


};

void EulerLagrange::PushFreeMassiveScalar(RealScalarField Phi, float m) {

    for (int i=0; i<Phi.n; i++) {
        for (int j=0; j<Phi.n; j++) {
            float phi_next = 2 * Phi.Get(i,j) - Phi.GetPast(i,j) \
                    + Phi.Del2X(i,j) + Phi.Del2Y(i,j) - m*m*Phi.Get(i,j);
            Phi.Push(i,j,phi_next);
        }
    } 

}


int main() {
	cout << "Beginning program..." << endl;

    RealScalarField x(5);

    cout << x.Get(1,1) << endl;
    x.Push(2,2,1.0);
    x.Push(2,3,1.0);

    cout << 0 % 50 << endl;
    cout << 50 % 50 << endl;
    cout << 49 % 50 << endl;
    cout << 51 % 50 << endl;
    cout << -1 % 50 << endl;

	cout << "...ending program." << endl;
	return 0;
}
