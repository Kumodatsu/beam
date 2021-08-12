#include "Common.hpp"
#include "raytracing/Camera.hpp"
#include "raytracing/Raytracing.hpp"
#include "rendering/Renderer.hpp"
#include "rendering/PixelBuffer.hpp"
#include "SceneParser.hpp"

int main(int argc, char** argv) {
    using namespace beam;

    if (argc != 2) {
        std::cerr << "You need to specify a scene file." << std::endl;
        return -1;
    }

    const std::string scene_path = argv[1];
    auto scene_update_time = std::filesystem::last_write_time(scene_path);

    Renderer renderer;

    constexpr UCount
        width  = 640,
        height = 480;

    constexpr Vec4 clear_color = Vec4(0.0f, 0.0f, 0.0f, 1.0f);

    PixelBuffer buffer(width, height);
    for (UIndex v = 0u; v < height; v++)
        for (UIndex u = 0u; u < width; u++)
            buffer.At(u, v) = clear_color;

    Camera camera(
        Float32(width) / Float32(height),
        80.0f,
        Vec3(0.0f, 0.0f, -3.0f),
        Vec3(0.0f, 0.0f, 1.0f),
        5.0f,
        0.1f
    );

    Scene scene;
    parse_scene(scene, argv[1]);

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
                buffer.At(u, v) = intersection.has_value()
                                ? intersection->Material.Color
                                : clear_color;
            }
        }            

        renderer.Render(buffer);
        renderer.SwapBuffers();

        if (std::filesystem::exists(scene_path)) {
            const auto update_time =
                std::filesystem::last_write_time(scene_path);
            if (update_time > scene_update_time) {
                scene_update_time = update_time;
                parse_scene(scene, argv[1]);    
            }
        }

        glfwPollEvents();
    }

    return 0;
}
