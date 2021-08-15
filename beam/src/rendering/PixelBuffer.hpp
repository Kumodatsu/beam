#pragma once
#include "rendering/Color.hpp"
#include <glad/glad.h>

namespace beam {

    using Pixel = Color;

    class PixelBuffer {
    public:
        PixelBuffer(UCount width, UCount height);
        ~PixelBuffer();

        inline UCount GetWidth()  const { return m_width;  }
        inline UCount GetHeight() const { return m_height; }

        inline Pixel& At(UIndex u, UIndex v) {
            return m_buffer[u + m_width * (m_height - 1 - v)];
        }

        inline const Pixel& At(UIndex u, UIndex v) const {
            return m_buffer[u + m_width * (m_height - 1 - v)];
        }

        void BufferData() const;
        void BindTexture(GLuint slot) const;
    private:
        UCount m_width;
        UCount m_height;
        Pixel* m_buffer;
        GLuint m_texture_id;
    };

}
