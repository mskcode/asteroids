#include "GlfwContext.h"
#include "../common/debug.h"
#include "OpenglException.h"
#include "opengl.h"
#include <cstdio>

using namespace opengl;

static void error_callback(int error, const char* description) {
    std::fprintf(stderr, "GL ERROR: %d %s\n", error, description);
}

GlfwContext::GlfwContext() {
    dbgln("Initializing GLFW");
    glfwSetErrorCallback(error_callback);

    if (glfwInit() != GLFW_TRUE) {
        throw_gl("GLFW initialization failed");
    }
}

GlfwContext::~GlfwContext() {
    if (!terminated_) {
        dbgln("Terminating GLFW");
        glfwTerminate();
        terminated_ = true;
    }
}
