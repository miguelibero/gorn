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

    enum class ClearType
    {
        Color,
        Depth,
        Stencil
    };

    enum class FeatureType
    {
        DepthTest,
        StencilTest,
        AlphaTest,
        RedMask,
        GreenMask,
        BlueMask,
        AlphaMask
    };

    GLenum getGlDrawMode(DrawMode mode);
    GLenum getGlBasicType(BasicType type);

    StencilFunction getStencilFunctionFromGl(GLenum gl);
    GLenum getGlStencilFunction(StencilFunction func);
    StencilAction getStencilActionFromGl(GLenum gl);
    GLenum getGlStencilAction(StencilAction act);

    GLbitfield getGlClearBufferBit(ClearType type);
    GLenum getGlFeature(FeatureType type);
}

#endif

