#include "Common.hpp"
#include "Camera.hpp"

namespace beam {

    Camera::Camera(Float32 aspect, Float32 fov_deg, Vec3 position,
            Vec3 direction, Float32 focal_distance, Float32 aperture_radius)
        : m_position(position)
        , m_forward(direction)
        , m_right(glm::normalize(glm::cross(Vec3(0.0f, 1.0f, 0.0f),
            direction)))
        , m_up(glm::cross(direction, m_right))
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
        return Ray(pixel_pos, glm::normalize(pixel_pos - m_position));
    }

    void Camera::Move(const Vec3& movement) {
        m_position = m_position
            + movement.x * m_right
            + movement.y * Vec3 {0.0f, 1.0f, 0.0f}
            + movement.z * m_forward;
    }

    void Camera::ResetRotation() {
        m_forward = Vec3(0.0f, 0.0f, 1.0f);
        m_up      = Vec3(0.0f, 1.0f, 0.0f);
        m_right   = glm::cross(m_up, m_forward);
    }

    void Camera::RotateVertically(Float32 angle_deg) {
        glm::quat rot = glm::angleAxis(-glm::radians(angle_deg), m_right);
        glm::mat4 rotMatrix = glm::mat4_cast(rot);
        m_forward = rotMatrix * Vec4(m_forward, 0.0f);
        m_right   = rotMatrix * Vec4(m_right, 0.0f);
        m_up      = rotMatrix * Vec4(m_up, 0.0f);
    }

    void Camera::RotateHorizontally(Float32 angle_deg) {
        glm::quat rot = glm::angleAxis(glm::radians(angle_deg),
            Vec3 {0.0f, 1.0f, 0.0f});
        glm::mat4 rotMatrix = glm::mat4_cast(rot);
        m_forward = rotMatrix * Vec4(m_forward, 0.0f);
        m_right   = rotMatrix * Vec4(m_right, 0.0f);
        m_up      = rotMatrix * Vec4(m_up, 0.0f);
    }

}
