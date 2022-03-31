#include "Window.h"
#include "Spaceship.h"
#include "debug.h"
#include <cstdio>
#include <stdexcept>

using namespace opengl;

static void error_callback(int error, const char* description) {
    std::fprintf(stderr, "GLFW3 ERROR: %d %s\n", error, description);
}

static void key_callback(GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action,
                         [[maybe_unused]] int mods) {
    dbgfln("Key event: key=%d, scancode=%d, action=%d, mods=%d", key, scancode, action, mods);
    if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        case GLFW_KEY_F1:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe rendering
            break;
        case GLFW_KEY_F2:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // normal rendering
            break;
        default:
            break;
        }
    }
}

Window::Window(int width, int height) {
    glfwSetErrorCallback(error_callback);
    if (glfwInit() != GLFW_TRUE) {
        throw std::runtime_error("GLFW initialization failed");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    dbgln("Initializing window");
    window_ = glfwCreateWindow(width, height, "Asteroids", nullptr, nullptr);
    if (window_ == nullptr) {
        // Window or OpenGL context creation failed
        throw std::runtime_error("Window creation failed");
    }

    glfwSetKeyCallback(window_, key_callback);
    glfwMakeContextCurrent(window_);

    // load all OpenGL function pointers
    // needs to come after the glfwMakeContentCurrent call
    dbgln("Loading OpenGL");
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
        throw std::runtime_error("Loading OpenGL failed with GLAD");
    }

    /* if (!GLAD_GL_ARB_direct_state_access) {
        // https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_direct_state_access.txt
        // https://www.khronos.org/opengl/wiki/Direct_State_Access. This is the way.
        std::cout << "DSA not supported!" << std::endl;
        return -1;
    } */

    std::printf("Vendor: %s, Renderer: %s, Version: %s, Shading Language Version: %s\n", glGetString(GL_VENDOR),
                glGetString(GL_RENDER), glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

    glfwSwapInterval(1);
}

Window::~Window() {
    if (window_ != nullptr) {
        glfwDestroyWindow(window_);
        window_ = nullptr;
    }
    if (!terminated_) {
        glfwTerminate();
        terminated_ = true;
    }
}

void Window::run() {
    asteroids::Spaceship spaceship;

    while (glfwWindowShouldClose(window_) == 0) {
        int width;
        int height;
        glfwGetFramebufferSize(window_, &width, &height);

        glViewport(0, 0, width, height);

        glClearColor(1.0F, 0.3F, 0.3F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);

        spaceship.render(window_);

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}

void Window::close() {
    glfwSetWindowShouldClose(window_, GLFW_TRUE);
}
