#pragma once

namespace beam::maths {

    inline constexpr Float32 PI = 3.1415926535f;

    inline constexpr Float32 deg_to_rad(Float32 angle_deg) {
        return angle_deg / 360.0f * 2.0f * PI;
    }

    inline constexpr Float32 rad_to_deg(Float32 angle_rad) {
        return angle_rad / (2.0f * PI) * 360.0f;
    }

}
