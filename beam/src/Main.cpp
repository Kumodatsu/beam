#include "Common.hpp"
#include "rendering/Renderer.hpp"

int main(int, char**) {
    using namespace beam;

    Renderer renderer;

    /* Loop until the user closes the window */
    while (!renderer.IsWindowCloseRequested())
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        renderer.SwapBuffers();

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}
