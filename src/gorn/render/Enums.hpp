#ifndef __gorn__Enums__
#define __gorn__Enums__

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

    enum class FrameBufferAttachType
    {
        Depth,
        Color,
        Stencil
    };

    size_t getBasicTypeSize(BasicType type);
}

#endif
