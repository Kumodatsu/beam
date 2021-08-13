#pragma once
#include "raytracing/Raytracing.hpp"
#include "raytracing/Camera.hpp"
#include "rendering/Renderer.hpp"

namespace beam {

    class AABB : public Intersectable {
    public:
        Float32 XMin, XMax, YMin, YMax, ZMin, ZMax;

        AABB()
            : XMin(-std::numeric_limits<Float32>::infinity())
            , XMax( std::numeric_limits<Float32>::infinity())
            , YMin(-std::numeric_limits<Float32>::infinity())
            , YMax( std::numeric_limits<Float32>::infinity())
            , ZMin(-std::numeric_limits<Float32>::infinity())
            , ZMax( std::numeric_limits<Float32>::infinity())
        { }
        AABB(Float32 x_min, Float32 x_max, Float32 y_min, Float32 y_max,
                Float32 z_min, Float32 z_max)
            : XMin(x_min), XMax(x_max), YMin(y_min), YMax(y_max), ZMin(z_min),
                ZMax(z_max) { }

        virtual AABB GetBoundingBox() const override;
        virtual std::optional<Intersection> Intersect(const Ray& ray)
            const override;
        virtual bool Intersects(const Ray& ray) const override;

        void Combine(const AABB& aabb);

        static AABB OverarchingAABB(const AABB& a, const AABB& b);

        inline static AABB Infinite() { return AABB(); }
        inline static AABB Nothing() {
            return AABB(
                 std::numeric_limits<Float32>::infinity(),
                -std::numeric_limits<Float32>::infinity(),
                 std::numeric_limits<Float32>::infinity(),
                -std::numeric_limits<Float32>::infinity(),
                 std::numeric_limits<Float32>::infinity(),
                -std::numeric_limits<Float32>::infinity()
            );
        }
    };

    class Sphere : public Intersectable {
    public:
        Vec3     Center;
        Float32  Radius;
        Material Material;

        Sphere(const beam::Material& material, const Vec3& center,
                Float32 radius)
            : Center(center), Radius(radius), Material(material) { }
        
        virtual AABB GetBoundingBox() const override;
        virtual std::optional<Intersection> Intersect(const Ray& ray)
            const override;
    };

    class Plane : public Intersectable {
    public:
        // The plane is defined by the set of all points (x, y, z) that obey:
        // x * Normal.X + y * Normal.Y + z * Normal.Z + D == 0.0f
        Vec3     Normal;
        Float32  D;
        Material Material;

        Plane(const beam::Material& material, const Vec3& normal, Float32 d)
            : Normal(normal), D(d), Material(material) { }

        Plane(const beam::Material& material, const Vec3& normal,
                const Vec3& point)
            : Normal(normal), D(-maths::dot(normal, point)), Material(material)
        { }

        virtual AABB GetBoundingBox() const override;
        virtual std::optional<Intersection> Intersect(const Ray& ray)
            const override;
    };

    class Scene : public Intersectable {
    public:
        Scene() { }

        template <typename IntersectableT, typename... Args>
        Scene& Add(Args&&... args) {
            m_objects.emplace_back(std::make_unique<IntersectableT>(args...));
            return *this;
        }

        virtual AABB GetBoundingBox() const override;
        virtual std::optional<Intersection> Intersect(const Ray& ray)
            const override;

        void Clear();
        void Trace(const Camera& camera, const Vec4& sky_color,
            PixelBuffer& buffer) const;
    private:
        std::vector<std::unique_ptr<Intersectable>> m_objects;
    };

}
