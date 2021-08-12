#pragma once

namespace beam::maths {

    inline constexpr Float32 PI = 3.1415926535f;

    inline constexpr Float32 deg_to_rad(Float32 angle_deg) {
        return angle_deg / 360.0 * 2.0 * PI;
    }

    inline constexpr Float32 rad_to_deg(Float32 angle_rad) {
        return angle_rad / (2.0 * PI) * 360.0;
    }

}
