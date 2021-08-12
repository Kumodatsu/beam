#include "Common.hpp"
#include "raytracing/Camera.hpp"
#include "raytracing/Raytracing.hpp"
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

    Camera camera(
        Float32(width) / Float32(height),
        80.0f,
        Vec3(0.0f, 0.0f, -3.0f),
        Vec3(0.0f, 0.0f, 1.0f),
        5.0f,
        0.1f
    );

    Scene scene;
    scene
    .Add<Sphere>(Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec3(0.0f, 0.0f, 10.0f), 3.0f)
    .Add<Sphere>(Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec3(5.0f, 0.0f, 10.0f), 2.0f)
    .Add<Sphere>(Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec3(0.0f, -6.0f, 10.0f), 3.0f)
    ;

    while (!renderer.IsWindowCloseRequested()) {
        constexpr Float32 speed = 1.0f;
        Vec3 movement = Vec3(0.0f, 0.0f, 0.0f);
        if (glfwGetKey(renderer.GetHandle(), GLFW_KEY_W))
            movement.Z += 1.0f;
        if (glfwGetKey(renderer.GetHandle(), GLFW_KEY_S))
            movement.Z -= 1.0f;
        if (glfwGetKey(renderer.GetHandle(), GLFW_KEY_A))
            movement.X -= 1.0f;
        if (glfwGetKey(renderer.GetHandle(), GLFW_KEY_D))
            movement.X += 1.0f;
        if (movement != Vec3(0.0f, 0.0f, 0.0f)) {
            maths::normalize(movement);
            camera.Move(speed * movement);
        }

        const Float32
            du = 1.0f / Float32(width),
            dv = 1.0f / Float32(height);
        for (UIndex v = 0u; v < height; v++) {
            for (UIndex u = 0u; u < width; u++) {
                const Float32
                    ru = u * du,
                    rv = v * dv;
                const Ray  ray          = camera.ScreenCoordsToRay(ru, rv);
                const auto intersection = scene.Intersect(ray);
                Vec4 color;
                if (intersection) {
                    color = Vec4(1.0f, 0.0f, 0.0f, 1.0f);
                } else {
                    color = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
                }
                buffer.At(u, v) = color;
            }
        }            

        renderer.Render(buffer);
        renderer.SwapBuffers();
        glfwPollEvents();
    }

    return 0;
}
