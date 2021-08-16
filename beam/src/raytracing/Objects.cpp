#include "Common.hpp"
#include "Objects.hpp"

namespace beam {

    // AABB

    AABB AABB::GetBoundingBox() const {
        return *this;
    }

    std::optional<Intersection> AABB::Intersect(const Ray&) const {
        return std::nullopt;
    }

    bool AABB::Intersects(const Ray& ray) const {
        const Vec3 inv_dir = 1.0f / ray.Direction;
        const Float32
            t_0   = inv_dir.x * (XMin - ray.Origin.x),
            t_1   = inv_dir.x * (XMax - ray.Origin.x),
            t_2   = inv_dir.y * (YMin - ray.Origin.y),
            t_3   = inv_dir.y * (YMax - ray.Origin.y),
            t_4   = inv_dir.z * (ZMin - ray.Origin.z),
            t_5   = inv_dir.z * (ZMax - ray.Origin.z),
            t_min = std::max(
                        std::max(std::min(t_0, t_1), std::min(t_2, t_3)),
                        std::min(t_4, t_5)
                    ),
            t_max = std::min(
                        std::min(std::max(t_0, t_1), std::max(t_2, t_3)),
                        std::max(t_4, t_5)
                    );
        return t_max >= 0.0f && t_max >= t_min;
    }

    void AABB::Combine(const AABB& aabb) {
        XMin = std::min(XMin, aabb.XMin);
        XMax = std::max(XMax, aabb.XMax);
        YMin = std::min(YMin, aabb.YMin);
        YMax = std::max(YMax, aabb.YMax);
        ZMin = std::min(ZMin, aabb.ZMin);
        ZMax = std::max(ZMax, aabb.ZMax);
    }

    AABB AABB::OverarchingAABB(const AABB& a, const AABB& b) {
        return AABB(
            std::min(a.XMin, b.XMin),
            std::max(a.XMax, b.XMax),
            std::min(a.YMin, b.YMin),
            std::max(a.YMax, b.YMax),
            std::min(a.ZMin, b.ZMin),
            std::max(a.ZMax, b.ZMax)
        );
    }

    // Sphere

    AABB Sphere::GetBoundingBox() const {
        return AABB(
            Center.x - Radius,
            Center.x + Radius,
            Center.y - Radius,
            Center.y + Radius,
            Center.z - Radius,
            Center.z + Radius
        );
    }

    std::optional<Intersection> Sphere::Intersect(const Ray& ray) const {
        const Vec3
            O_C = ray.Origin - Center;
        const Float32
            a   = glm::dot(ray.Direction, ray.Direction),
            b   = 2.0f * glm::dot(ray.Direction, O_C),
            c   = glm::dot(O_C, O_C) - Radius * Radius,
            D   = b * b - 4.0f * a * c;
        if (D < 0.0f)
            return std::nullopt;
        const Float32
            s   = glm::sqrt(D),
            t_0 = (-b + s) / (2.0f * a),
            t_1 = (-b - s) / (2.0f * a),
            t   = (t_0 < 0.0f || t_1 < t_0) ? t_1 : t_0;
        if (t < 0.0f)
            return std::nullopt;
        const auto P = ray.Traverse(t);
        return Intersection(P, glm::normalize(P - Center), Material);
    }

    // Plane

    AABB Plane::GetBoundingBox() const {
        AABB aabb = AABB::Infinite();
        if (Normal.x > 0.0f && Normal.y == 0.0f && Normal.z == 0.0f)
            aabb.XMin = aabb.XMax = -D;
        else if (Normal.x == 0.0f && Normal.y > 0.0f && Normal.z == 0.0f)
            aabb.YMin = aabb.YMax = -D;
        else if (Normal.x == 0.0f && Normal.y == 0.0f && Normal.z > 0.0f)
            aabb.ZMin = aabb.ZMax = -D;
        return aabb;
    }

    std::optional<Intersection> Plane::Intersect(const Ray& ray) const {
        const Float32 t
            = -(glm::dot(ray.Origin,    Normal) + D)
            /   glm::dot(ray.Direction, Normal);
        if (t < 0.0f)
            return std::nullopt;
        const auto P = ray.Traverse(t);
        return Intersection(
            P,
            glm::dot(ray.Direction, Normal) > 0.0f ? -Normal : Normal,
            Material
        );
    }

    // Triangle

    AABB Triangle::GetBoundingBox() const {
        return AABB(
            std::min({m_A.x, m_B.x, m_C.x}),
            std::max({m_A.x, m_B.x, m_C.x}),
            std::min({m_A.y, m_B.y, m_C.y}),
            std::max({m_A.y, m_B.y, m_C.y}),
            std::min({m_A.z, m_B.z, m_C.z}),
            std::max({m_A.z, m_B.z, m_C.z})
        );
    }

    std::optional<Intersection> Triangle::Intersect(const Ray& ray) const {
        // Möller-Trumbore ray/triangle intersection algorithm, adapted from
        // https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
        constexpr Float32 epsilon = 1.0e-7f;
        const Vec3
            AB = m_B - m_A,
            AC = m_C - m_A,
            h  = glm::cross(ray.Direction, AC);
        const Float32 a = glm::dot(AB, h);
        if (-epsilon < a && a < epsilon)
            return std::nullopt; // The ray is parallel to the triangle
        const Float32 inv_a = 1.0f / a;
        const Vec3    AO    = ray.Origin - m_A;
        const Float32 u     = inv_a * glm::dot(AO, h);
        if (u < 0.0f || 1.0f < u)
            return std::nullopt;
        const Vec3    q = glm::cross(AO, AB);
        const Float32 v = inv_a * glm::dot(ray.Direction, q);
        if (v < 0.0f || 1.0f < u + v)
            return std::nullopt;
        const Float32 t = inv_a * glm::dot(AC, q);
        if (epsilon < t && t < 1.0f / epsilon)
            return Intersection(
                ray.Traverse(t),
                m_normal,
                Material
            );
        return std::nullopt;
    }

    // Scene

    AABB Scene::GetBoundingBox() const {
        AABB aabb = AABB::Nothing();
        for (const auto& object : m_objects)
            aabb.Combine(object->GetBoundingBox());
        return aabb;
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
                glm::length2(ray.Origin - intersection->Point);
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

    void Scene::Trace(const Camera& camera, const Color& sky_color,
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
