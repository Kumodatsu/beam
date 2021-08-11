#include "Common.hpp"
#include "rendering/Renderer.hpp"
#include "rendering/PixelBuffer.hpp"

int main(int, char**) {
    using namespace beam;

    Renderer renderer;

    constexpr UCount
        width  = 640,
        height = 480;

    PixelBuffer buffer(width, height);
    for (UIndex v = 0u; v < height; v++)
        for (UIndex u = 0u; u < width; u++) {
            buffer.At(u, v) = Vec4(
                Float32(u + 1) / Float32(width),
                0.0f, 0.0f, 1.0f
            );
        }


    /* Loop until the user closes the window */
    while (!renderer.IsWindowCloseRequested())
    {
        renderer.Render(buffer);

        /* Swap front and back buffers */
        renderer.SwapBuffers();

        /* Poll for and process events */
        glfwPollEvents();
    }

    return 0;
}
