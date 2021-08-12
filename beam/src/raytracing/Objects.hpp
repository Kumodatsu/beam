#pragma once
#include "raytracing/Raytracing.hpp"
#include "raytracing/Camera.hpp"
#include "rendering/Renderer.hpp"

namespace beam {

    class Sphere : public Intersectable {
    public:
        Vec3     Center;
        Float32  Radius;
        Material Material;

        Sphere(const beam::Material& material, const Vec3& center,
                Float32 radius)
            : Material(material), Center(center), Radius(radius) { }
        
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

        virtual std::optional<Intersection> Intersect(const Ray& ray)
            const override;

        void Clear();
        void Trace(const Camera& camera, const Vec4& sky_color,
            PixelBuffer& buffer) const;
    private:
        std::vector<std::unique_ptr<Intersectable>> m_objects;
    };

}
