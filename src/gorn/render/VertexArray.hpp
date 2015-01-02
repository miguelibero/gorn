#ifndef __gorn__VertexArray__
#define __gorn__VertexArray__

#include <gorn/render/Gl.hpp>
#include <vector>
#include <memory>

namespace gorn
{
    class VertexBuffer;
    class VertexDefinition;
    class AttributeBinding;
    class Material;
    class Program;

    class VertexArray
    {
    private:
        static GLuint _currentId;
        mutable GLuint _id;
        std::vector<std::shared_ptr<VertexBuffer>> _vbos;
        std::shared_ptr<Program> _program;
        std::shared_ptr<Material> _material;
    public:
        VertexArray();
        ~VertexArray();
        GLuint getId() const;

        void bind() const;
        void bindAttribute(GLuint attribute, const std::shared_ptr<VertexBuffer>& buffer,
            GLenum type, GLboolean normalized, GLint size,
            GLsizei stride=0, GLsizei offset=0);
        AttributeBinding bindAttribute(const std::shared_ptr<VertexBuffer>& vbo);
        void bindData(const VertexDefinition& vdef, const std::shared_ptr<VertexBuffer>& vbo);
        void bindData(const std::shared_ptr<VertexBuffer>& vbo);
        void addData(const std::shared_ptr<VertexBuffer>& vbo);
        void bindProgram(const std::shared_ptr<Program>& program);
        void bindMaterial(const std::shared_ptr<Material>& material);
        const std::shared_ptr<Program>& getProgram() const;
        const std::shared_ptr<Material>& getMaterial() const;
    };
}

#endif
