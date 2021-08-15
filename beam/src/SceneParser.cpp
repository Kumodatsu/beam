#include "Common.hpp"
#include "SceneParser.hpp"
#include <nlohmann/json.hpp>
#include "rendering/Color.hpp"

using json = nlohmann::json;

namespace beam {

    static Vec3 parse_vec3(const json& src) {
        return Vec3(
            src["x"],
            src["y"],
            src["z"]
        );
    }

    static Color parse_color(const json& src) {
        return Color(
            src["r"],
            src["g"],
            src["b"]
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

    static const json& get_key(const json& src, const std::string& key) {
        if (src.contains(key))
            return src[key];
        throw std::runtime_error("Key not present.");
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

            for (const auto& obj : get_key(scene_desc, "scene")) {                
                if (get_key(obj, "type") == "sphere") {
                    scene.Add<Sphere>(
                        parse_material(get_key(obj, "material")),
                        parse_vec3(get_key(obj, "pos")),
                        get_key(obj, "radius")
                    );
                } else if (get_key(obj, "type") == "plane") {
                    if (obj.contains("d"))
                        scene.Add<Plane>(
                            parse_material(get_key(obj, "material")),
                            parse_vec3(get_key(obj, "normal")),
                            get_key(obj, "d")
                        );
                    else
                        scene.Add<Plane>(
                            parse_material(get_key(obj, "material")),
                            parse_vec3(get_key(obj, "normal")),
                            parse_vec3(get_key(obj, "point"))
                        );
                } else if (get_key(obj, "type") == "triangle") {
                    scene.Add<Triangle>(
                        parse_material(get_key(obj, "material")),
                        parse_vec3(get_key(obj, "a")),
                        parse_vec3(get_key(obj, "b")),
                        parse_vec3(get_key(obj, "c"))
                    );
                } else {
                    std::cerr << "Unknown object type." << std::endl;
                    return false;
                }
            }
        } catch (const std::exception& exc) {
            std::cerr << exc.what() << std::endl;
            scene.Clear();
            return false;
        }

        return true;
    }

}
