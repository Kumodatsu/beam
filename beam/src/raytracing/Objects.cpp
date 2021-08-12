#include "Common.hpp"
#include "Objects.hpp"

namespace beam {

    std::optional<Intersection> Sphere::Intersect(const Ray& ray) const {
        const Vec3
            O_C = ray.Origin - Center;
        const Float32
            a   = maths::dot(ray.Direction, ray.Direction),
            b   = 2.0f * maths::dot(ray.Direction, O_C),
            c   = maths::dot(O_C, O_C) - Radius * Radius,
            D   = b * b - 4.0f * a * c;
        if (D < 0.0f)
            return std::nullopt;
        const Float32
            s   = std::sqrt(D),
            t_0 = (-b + s) / (2.0f * a),
            t_1 = (-b - s) / (2.0f * a),
            t   = (t_0 < 0.0f || t_1 < t_0) ? t_1 : t_0;
        if (t < 0.0f)
            return std::nullopt;
        const auto P = ray.Traverse(t);
        return Intersection(P, maths::normalized(P - Center), Material);
    }

    std::optional<Intersection> Scene::Intersect(const Ray& ray) const {
        std::optional<Intersection>
            closest_intersection = std::nullopt;
        Float32
            closest_distance_sq  = std::numeric_limits<Float32>::infinity();
        for (const auto& object : m_objects) {
            const auto intersection = object->Intersect(ray);
            if (!intersection)
                continue;
            const Float32 distance_sq =
                maths::length_sq(ray.Origin - intersection->Point);
            if (closest_distance_sq > distance_sq) {
                closest_intersection = intersection;
                closest_distance_sq  = distance_sq;
            }
        }
        return closest_intersection;
    }

    void Scene::Clear() {
        m_objects.clear();
    }

    void Scene::Trace(const Camera& camera, const Vec4& sky_color,
            PixelBuffer& buffer) const {
        const USize
            width  = buffer.GetWidth(),
            height = buffer.GetHeight();
        const Float32
            du = 1.0f / Float32(width),
            dv = 1.0f / Float32(height);
        for (UIndex v = 0u; v < height; v++) {
            for (UIndex u = 0u; u < width; u++) {
                const Float32
                    ru = u * du,
                    rv = v * dv;
                const Ray  ray          = camera.ScreenCoordsToRay(ru, rv);
                const auto intersection = Intersect(ray);
                buffer.At(u, v) = intersection.has_value()
                                ? intersection->Material.Color
                                : sky_color;
            }
        }
    }

}
