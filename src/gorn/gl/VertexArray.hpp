#ifndef __gorn__VertexArray__
#define __gorn__VertexArray__

#include <gorn/gl/Enums.hpp>
#include <gorn/gl/Base.hpp>
#include <gorn/gl/UniformValue.hpp>
#include <vector>
#include <memory>

namespace gorn
{
    class VertexBuffer;
    class VertexDefinition;
    class VertexAttributeDefinition;
    class Material;
    class Program;

    class VertexArray
    {
    private:
        static GLuint s_currentId;
        mutable GLuint _id;
        std::shared_ptr<VertexBuffer> _elementVbo;
        BasicType _elementType;
        std::vector<std::shared_ptr<VertexBuffer>> _vertexVbos;
        std::shared_ptr<Program> _program;
        std::shared_ptr<Material> _material;

        void cleanup();
        static void bindId(GLuint id);
    public:
        VertexArray();
        ~VertexArray();

        VertexArray(const VertexArray& other) = delete;
        VertexArray& operator=(const VertexArray& other) = delete;

        VertexArray(VertexArray&& other);
        VertexArray& operator=(VertexArray&& other);

        GLuint getId() const;
        void bind() const;
        static void unbind();
        void activate() const;
        void setAttribute(const std::shared_ptr<VertexBuffer>& vbo, const VertexAttributeDefinition& def);
        void addVertexData(const std::shared_ptr<VertexBuffer>& vbo, const VertexDefinition& def);
        void setElementData(const std::shared_ptr<VertexBuffer>& vbo, BasicType type=BasicType::UnsignedInteger);
        void setProgram(const std::shared_ptr<Program>& program);
        void setMaterial(const std::shared_ptr<Material>& material);
        const std::shared_ptr<Program>& getProgram() const;
        const std::shared_ptr<Material>& getMaterial() const;
        void setUniformValue(const std::string& name, const UniformValue& value);
        void setUniformValue(const GLint& location, const UniformValue& value);

        void draw(size_t count, DrawMode mode, size_t offset=0);
        void draw(size_t count, size_t offset=0);
    };
}

#endif
