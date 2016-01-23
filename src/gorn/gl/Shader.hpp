#ifndef __gorn__Shader__
#define __gorn__Shader__

#include <gorn/gl/Base.hpp>

class buffer;

namespace gorn
{
    enum class ShaderType
    {
        Vertex,
        Fragment
    };

    class Shader
    {
    private:
        GLuint _id;
    public:
        typedef ShaderType Type;

        Shader(const buffer& source, ShaderType type);
        ~Shader();
        GLuint getId() const;
    };
}

#endif
