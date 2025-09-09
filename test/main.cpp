// main.cpp
// call the fields classes and euler lagrange
// run and send to openGL calls, visualize

// working compilation so far:
// g++ main.cpp src/glad.c -Iinclude -o main -lglfw -lGL -ldl -lpthread -lm -lX11

#include <iostream>
#include <unistd.h>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "fields.cpp"
#include "eulerlagrange.cpp"

using namespace std;



void run_free_scalar()
{
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}



int main() {

    //    run_free_scalar();


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    


    glViewport(0, 0, 800, 600);

    // call on every window resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}


