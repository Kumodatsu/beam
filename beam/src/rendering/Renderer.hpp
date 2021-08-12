#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "rendering/PixelBuffer.hpp"

namespace beam {

    class Renderer {
    public:
        Renderer();
        ~Renderer();

        inline GLFWwindow* GetHandle() const { return m_window; }

        bool IsWindowCloseRequested() const;
        
        void Render(const PixelBuffer& buffer);
        void SwapBuffers() const;
    private:
        GLFWwindow* m_window;

        struct GLState {
            GLuint VAO_ID, VBO_ID, ShaderID;
        } m_gl_state;
    };

}
