#include "Common.hpp"
#include "SceneParser.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace beam {

    static Vec3 parse_vec3(const json& src) {
        return Vec3(
            src["x"],
            src["y"],
            src["z"]
        );
    }

    static Vec4 parse_color(const json& src) {
        return Vec4(
            src["r"],
            src["g"],
            src["b"],
            src["a"]
        );
    }

    static MaterialType parse_material_type(const std::string& src) {
        if (src == "diffuse")
            return MaterialType::Diffuse;
        throw std::runtime_error("Invalid material type.");
    }

    static Material parse_material(const json& src) {
        return Material(
            parse_material_type(src["type"]),
            parse_color(src["color"]),
            src["emission"]
        );
    }

    bool parse_scene(Scene& scene, const std::string& path) {
        scene.Clear();

        std::ifstream file(path);
        if (!file.is_open() || file.bad()) {
            std::cerr << "Can't open scene file." << std::endl;
            return false;
        }
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        try {
            const auto scene_desc = json::parse(buffer);

            for (const auto& obj : scene_desc["scene"]) {
                if (obj["type"] == "sphere") {
                    scene.Add<Sphere>(
                        parse_material(obj["material"]),
                        parse_vec3(obj["pos"]),
                        obj["radius"]
                    );
                } else {
                    std::cerr << "Unknown object type." << std::endl;
                    return false;
                }
            }
        } catch (const std::exception& exc) {
            std::cerr << exc.what() << std::endl;
            return false;
        }

        return true;
    }

}
