
#include <gorn/render/RenderEnums.hpp>

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
}
