#ifndef __gorn__GlEnums__
#define __gorn__GlEnums__

#include <gorn/render/Gl.hpp>
#include <gorn/render/Enums.hpp>

namespace gorn
{
    GLenum getGlDrawMode(DrawMode mode);
    GLenum getGlBasicType(BasicType type);
}

#endif

