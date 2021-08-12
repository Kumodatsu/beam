#pragma once
#include "maths/Trigonometry.hpp"
#include "maths/Vec3.hpp"
#include "raytracing/Raytracing.hpp"

namespace beam {

    class Camera {
    public:
        Camera(Float32 aspect, Float32 fov_deg, Vec3 position, Vec3 direction,
            Float32 focal_distance, Float32 aperture_radius);
        
        inline Vec3 GetPosition() const { return m_position; }

        Ray ScreenCoordsToRay(Float32 u, Float32 v) const;
        
        inline void SetPosition(const Vec3& position) {
            m_position = position;
        }

        inline void SetFOV(Float32 fov_deg) {
            m_screen_scale = FOVToScreenScale(fov_deg);
        }

        inline void SetFocalDistance(Float32 focal_distance) {
            m_focal_distance = focal_distance;
        }

        inline void SetApertureRadius(Float32 apreture_radius) {
            m_aperture_radius = apreture_radius;
        }

        void Move(const Vec3& movement);
        void ResetRotation();
        void RotateVertically(Float32 angle_deg);
        void RotateHorizontally(Float32 angle_deg);
    private:
        Vec3    m_position,
                m_forward,
                m_right,
                m_up;
        Float32 m_screen_scale,
                m_screen_aspect,
                m_focal_distance,
                m_aperture_radius;

        inline Float32 FOVToScreenScale(Float32 fov_deg) {
            return 2.0f * std::tan(0.5f * maths::deg_to_rad(fov_deg));
        }
    };

}
