#pragma once
#include "euler_lagrange.h"

class Renderer {
public:
    Renderer(int width, int height, Simulation &sim);
    void run();

private:
    int width, height;
    Simulation &sim;
};
