
#include <gorn/render/Enums.hpp>
#include <gorn/render/Gl.hpp>

namespace gorn
{
    size_t getSize(BasicType type)
    {
        switch(type)
        {
            case BasicType::Byte:
                return sizeof(GLbyte);
            case BasicType::UnsignedByte:
                return sizeof(GLubyte);
            case BasicType::Short:
                return sizeof(GLshort);
            case BasicType::UnsignedShort:
                return sizeof(GLushort);
            case BasicType::Integer:
                return sizeof(GLint);
            case BasicType::UnsignedInteger:
                return sizeof(GLuint);
            case BasicType::Float:
                return sizeof(GLfloat);
            default:
                return 0;               
        }
    }
}

