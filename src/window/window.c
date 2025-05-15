#include "window.h"

b8 initWindow(EngineContext *ctx) {
    if (!glfwInit()) {
        NFATAL("Failed to initialize GLFW.\n")
        return false;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Nebula Engine", NULL, NULL);
    if (!window) {
        NFATAL("Failed to create GLFW window.\n")
        glfwTerminate();
        return false;
    }

    ctx->window = window;
    
    return true;
}

void cleanupWindow(GLFWwindow *window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}