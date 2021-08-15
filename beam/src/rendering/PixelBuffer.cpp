#include "Common.hpp"
#include "PixelBuffer.hpp"

namespace beam {

    PixelBuffer::PixelBuffer(UCount width, UCount height)
        : m_width(width)
        , m_height(height)
        , m_buffer(new Pixel[width * height])
        , m_texture_id(0u)
    {
        for (UIndex v = 0u; v < height; v++)
            for (UIndex u = 0u; u < width; u++)
                At(u, v) = colors::Black;
        glCreateTextures(GL_TEXTURE_2D, 1, &m_texture_id);
        glTextureStorage2D(m_texture_id, 1, GL_RGBA32F, static_cast<GLsizei>(width),
            static_cast<GLsizei>(height));
    }

    PixelBuffer::~PixelBuffer() {
        glDeleteTextures(1, &m_texture_id);
        delete[] m_buffer;
    }

    void PixelBuffer::BufferData() const {
        glTextureSubImage2D(m_texture_id, 0, 0, 0, static_cast<GLsizei>(m_width),
            static_cast<GLsizei>(m_height), GL_RGBA, GL_FLOAT, m_buffer);
    }

    void PixelBuffer::BindTexture(GLuint slot) const {
        glBindTextureUnit(slot, m_texture_id);
    }

}
