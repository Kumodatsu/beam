#include "Common.hpp"
#include "Camera.hpp"

namespace beam {

    Camera::Camera(Float32 aspect, Float32 fov_deg, Vec3 position,
            Vec3 direction, Float32 focal_distance, Float32 aperture_radius)
        : m_position(position)
        , m_forward(direction)
        , m_right(maths::normalized(maths::cross(Vec3(0.0f, 1.0f, 0.0f),
            direction)))
        , m_up(maths::cross(direction, m_right))
        , m_screen_scale(FOVToScreenScale(fov_deg))
        , m_screen_aspect(aspect)
        , m_focal_distance(focal_distance)
        , m_aperture_radius(aperture_radius)
    { }

    Ray Camera::ScreenCoordsToRay(Float32 u, Float32 v) const {
        const Float32 scale = m_focal_distance * m_screen_scale;
        const Vec3 pixel_pos
            = m_position
            + m_focal_distance * m_forward
            + (u - 0.5f) * scale * m_right
            - (v - 0.5f) * scale * (1.0f / m_screen_aspect) * m_up;
        return Ray(pixel_pos, maths::normalized(pixel_pos - m_position));
    }

    void Camera::Move(const Vec3& movement) {
        m_position += movement;
    }

    void Camera::ResetRotation() {
        m_forward = Vec3(0.0f, 0.0f, 1.0f);
        m_up      = Vec3(0.0f, 1.0f, 0.0f);
        m_right   = maths::cross(m_up, m_forward);
    }

    void Camera::RotateVertically(Float32 /*angle_deg*/) {
        throw std::runtime_error("Not implemented.");
    }

    void Camera::RotateHorizontally(Float32 /*angle_deg*/) {
        throw std::runtime_error("Not implemented.");
    }

}
