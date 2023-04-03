#include "Texture.h"

#include <gl3w/GL/gl3w.h>

#include <stdexcept>

Texture::Texture(const std::string & filename) : m_filename(filename) {
    glGenTextures(1, &m_tex);
    glBindTexture(GL_TEXTURE_2D, m_tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int x, y, n;
    unsigned char * data = m_image_loader.load(m_filename, &x, &y, &n);
    if (data == nullptr) {
        throw std::runtime_error("Unable to load texture");
    }

    // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    if (n == 3) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    } else if (n == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    } else {
        throw std::runtime_error(&"Unexpected number of components per pixel: " [ n]);
    }

    glGenerateMipmap(GL_TEXTURE_2D);
    m_image_loader.free(data);
}

void Texture::bind(GLenum texture_unit) const {
    glActiveTexture(texture_unit);
    glBindTexture(GL_TEXTURE_2D, m_tex);
}

