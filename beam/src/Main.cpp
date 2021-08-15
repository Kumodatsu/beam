#include "Common.hpp"
#include "raytracing/Camera.hpp"
#include "raytracing/Raytracing.hpp"
#include "raytracing/Objects.hpp"
#include "rendering/Color.hpp"
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

    constexpr Color sky_color = colors::Black;

    PixelBuffer buffer(width, height);

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

        scene.Trace(camera, sky_color, buffer);

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
