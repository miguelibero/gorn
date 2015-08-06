
#include <gorn/gl/GlEnums.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{
    GLenum getGlDrawMode(DrawMode mode)
    {
        switch(mode)
        {
            case DrawMode::Lines:
                return GL_LINES;
            case DrawMode::Points:
                return GL_POINTS;
            case DrawMode::Triangles:
                return GL_TRIANGLES;
            default:
                throw Exception("Unsupported draw mode.");
        }
    }

    GLenum getGlBasicType(BasicType type)
    {
        switch(type)
        {
            case BasicType::Byte:
                return GL_BYTE;
            case BasicType::UnsignedByte:
                return GL_UNSIGNED_BYTE;
            case BasicType::Short:
                return GL_SHORT;
            case BasicType::UnsignedShort:
                return GL_UNSIGNED_SHORT;
            case BasicType::Integer:
                return GL_INT;
            case BasicType::UnsignedInteger:
                return GL_UNSIGNED_INT;
            case BasicType::Float:
                return GL_FLOAT;
            default:
                return 0;               
        }
    }

    GLenum getGlStencilFunction(StencilFunction func)
    {
        switch(func)
        {
            case StencilFunction::Always:
                return GL_ALWAYS;
            case StencilFunction::Never:
                return GL_NEVER;
            case StencilFunction::Less:
                return GL_LESS;
            case StencilFunction::LessEqual:
                return GL_LEQUAL;
            case StencilFunction::Greater:
                return GL_GREATER;
            case StencilFunction::GreaterEqual:
                return GL_GEQUAL;
            case StencilFunction::Equal:
                return GL_EQUAL;
            case StencilFunction::NotEqual:
                return GL_NOTEQUAL;
            default:
                return 0;
        }
    }

    GLenum getGlStencilAction(StencilAction act)
    {
        switch(act)
        {
            case StencilAction::Keep:
                return GL_KEEP;
            case StencilAction::Zero:
                return GL_ZERO;
            case StencilAction::Replace:
                return GL_REPLACE;
            case StencilAction::Increment:
                return GL_INCR;
            case StencilAction::IncrementWrap:
                return GL_INCR_WRAP;
            case StencilAction::Decrement:
                return GL_DECR;
            case StencilAction::DecrementWrap:
                return GL_DECR_WRAP;
            case StencilAction::Invert:
                return GL_INVERT;
            default:
                return 0;
        }
    }

}
