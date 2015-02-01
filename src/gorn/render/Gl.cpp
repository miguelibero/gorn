#include <gorn/render/Gl.hpp>
#include <gorn/base/Exception.hpp>

#ifdef GORN_PLATFORM_ANDROID

#include <EGL/egl.h>

PFNGLGENVERTEXARRAYSOESPROC glGenVertexArraysOESEXT = 0;
PFNGLBINDVERTEXARRAYOESPROC glBindVertexArrayOESEXT = 0;
PFNGLDELETEVERTEXARRAYSOESPROC glDeleteVertexArraysOESEXT = 0;

void gornInitGlExtensions() {
     glGenVertexArraysOESEXT = (PFNGLGENVERTEXARRAYSOESPROC)
        eglGetProcAddress("glGenVertexArraysOES");
     glBindVertexArrayOESEXT = (PFNGLBINDVERTEXARRAYOESPROC)
        eglGetProcAddress("glBindVertexArrayOES");
     glDeleteVertexArraysOESEXT = (PFNGLDELETEVERTEXARRAYSOESPROC)
        eglGetProcAddress("glDeleteVertexArraysOES");
}

#endif

namespace gorn
{
    void checkGlError(const char* what)
    {
        GLenum glErr = glGetError();
        if (glErr != GL_NO_ERROR)
        {
            throw gorn::Exception(std::string("OpenGL error ")+
                what+":"+(const char*)gluErrorString(glErr));
        }
    }
}
