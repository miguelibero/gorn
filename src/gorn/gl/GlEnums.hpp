#ifndef __gorn__GlEnums__
#define __gorn__GlEnums__

#include <gorn/render/RenderEnums.hpp>
#include <gorn/gl/GlBase.hpp>

namespace gorn
{
    enum class FrameBufferAttachType
    {
        Depth,
        Color,
        Stencil
    };

    GLenum getGlDrawMode(DrawMode mode);
    GLenum getGlBasicType(BasicType type);
}

#endif

