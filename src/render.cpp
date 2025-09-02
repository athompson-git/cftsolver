#include "render.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

Renderer::Renderer(int w, int h, Simulation &s)
: width(w), height(h), sim(s) {}

void Renderer::run() {
    if (!glfwInit()) {
        std::cerr << "GLFW init failed\n";
        return;
    }

    GLFWwindow* window = glfwCreateWindow(width, height, "Scalar QED 2+1D (|phi|^2)", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glewInit();

    int Nx = sim.field.Nx;
    int Ny = sim.field.Ny;

    std::vector<float> pixels(Nx*Ny*3);

    while (!glfwWindowShouldClose(window)) {
        sim.step();

        for (int i=0; i<Nx; i++) {
            for (int j=0; j<Ny; j++) {
                float v = (float)sim.field.magnitude2(i,j);
                v = std::min(v*10.0f, 1.0f); // normalize
                pixels[3*(i*Ny+j) + 0] = v; // R
                pixels[3*(i*Ny+j) + 1] = 0.0f;
                pixels[3*(i*Ny+j) + 2] = 1.0f-v; // B
            }
        }

        glDrawPixels(Nx, Ny, GL_RGB, GL_FLOAT, pixels.data());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
