#include "Window.h"
#include "../common/debug.h"
#include "openglerror.h"
#include <cstdio>
#include <map>

using namespace engine;

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

static Window* g_window_instance{nullptr};

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

static void framebuffer_size_callback([[maybe_unused]] GLFWwindow* window,
                                      [[maybe_unused]] int width,
                                      [[maybe_unused]] int height) {
    if (g_window_instance != nullptr) {
        g_window_instance->update_window_size();
    }
}

Window::Window(const WindowOptions& options) {
    dbgln("Initializing window");

    // https://www.glfw.org/docs/latest/window_guide.html#window_hints_wnd
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, options.opengl_version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, options.opengl_version_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, options.resizable ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    window_ = glfwCreateWindow(static_cast<int>(options.window_size.width),
                               static_cast<int>(options.window_size.height),
                               options.title.data(),
                               nullptr,
                               nullptr);
    if (window_ == nullptr) {
        // Window or OpenGL context creation failed
        throw_gl("Window creation failed");
    }

    window_size_ = options.window_size;
    glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);

    glfwMakeContextCurrent(window_);
    if (options.vsync_enabled) {
        glfwSwapInterval(1);
    }

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

    g_window_instance = this;
}

Window::~Window() {
    if (window_ != nullptr) {
        dbgln("Destroying window");
        glfwDestroyWindow(window_);
        window_ = nullptr;
    }
}

auto Window::should_close() const -> bool {
    return glfwWindowShouldClose(window_) == 1;
}

auto Window::window_pointer() const -> GLFWwindow* {
    return window_;
}

auto Window::window_size() const -> const Dimensions2D& {
    return window_size_;
}

void Window::close() {
    glfwSetWindowShouldClose(window_, GLFW_TRUE);
}

void Window::update_window_size() {
    int width{0};
    int height{0};
    glfwGetFramebufferSize(window_, &width, &height);
    window_size_.width = width;
    window_size_.height = height;
}
