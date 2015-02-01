#ifndef __gorn__Enums__
#define __gorn__Enums__

#include <cstdlib>

namespace gorn
{
    enum class DrawMode
    {
        Triangles,
        Quads,
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

    size_t getSize(BasicType type);
}

#endif
