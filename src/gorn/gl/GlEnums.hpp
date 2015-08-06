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

    enum class StencilFunction
    {
        Always,
        Never,
        Less,
        LessEqual,
        Greater,
        GreaterEqual,
        Equal,
        NotEqual
    };

    enum class StencilAction
    {
        Keep,
        Zero,
        Replace,
        Increment,
        IncrementWrap,
        Decrement,
        DecrementWrap,
        Invert
    };

    GLenum getGlDrawMode(DrawMode mode);
    GLenum getGlBasicType(BasicType type);
    GLenum getGlStencilFunction(StencilFunction func);
    GLenum getGlStencilAction(StencilAction act);
}

#endif

