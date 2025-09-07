// render.cpp
// responsible for setting up windows, shaders etc
// opengl helper functions etc.

//#pragma once
#include <GLFW/glfw3.h>
//#include <glad/glad.h>



int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* win = glfwCreateWindow(900,900,"scalar", nullptr, nullptr);

    glfwMakeContextCurrent(win);
    //gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glDisable(GL_DEPTH_TEST);


    return 0;

}
