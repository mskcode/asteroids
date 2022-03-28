#include "GlWindow.h"

#include <stdexcept>
#include <cstdio>
#include <unistd.h>
#include "Spaceship.h"
#include "debug.h"

using namespace asteroids;

static void error_callback(int error, const char *description) {
    std::fprintf(stderr, "GLFW3 ERROR: %d %s\n", error, description);
}

static void
key_callback(GLFWwindow *window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

GlWindow::GlWindow(int width, int height) {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        throw std::runtime_error("GLFW initialization failed");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // 4, 2
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // 6, 0
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    debugln("Initializing window");
    window = glfwCreateWindow(width, height, "Asteroids", NULL, NULL);
    if (!window) {
        // Window or OpenGL context creation failed
        throw std::runtime_error("Window creation failed");
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    // load all OpenGL function pointers
    // needs to come after the glfwMakeContentCurrent call
    debugln("Loading OpenGL");
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("Loading OpenGL failed with GLAD");
    }

    /* if (!GLAD_GL_ARB_direct_state_access) {
        // https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_direct_state_access.txt
        // https://www.khronos.org/opengl/wiki/Direct_State_Access. This is the way.
        std::cout << "DSA not supported!" << std::endl;
        return -1;
    } */

    std::printf("Vendor: %s, Renderer: %s, Version: %s, Shading Language Version: %s\n",
                glGetString(GL_VENDOR), glGetString(GL_RENDER), glGetString(GL_VERSION),
                glGetString(GL_SHADING_LANGUAGE_VERSION));

    glfwSwapInterval(1);
}

GlWindow::~GlWindow() {
    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate();
}

void GlWindow::run() {
    Spaceship spaceship;

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe rendering
    while (!glfwWindowShouldClose(window)) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        glViewport(0, 0, width, height);
        glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        spaceship.render(window);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void GlWindow::close() {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}
