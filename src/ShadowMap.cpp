#include "ShadowMap.h"
#include <gl3w/GL/gl3w.h>
#include <gl3w/GL/glcorearb.h>
#include "GameState.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace shadow_constants;

ShadowMap::ShadowMap(const std::shared_ptr<ShaderHandler> & shader_handler) : m_shader_handler(shader_handler) {
    initBuffers();

    m_light_pos = glm::vec3(-2.0f, 4.0f, -1.0f);
}

void ShadowMap::setup() const {
    const glm::mat4 light_projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, NEAR_PLANE, FAR_PLANE);
    const glm::mat4 light_view = glm::lookAt(m_light_pos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    const glm::mat4 light_space = light_projection * light_view;

    m_shader_handler->enable();
    m_shader_handler->uploadMat4Uniform("light_space", light_space);

    // TODO make sure this works
    GLint old_viewport[4];
    glGetIntegerv(GL_VIEWPORT, old_viewport);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glClear(GL_DEPTH_BUFFER_BIT);


    glViewport(old_viewport[0], old_viewport[1], old_viewport[2], old_viewport[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ShadowMap::initBuffers() {
    glGenFramebuffers(1, &m_fbo);

    glGenTextures(1, &m_depth_map);
    glBindTexture(GL_TEXTURE_2D, m_depth_map);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, WIDTH, HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth_map, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
