#pragma once

#include "GL/gl3w.h"
#include "GL/glcorearb.h"
#include <string>

class Texture {
public:
    Texture(const std::string & file_name);

    void bind(GLenum texture_unit);

private:
    std::string m_file_name;
    GLuint m_tex;
};
