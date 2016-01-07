
#include <gorn/gl/Enums.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{
    size_t getBasicTypeSize(BasicType type)
    {
        switch(type)
        {
            case BasicType::Byte:
                return 1;
            case BasicType::UnsignedByte:
                return 1;
            case BasicType::Short:
                return sizeof(short);
            case BasicType::UnsignedShort:
                return sizeof(unsigned short);
            case BasicType::Integer:
                return sizeof(int);
            case BasicType::UnsignedInteger:
                return sizeof(unsigned int);
            case BasicType::Float:
                return sizeof(float);
            default:
                return 0;               
        }
    }

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

    StencilFunction getStencilFunctionFromGl(GLenum gl)
    {
        if(gl == GL_ALWAYS)
        {
            return StencilFunction::Always;
        }
        else if(gl == GL_NEVER)
        {
            return StencilFunction::Never;
        }
        else if(gl == GL_LESS)
        {
            return StencilFunction::Less;
        }
        else if(gl == GL_LEQUAL)
        {
            return StencilFunction::LessEqual;
        }
        else if(gl == GL_GREATER)
        {
            return StencilFunction::Greater;
        }
        else if(gl == GL_GEQUAL)
        {
            return StencilFunction::GreaterEqual;
        }
        else if(gl == GL_EQUAL)
        {
            return StencilFunction::Equal;
        }
        else if(gl == GL_NOTEQUAL)
        {
            return StencilFunction::NotEqual;
        }
        else
        {
            throw Exception("Invalid OpenGL stencil function.");
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

    StencilAction getStencilActionFromGl(GLenum gl)
    {
        if(gl == GL_KEEP)
        {
            return StencilAction::Keep;
        }
        else if(gl == GL_ZERO)
        {
            return StencilAction::Zero;
        }
        else if(gl == GL_REPLACE)
        {
            return StencilAction::Replace;
        }
        else if(gl == GL_INCR)
        {
            return StencilAction::Increment;
        }
        else if(gl == GL_INCR_WRAP)
        {
            return StencilAction::IncrementWrap;
        }
        else if(gl == GL_DECR)
        {
            return StencilAction::Decrement;
        }
        else if(gl == GL_DECR_WRAP)
        {
            return StencilAction::DecrementWrap;
        }
        else if(gl == GL_INVERT)
        {
            return StencilAction::Invert;
        }
        else
        {
            throw Exception("Invalid OpenGL stencil action.");
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

    GLbitfield getGlClearBufferBit(ClearType type)
    {
        switch(type)
        {
            case ClearType::Color:
                return GL_COLOR_BUFFER_BIT;
            case ClearType::Stencil:
                return GL_STENCIL_BUFFER_BIT;
            case ClearType::Depth:
                return GL_DEPTH_BUFFER_BIT;
            default:
                return 0;
        }
    }

    GLenum getGlTest(TestType type)
    {
        switch(type)
        {
            case TestType::Stencil:
                return GL_STENCIL_TEST;
            case TestType::Depth:
                return GL_DEPTH_TEST;
            default:
                return 0;
        }
    }

}
