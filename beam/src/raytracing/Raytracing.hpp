#pragma once
#include "maths/Vec3.hpp"
#include "maths/Vec4.hpp"

namespace beam {

    // Hi, Ray!
    struct Ray {
        Vec3 Origin, Direction;
        
        constexpr Ray(const Vec3& origin, const Vec3& direction)
            : Origin(origin), Direction(direction) { }
        
        inline constexpr Vec3 Traverse(Float32 t) const {
            return Origin + t * Direction;
        }
    };

    struct Intersection {
        Vec3 Point, Normal;

        constexpr Intersection()
            : Point(Vec3(0.0f, 0.0f, 0.0f)), Normal(Vec3(0.0f, 1.0f, 0.0f)) { }
        constexpr Intersection(Vec3 point, Vec3 normal)
            : Point(point), Normal(normal) { }
    };

    class Intersectable {
    public:
        Vec4 Color;

        Intersectable(const Vec4& color) : Color(color) { }
        virtual ~Intersectable() { }
        
        virtual std::optional<Intersection> Intersect(const Ray& ray) const = 0;
    };

    class Sphere : public Intersectable {
    public:
        Vec3    Center;
        Float32 Radius;

        Sphere(const Vec4& color, const Vec3& center, Float32 radius)
            : Intersectable(color), Center(center), Radius(radius) { }
        
        virtual std::optional<Intersection> Intersect(const Ray& ray)
            const override;
    };

    class Scene : public Intersectable {
    public:
        Scene() : Intersectable(Vec4(0.0f, 0.0f, 0.0f, 1.0f)) { }

        template <typename IntersectableT, typename... Args>
        Scene& Add(Args&&... args) {
            m_objects.emplace_back(std::make_unique<IntersectableT>(args...));
            return *this;
        }

        virtual std::optional<Intersection> Intersect(const Ray& ray)
            const override;
    private:
        std::vector<std::unique_ptr<Intersectable>> m_objects;
    };

}
