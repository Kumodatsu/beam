#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace beam {

    class Renderer {
    public:
        Renderer();
        ~Renderer();

        bool IsWindowCloseRequested() const;
        
        void SwapBuffers() const;
    private:
        GLFWwindow* m_window;
    };

}
