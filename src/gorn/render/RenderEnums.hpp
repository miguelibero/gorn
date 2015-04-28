#ifndef __gorn__RenderEnums__
#define __gorn__RenderEnums__

#include <cstdlib>

namespace gorn
{
    enum class DrawMode
    {
        Quads,
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
