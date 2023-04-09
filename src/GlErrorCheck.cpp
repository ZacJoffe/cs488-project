#include "GlErrorCheck.h"
#include <gl3w/GL/gl3w.h>
#include <gl3w/GL/glcorearb.h>

#include <sstream>
#include <stdexcept>

std::string getErrorString(GLenum err_code) {
    switch (err_code) {
        case GL_NO_ERROR:
            break;
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            return "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            return "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            return "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            return "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
        case GL_FRAMEBUFFER_UNSUPPORTED:
            return "GL_FRAMEBUFFER_UNSUPPORTED";
        case GL_FRAMEBUFFER_UNDEFINED:
            return "GL_FRAMEBUFFER_UNDEFINED";
        default:
            break;
    }
    return "";
};

void checkGLErrors(const std::string & curr_filename, int curr_linenum) {
    GLenum err_code;
    bool err_found = false;
    std::stringstream err;

    // TODO refactor this
    do {
        err_code = glGetError();
        if (err_code != GL_NO_ERROR) {
            err << "[GL Error " << err_code <<  " " << getErrorString(err_code) << " "
                    << " caused by " << curr_filename << ":" << curr_linenum << "]" << std::endl;
            err_found = true;
        }
        err_code = glGetError();
    } while (err_code != GL_NO_ERROR);

    if (err_found) {
        throw std::runtime_error(err.str());
    }
}

void checkFramebufferCompleteness() {
    const GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        std::stringstream err;
        err << "Framebuffer not complete. " << getErrorString(status) << std::endl;
        throw std::runtime_error(err.str());
    }
}

