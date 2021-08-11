namespace beam::maths {

    struct Vec4 {
        Float32 X, Y, Z, W;
        
        constexpr Vec4() : Vec4(0.0f, 0.0f, 0.0f, 0.0f) { }
        constexpr Vec4(Float32 x, Float32 y, Float32 z, Float32 w)
            : X(x), Y(y), Z(z), W(w) { }
    };

    // Component-wise operations

    inline constexpr Vec4 operator + (const Vec4& a, const Vec4& b) {
        return Vec4(a.X + b.X, a.Y + b.Y, a.Z + b.Z, a.W + b.W);
    }

    inline constexpr Vec4 operator - (const Vec4& a, const Vec4& b) {
        return Vec4(a.X - b.X, a.Y - b.Y, a.Z - b.Z, a.W - b.W);
    }

    inline constexpr Vec4 operator * (const Vec4& a, const Vec4& b) {
        return Vec4(a.X * b.X, a.Y * b.Y, a.Z * b.Z, a.W * b.W);
    }

    inline constexpr Vec4 operator / (const Vec4& a, const Vec4& b) {
        return Vec4(a.X / b.X, a.Y / b.Y, a.Z / b.Z, a.W / b.W);
    }

    // Scalar operations

    inline constexpr Vec4 operator * (Float32 s, const Vec4& v) {
        return Vec4(s * v.X, s * v.Y, s * v.Z, s * v.W);
    }

    inline constexpr Vec4 operator * (const Vec4& v, Float32 s) {
        return Vec4(s * v.X, s * v.Y, s * v.Z, s * v.W);
    }

    inline constexpr Vec4 operator / (const Vec4& v, Float32 s) {
        return Vec4(v.X / s, v.Y / s, v.Z / s, v.W / s);
    }

    inline constexpr Vec4 operator - (const Vec4& v) {
        return -1.0f * v;
    }

    // Assignment operators

    inline constexpr Vec4& operator += (Vec4& a, const Vec4& b) {
        return a = a + b;
    }

    inline constexpr Vec4& operator -= (Vec4& a, const Vec4& b) {
        return a = a - b;
    }

    inline constexpr Vec4& operator *= (Vec4& a, const Vec4& b) {
        return a = a * b;
    }

    inline constexpr Vec4& operator /= (Vec4& a, const Vec4& b) {
        return a = a / b;
    }

    inline constexpr Vec4& operator *= (Vec4& v, Float32 s) {
        return v = s * v;
    }

    inline constexpr Vec4& operator /= (Vec4& v, Float32 s) {
        return v = v / s;
    }

    // Other operations

    inline constexpr Float32 dot(const Vec4& a, const Vec4& b) {
        return a.X * b.X + a.Y * b.Y + a.Z * b.Z + a.W * b.W;
    }

    inline constexpr Float32 length_sq(const Vec4& v) {
        return dot(v, v);
    }

    inline constexpr Float32 length(const Vec4& v) {
        return std::sqrt(length_sq(v));
    }

    inline constexpr Vec4 normalized(const Vec4& v) {
        return v / length(v);
    }

    inline void normalize(Vec4& v) {
        v /= length(v);
    }

    // Stream operator

    std::ostream& operator << (std::ostream& stream, const Vec4& v);

}

namespace beam {
    using Vec4 = ::beam::maths::Vec4;
}
