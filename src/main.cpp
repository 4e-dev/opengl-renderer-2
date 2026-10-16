// standard
#include <array>

// third party
#include <glad/glad.h>
#include <glfw/glfw3.h>

// custom
#include <math/linear_algebra.h>
#include <util/log.h>

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    /* Handles key and mouse input for GLFW */
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main() {
    if (!glfwInit()) {
        log("FAILED::GLFW initialization.", ERROR, __FILE__, __LINE__);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // using opengl v4.6 - core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Retail Sim", nullptr, nullptr);
    if (!window)
    {
        log("FAILED::GLFW window creation.", ERROR, __FILE__, __LINE__);
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        log("FAILED::GLAD initialization.", ERROR, __FILE__, __LINE__);
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }


    //TODO: currently going through the glfw tutorial text
    GLuint vertex_buffer;

    // gameplay loop
    while (!glfwWindowShouldClose(window))
    {
        // TODO: run something...
    }

    // cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}

