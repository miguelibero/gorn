#ifndef __gorn__Kinds__
#define __gorn__Kinds__

#include <string>

namespace gorn
{
    class AttributeKind
    {
    public:
        AttributeKind() = delete;
        static const char* Position;
        static const char* Normal;
        static const char* Color;
        static const char* TexCoords;

        static bool isTransformable(const std::string& name);
    };

    class UniformKind
    {
    public:
        UniformKind() = delete;
        static const char* Texture0;
        static const char* Texture1;
        static const char* Texture2;
        static const char* Texture3;
        static const char* Texture4;
        static const char* Texture5;
        static const char* Texture6;
        static const char* Color;
        static const char* Model;
        static const char* View;
        static const char* Projection;
    };
}

#endif
