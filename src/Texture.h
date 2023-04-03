#pragma once

#include <gl3w/GL/gl3w.h>
#include <gl3w/GL/glcorearb.h>

#include <string>

class Texture {
public:
    Texture(const std::string & filename);

    void bind(GLenum texture_unit) const;

private:
    std::string m_filename;
    GLuint m_tex;
};

