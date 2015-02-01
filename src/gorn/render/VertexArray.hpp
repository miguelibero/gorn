#ifndef __gorn__VertexArray__
#define __gorn__VertexArray__

#include <gorn/render/Gl.hpp>
#include <vector>
#include <memory>

namespace gorn
{
    class VertexBuffer;
    class VertexDefinition;
    class AttributeDefinition;
    class Material;
    class Program;
    class UniformValue;

    enum class VertexArrayDrawMode
    {
        Triangles,
        Quads,
        Lines,
        Points
    };

    class VertexArray
    {
    public:
        typedef VertexArrayDrawMode DrawMode;
    private:
        static GLuint s_currentId;
        mutable GLuint _id;
        std::shared_ptr<VertexBuffer> _elementVbo;
        GLenum _elementType;
        std::vector<std::shared_ptr<VertexBuffer>> _vertexVbos;
        std::shared_ptr<Program> _program;
        std::shared_ptr<Material> _material;

        static GLenum getGlDrawMode(DrawMode mode);
    public:
        VertexArray();
        ~VertexArray();
        GLuint getId() const;

        void bind() const;
        void activate() const;
        void setAttribute(GLuint attribute, const std::shared_ptr<VertexBuffer>& buffer,
            GLenum type, GLboolean normalized, GLint size,
            GLsizei stride=0, GLsizei offset=0);
        void setAttribute(const std::shared_ptr<VertexBuffer>& vbo, const AttributeDefinition& def);
        void addVertexData(const std::shared_ptr<VertexBuffer>& vbo, const VertexDefinition& def);
        void setElementData(const std::shared_ptr<VertexBuffer>& vbo, GLenum type=GL_UNSIGNED_INT);
        void setProgram(const std::shared_ptr<Program>& program);
        void setMaterial(const std::shared_ptr<Material>& material);
        const std::shared_ptr<Program>& getProgram() const;
        const std::shared_ptr<Material>& getMaterial() const;
        void setUniformValue(const std::string& name, const UniformValue& value);
	    void setUniformValue(const GLint& location, const UniformValue& value);

        void draw(GLsizei count, DrawMode mode, GLint offset=0);
    };
}

#endif
