#ifndef __gorn__Enums__
#define __gorn__Enums__

#include <cstdlib>

namespace gorn
{
    enum class DrawMode
    {
        Triangles,
        Lines,
        Points
    };

    enum class BasicType
    {
        None,
        Float,
        Integer,
        UnsignedInteger,
        Byte,
        UnsignedByte,
        Short,
        UnsignedShort
    };

    size_t getBasicTypeSize(BasicType type);
}

#endif
