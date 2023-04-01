#include "Texture.h"

#include <gl3w/GL/gl3w.h>

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb/stb_image.h"

#include <stdexcept>

Texture::Texture(const std::string & filename) : m_filename(filename) {
    glGenTextures(1, &m_tex);
    glBindTexture(GL_TEXTURE_2D, m_tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // force stbi to load image with origin coordinate being on bottom left of image
    stbi_set_flip_vertically_on_load(1);
    int x, y, n;
    unsigned char * data = stbi_load(m_filename.c_str(), &x, &y, &n, 0);
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
    stbi_image_free(data);
}


void Texture::bind(GLenum texture_unit) {
    glActiveTexture(texture_unit);
    glBindTexture(GL_TEXTURE_2D, m_tex);
}
