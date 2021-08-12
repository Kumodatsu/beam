#pragma once

namespace beam::maths {

    struct Vec3 {
        Float32 X, Y, Z;
        
        constexpr Vec3() : Vec3(0.0f, 0.0f, 0.0f) { }
        constexpr Vec3(Float32 x, Float32 y, Float32 z) : X(x), Y(y), Z(z) { }
    };

    // Component-wise operations

    inline constexpr Vec3 operator + (const Vec3& a, const Vec3& b) {
        return Vec3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
    }

    inline constexpr Vec3 operator - (const Vec3& a, const Vec3& b) {
        return Vec3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
    }

    inline constexpr Vec3 operator * (const Vec3& a, const Vec3& b) {
        return Vec3(a.X * b.X, a.Y * b.Y, a.Z * b.Z);
    }

    inline constexpr Vec3 operator / (const Vec3& a, const Vec3& b) {
        return Vec3(a.X / b.X, a.Y / b.Y, a.Z / b.Z);
    }

    // Scalar operations

    inline constexpr Vec3 operator * (Float32 s, const Vec3& v) {
        return Vec3(s * v.X, s * v.Y, s * v.Z);
    }

    inline constexpr Vec3 operator * (const Vec3& v, Float32 s) {
        return Vec3(s * v.X, s * v.Y, s * v.Z);
    }

    inline constexpr Vec3 operator / (const Vec3& v, Float32 s) {
        return Vec3(v.X / s, v.Y / s, v.Z / s);
    }

    inline constexpr Vec3 operator - (const Vec3& v) {
        return -1.0f * v;
    }

    // Assignment operators

    inline constexpr Vec3& operator += (Vec3& a, const Vec3& b) {
        return a = a + b;
    }

    inline constexpr Vec3& operator -= (Vec3& a, const Vec3& b) {
        return a = a - b;
    }

    inline constexpr Vec3& operator *= (Vec3& a, const Vec3& b) {
        return a = a * b;
    }

    inline constexpr Vec3& operator /= (Vec3& a, const Vec3& b) {
        return a = a / b;
    }

    inline constexpr Vec3& operator *= (Vec3& v, Float32 s) {
        return v = s * v;
    }

    inline constexpr Vec3& operator /= (Vec3& v, Float32 s) {
        return v = v / s;
    }

    // Equality operations

    inline constexpr bool operator == (const Vec3& a, const Vec3& b) {
        return a.X == b.X && a.Y == b.Y && a.Z == b.Z;
    }

    inline constexpr bool operator != (const Vec3& a, const Vec3& b) {
        return a.X != b.X || a.Y != b.Y || a.Z != b.Z;
    }

    // Other operations

    inline constexpr Float32 dot(const Vec3& a, const Vec3& b) {
        return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
    }

    inline constexpr Float32 length_sq(const Vec3& v) {
        return dot(v, v);
    }

    inline constexpr Float32 length(const Vec3& v) {
        return std::sqrt(length_sq(v));
    }

    inline constexpr Vec3 normalized(const Vec3& v) {
        return v / length(v);
    }

    inline void normalize(Vec3& v) {
        v /= length(v);
    }

    inline constexpr Vec3 cross(const Vec3& a, const Vec3& b) {
        return Vec3(
            a.Y * b.Z - a.Z * b.Y,
            a.Z * b.X - a.X * b.Z,
            a.X * b.Y - a.Y * b.X
        );
    }

    // Stream operator

    std::ostream& operator << (std::ostream& stream, const Vec3& v);

}

namespace beam {
    using Vec3 = ::beam::maths::Vec3;
}
