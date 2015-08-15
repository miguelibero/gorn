#include <gorn/gl/Base.hpp>
#include <gorn/base/Exception.hpp>
#include <sstream>

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
            std::stringstream ss;
            ss << "OpenGL error " << glErr << " " << what;
            throw gorn::Exception(ss.str());
        }
    }
}
