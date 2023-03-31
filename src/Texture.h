#pragma once

#include "GL/gl3w.h"
#include "GL/glcorearb.h"
#include <string>

class Texture {
public:
    Texture(const std::string & filename);

    void bind(GLenum texture_unit);

private:
    std::string m_filename;
    GLuint m_tex;
};
