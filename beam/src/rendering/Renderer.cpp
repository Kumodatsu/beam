#include "Common.hpp"
#include "Renderer.hpp"

static void GLAPIENTRY gl_message_callback(
    GLenum, // source
    GLenum type,
    GLuint, // id
    GLenum severity,
    GLsizei, // length
    const GLchar* message,
    const void* // user_param
) {
    if (severity == GL_DEBUG_SEVERITY_HIGH
            || severity == GL_DEBUG_SEVERITY_MEDIUM
            || severity == GL_DEBUG_SEVERITY_LOW) {
        fprintf(stderr, "GL: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            type, severity, message);
    }
}

namespace beam {

    Renderer::Renderer()
        : m_window(nullptr)
    {
        if (!glfwInit())
            throw std::runtime_error("Failed to initialize GLFW.");
        m_window = glfwCreateWindow(640, 480, "Beam", nullptr, nullptr);
        if (!m_window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create window.");
        }
        glfwMakeContextCurrent(m_window);
        const auto proc = reinterpret_cast<GLADloadproc>(glfwGetProcAddress);
        if (!gladLoadGLLoader(proc)) {
            glfwTerminate();
            throw std::runtime_error("Could not initialize Glad.");
        }

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(gl_message_callback, this);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    Renderer::~Renderer() {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    bool Renderer::IsWindowCloseRequested() const {
        return glfwWindowShouldClose(m_window);
    }

    void Renderer::SwapBuffers() const {
        glfwSwapBuffers(m_window);
    }

}
