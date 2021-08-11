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

static constexpr std::array<beam::Float32, 6 * 4> SquareVertices {
//   x      y     u     v
    -1.0f, -1.0f, 0.0f, 0.0f,
     1.0f, -1.0f, 1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f, 1.0f,
    -1.0f,  1.0f, 0.0f, 1.0f,
     1.0f, -1.0f, 1.0f, 0.0f,
     1.0f,  1.0f, 1.0f, 1.0f
};

static const GLchar* VertexSrc = reinterpret_cast<const GLchar*>(R"(
    #version 450

    in vec2 v_pos;
    in vec2 v_texcoords;

    out vec2 f_texcoords;

    void main() {
        gl_Position = vec4(v_pos, 0.0f, 1.0f);
        f_texcoords = v_texcoords;
    }
)");

static const GLchar* FragmentSrc = reinterpret_cast<const GLchar*>(R"(
    #version 450

    uniform sampler2D u_texture;

    in vec2 f_texcoords;

    out vec4 o_color;

    void main() {
        o_color = texture(u_texture, f_texcoords);
    }
)");


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

        glCreateVertexArrays(1, &m_gl_state.VAO_ID);
        glBindVertexArray(m_gl_state.VAO_ID);
        glCreateBuffers(1, &m_gl_state.VBO_ID);
        glBindBuffer(GL_ARRAY_BUFFER, m_gl_state.VBO_ID);
        glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(Float32) * SquareVertices.size(),
            SquareVertices.data(),
            GL_STATIC_DRAW
        );
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(Float32),
            reinterpret_cast<const void*>(0)
        );
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(Float32),
            reinterpret_cast<const void*>(2 * sizeof(Float32))
        );
        m_gl_state.ShaderID = glCreateProgram();
        const GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vshader, 1, &VertexSrc, nullptr);
        glCompileShader(vshader);
        glAttachShader(m_gl_state.ShaderID, vshader);
        const GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fshader, 1, &FragmentSrc, nullptr);
        glCompileShader(fshader);
        glAttachShader(m_gl_state.ShaderID, fshader);
        glLinkProgram(m_gl_state.ShaderID);
        glDetachShader(m_gl_state.ShaderID, fshader);
        glDetachShader(m_gl_state.ShaderID, vshader);
        glDeleteShader(fshader);
        glDeleteShader(vshader);
        glUseProgram(m_gl_state.ShaderID);
        glUniform1i(glGetUniformLocation(m_gl_state.ShaderID, "u_texture"), 0);
    }

    Renderer::~Renderer() {
        glDeleteProgram(m_gl_state.ShaderID);
        glDeleteBuffers(1, &m_gl_state.VBO_ID);
        glDeleteVertexArrays(1, &m_gl_state.VAO_ID);
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    bool Renderer::IsWindowCloseRequested() const {
        return glfwWindowShouldClose(m_window);
    }

    void Renderer::Render(const PixelBuffer& buffer) {
        buffer.BufferData();
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(m_gl_state.VAO_ID);
        buffer.BindTexture(0);
        glUseProgram(m_gl_state.ShaderID);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void Renderer::SwapBuffers() const {
        glfwSwapBuffers(m_window);
    }

}
