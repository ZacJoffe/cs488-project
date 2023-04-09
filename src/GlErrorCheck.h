#pragma once

#include <string>

#if(DEBUG)
    #define CHECK_GL_ERRORS checkGLErrors(__FILE__, __LINE__)
    #define CHECK_FRAMEBUFFER_COMPLETENESS checkFramebufferCompleteness()
#else
    #define CHECK_GL_ERRORS
    #define CHECK_FRAMEBUFFER_COMPLETENESS
#endif

void checkGLErrors(const std::string & curr_filename, int curr_linenum);
void checkFramebufferCompleteness();

