#ifndef __gorn__VertexArray__
#define __gorn__VertexArray__

#include <gorn/render/Enums.hpp>
#include <gorn/render/Gl.hpp>
#include <vector>
#include <map>
#include <memory>

namespace gorn
{
    class VertexBuffer;
    class VertexDefinition;
    class AttributeDefinition;
    class Material;
    class Program;
    class UniformValue;

    class VertexArray
    {
    public:
        typedef std::map<std::string, UniformValue> UniformValueMap;
    private:
        static GLuint s_currentId;
        mutable GLuint _id;
        std::shared_ptr<VertexBuffer> _elementVbo;
        BasicType _elementType;
        std::vector<std::shared_ptr<VertexBuffer>> _vertexVbos;
        std::shared_ptr<Program> _program;
        std::shared_ptr<Material> _material;

    public:
        VertexArray();
        ~VertexArray();
        GLuint getId() const;

        void bind() const;
        void activate() const;
        void setAttribute(const std::shared_ptr<VertexBuffer>& vbo, const AttributeDefinition& def);
        void addVertexData(const std::shared_ptr<VertexBuffer>& vbo, const VertexDefinition& def);
        void setElementData(const std::shared_ptr<VertexBuffer>& vbo, BasicType type=BasicType::UnsignedInteger);
        void setProgram(const std::shared_ptr<Program>& program);
        void setMaterial(const std::shared_ptr<Material>& material);
        const std::shared_ptr<Program>& getProgram() const;
        const std::shared_ptr<Material>& getMaterial() const;
        void setUniformValue(const std::string& name, const UniformValue& value);
	    void setUniformValue(const GLint& location, const UniformValue& value);
        void setUniformValues(const UniformValueMap& values);

        void draw(size_t count, DrawMode mode=DrawMode::Triangles, size_t offset=0);
    };
}

#endif
