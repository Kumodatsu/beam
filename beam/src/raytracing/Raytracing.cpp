#include "Common.hpp"
#include "Raytracing.hpp"

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
        return Intersection(P, maths::normalized(P - Center));
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

}
