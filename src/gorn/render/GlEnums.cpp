
#include <gorn/render/GlEnums.hpp>
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
}
