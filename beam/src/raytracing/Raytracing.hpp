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

    enum class MaterialType : UInt8 {
        Diffuse
    };

    struct Material {
        MaterialType Type;
        Vec4         Color;
        Float32      Emission;

        constexpr Material()
            : Type(MaterialType::Diffuse)
            , Color(Vec4(1.0f, 1.0f, 1.0f, 1.0f))
            , Emission(0.0f)
        { }
        constexpr Material(MaterialType type, Vec4 color, Float32 emission)
            : Type(type), Color(color), Emission(emission) { }
    };

    struct Intersection {
        Vec3     Point,
                 Normal;
        Material Material;

        constexpr Intersection()
            : Point(Vec3(0.0f, 0.0f, 0.0f))
            , Normal(Vec3(0.0f, 1.0f, 0.0f))
            , Material()
        { }
        constexpr Intersection(
            const Vec3& point,
            const Vec3& normal,
            const beam::Material& material
        ) : Point(point), Normal(normal), Material(material) { }
    };

    class Intersectable {
    public:
        Intersectable() { }
        virtual ~Intersectable() { }
        
        virtual std::optional<Intersection> Intersect(const Ray& ray) const = 0;
    };

}
