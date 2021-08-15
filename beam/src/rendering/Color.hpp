#pragma once

namespace beam {

    struct Color {
        Float32 R, G, B;

        constexpr Color()
            : Color(0.0f, 0.0f, 0.0f) { }
        constexpr Color(Float32 r, Float32 g, Float32 b)
            : R(r), G(g), B(b), m_alpha(1.0f) { }
    private:
        Float32 m_alpha; // For padding and possible future use.
    };

    // Some basic colors
    namespace colors {
        inline constexpr Color
            Black  = Color(0.0f, 0.0f, 0.0f),
            Blue   = Color(0.0f, 0.0f, 1.0f),
            Green  = Color(0.0f, 1.0f, 0.0f),
            Cyan   = Color(0.0f, 1.0f, 1.0f),
            Red    = Color(1.0f, 0.0f, 0.0f),
            Purple = Color(1.0f, 0.0f, 1.0f),
            Yellow = Color(1.0f, 1.0f, 0.0f),
            White  = Color(1.0f, 1.0f, 1.0f);
    }    

    // Component-wise operations

    inline constexpr Color operator + (const Color& a, const Color& b) {
        return Color(a.R + b.R, a.G + b.G, a.B + b.B);
    }

    inline constexpr Color operator - (const Color& a, const Color& b) {
        return Color(a.R - b.R, a.G - b.G, a.B - b.B);
    }

    // Scalar operations

    inline constexpr Color operator * (Float32 s, const Color& c) {
        return Color(s * c.R, s * c.G, s * c.B);
    }

    inline constexpr Color operator * (const Color& c, Float32 s) {
        return Color(s * c.R, s * c.G, s * c.B);
    }

    inline constexpr Color operator / (Float32 s, const Color& c) {
        return Color(s / c.R, s / c.G, s / c.B);
    }

    inline constexpr Color operator / (const Color& c, Float32 s) {
        return Color(c.R / s, c.G / s, c.B / s);
    }

    // Assignment operators

    inline constexpr Color& operator += (Color& a, const Color& b) {
        return a = a + b;
    }

    inline constexpr Color& operator -= (Color& a, const Color& b) {
        return a = a - b;
    }

    inline constexpr Color& operator *= (Color& v, Float32 s) {
        return v = s * v;
    }

    inline constexpr Color& operator /= (Color& v, Float32 s) {
        return v = v / s;
    }

    // Other operations

    inline constexpr Color blend(const Color& a, const Color& b) {
        return 0.5f * (a + b);
    }

    // Stream operator

    std::ostream& operator << (std::ostream& stream, const Color& v);

}
