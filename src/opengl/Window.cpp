#include "Window.h"
#include "../common/debug.h"
#include "OpenglException.h"
#include <cstdio>
#include <map>
#include <stdexcept>

using namespace opengl;

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

Window::Window(const std::string_view& title, int width, int height) {
    dbgln("Initializing window");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window_ = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
    if (window_ == nullptr) {
        // Window or OpenGL context creation failed
        throw_gl("Window creation failed");
    }

    glfwMakeContextCurrent(window_);

    // load all OpenGL function pointers
    // needs to come after the glfwMakeContentCurrent call
    dbgln("Loading OpenGL");
    if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
        throw_gl("Loading OpenGL failed with GLAD");
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
}

auto Window::window_pointer() const -> GLFWwindow* {
    return window_;
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

void Window::toggle_wireframe_rendering() {
    if (wireframe_rendering_) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // normal rendering
        wireframe_rendering_ = false;
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe rendering
        wireframe_rendering_ = true;
    }
}
