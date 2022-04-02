#include "Window.h"
#include "debug.h"
#include <cstdio>
#include <map>
#include <stdexcept>
#include <string>

using namespace opengl;

static void error_callback(int error, const char* description) {
    std::fprintf(stderr, "GL ERROR: %d %s\n", error, description);
}

static const std::map<GLenum, std::string> g_debug_source_map{{GL_DEBUG_SOURCE_API, "SOURCE_API"},
                                                              {GL_DEBUG_SOURCE_WINDOW_SYSTEM, "WINDOW_SYSTEM"},
                                                              {GL_DEBUG_SOURCE_SHADER_COMPILER, "SHADER_COMPILER"},
                                                              {GL_DEBUG_SOURCE_THIRD_PARTY, "THIRD_PARTY"},
                                                              {GL_DEBUG_SOURCE_APPLICATION, "APPLICATION"},
                                                              {GL_DEBUG_SOURCE_OTHER, "OTHER"}};

static const std::map<GLenum, std::string> g_debug_type_map{{GL_DEBUG_TYPE_ERROR, "ERROR"},
                                                            {GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, "DEPRECATED_BEHAVIOR"},
                                                            {GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR, "UNDEFINED_BEHAVIOR"},
                                                            {GL_DEBUG_TYPE_PORTABILITY, "PORTABILITY"},
                                                            {GL_DEBUG_TYPE_PERFORMANCE, "PERFORMANCE"},
                                                            {GL_DEBUG_TYPE_OTHER, "OTHER"},
                                                            {GL_DEBUG_TYPE_MARKER, "MARKER"}};

static const std::map<GLenum, std::string> g_debug_severity_map{{GL_DEBUG_SEVERITY_HIGH, "HIGH"},
                                                                {GL_DEBUG_SEVERITY_MEDIUM, "MEDIUM"},
                                                                {GL_DEBUG_SEVERITY_LOW, "LOW"},
                                                                {GL_DEBUG_SEVERITY_NOTIFICATION, "NOTIFICATION"}};

static void debug_callback(GLenum source,
                           GLenum type,
                           [[maybe_unused]] GLuint id,
                           GLenum severity,
                           [[maybe_unused]] GLsizei length,
                           const GLchar* message,
                           [[maybe_unused]] const void* user_param) {
    std::fprintf(stderr,
                 "GL DEBUG: %s type = %s, severity = %s, message = %s\n",
                 g_debug_source_map.at(source).c_str(),
                 g_debug_type_map.at(type).c_str(),
                 g_debug_severity_map.at(severity).c_str(),
                 message);
}

static void
key_callback(GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods) {
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

#ifndef NDEBUG
    // This block needs to come way down here or else you get a core dump
    dbgln("Enabling OpenGL debug output");
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debug_callback, nullptr);
    glDebugMessageControl(GL_DEBUG_SOURCE_API,
                          GL_DEBUG_TYPE_OTHER,
                          GL_DEBUG_SEVERITY_NOTIFICATION,
                          0,
                          nullptr,
                          GL_FALSE);
#endif

    std::printf("Vendor: %s, RenderableObject: %s, Version: %s, Shading Language Version: %s\n",
                glGetString(GL_VENDOR),
                glGetString(GL_RENDERER),
                glGetString(GL_VERSION),
                glGetString(GL_SHADING_LANGUAGE_VERSION));

    glfwSwapInterval(1);
}

Window::~Window() {
    if (window_ != nullptr) {
        dbgln("Destroying window");
        glfwDestroyWindow(window_);
        window_ = nullptr;
    }
    if (!terminated_) {
        dbgln("Terminating GLFW");
        glfwTerminate();
        terminated_ = true;
    }
}

void Window::run(const std::function<bool(GLFWwindow*)>& render) {
    bool continue_render_loop = true;
    while (continue_render_loop && glfwWindowShouldClose(window_) == 0) {
        continue_render_loop = render(window_);
        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}

void Window::close() {
    glfwSetWindowShouldClose(window_, GLFW_TRUE);
}
