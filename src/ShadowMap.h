#pragma once

#include <gl3w/GL/gl3w.h>
#include <glm/glm.hpp>
#include "ShaderHandler.h"

#include <memory>

namespace shadow_constants {
    static const unsigned int WIDTH = 1024;
    static const unsigned int HEIGHT = 1024;

    static const float NEAR_PLANE = 1.0f;
    static const float FAR_PLANE = 7.5f;
}

class ShadowMap {
public:
    ShadowMap(const std::shared_ptr<ShaderHandler> & shader_handler);
    void setup() const;

private:
    void initBuffers();

    GLuint m_fbo;
    GLuint m_depth_map;

    glm::vec3 m_light_pos;

    std::shared_ptr<ShaderHandler> m_shader_handler;
};
