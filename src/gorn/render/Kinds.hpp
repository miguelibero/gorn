#ifndef __gorn__Kinds__
#define __gorn__Kinds__

namespace gorn
{
    class AttributeKind
    {
    private:
        AttributeKind();
    public:
        static const char* Position;
        static const char* Color;
        static const char* TexCoords;
    };

    class UniformKind
    {
    private:
        UniformKind();
    public:
        static const char* Texture0;
        static const char* Texture1;
        static const char* Texture2;
        static const char* Texture3;
        static const char* Texture4;
        static const char* Texture5;
        static const char* Texture6;
        static const char* Color;
        static const char* Transform;
    };
}

#endif
