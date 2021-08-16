#pragma once

namespace beam {

    using Color = glm::vec4;

    // Some basic colors

    namespace colors {
        inline constexpr Color
            Black  { 0.0f, 0.0f, 0.0f, 1.0f },
            Blue   { 0.0f, 0.0f, 1.0f, 1.0f },
            Green  { 0.0f, 1.0f, 0.0f, 1.0f },
            Cyan   { 0.0f, 1.0f, 1.0f, 1.0f },
            Red    { 1.0f, 0.0f, 0.0f, 1.0f },
            Purple { 1.0f, 0.0f, 1.0f, 1.0f },
            Yellow { 1.0f, 1.0f, 0.0f, 1.0f },
            White  { 1.0f, 1.0f, 1.0f, 1.0f };
    }

}
