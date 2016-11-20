#ifndef __gorn__Program__
#define __gorn__Program__

#include <gorn/gl/Base.hpp>
#include <gorn/gl/Shader.hpp>
#include <gorn/gl/VertexDefinition.hpp>
#include <gorn/gl/UniformKind.hpp>
#include <glm/glm.hpp>
#include <buffer.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

namespace gorn
{
    class UniformValue;
    class ProgramDefinition;

    class Program
    {
    public:
        typedef ProgramDefinition Definition;
		typedef std::unordered_map<UniformKind, GLint> UniformMap;
		typedef std::unordered_map<AttributeKind, GLint> AttributeMap;
    private:
        static GLuint s_currentId;
        GLuint _id;
        std::shared_ptr<Shader> _vertexShader;
        std::shared_ptr<Shader> _fragmentShader;
		VertexDefinition _vertexDefinition;
        mutable UniformMap _uniforms;
        mutable AttributeMap _attributes;
        void cleanup();
    public:
        Program(const std::shared_ptr<Shader>& vertexShader,
            const std::shared_ptr<Shader>& fragmentShader);
        ~Program();

        Program(const Program& other) = delete;
        Program& operator=(const Program& other) = delete;

        Program(Program&& other);
        Program& operator=(Program&& other);

        void use() const;
        GLuint getId() const;
        const Shader& getFragmentShader() const;
        const Shader& getVertexShader() const;

        void loadDefinition(const Definition& def);

		GLint getAttribute(const AttributeKind& kind) const;
        GLint getUniform(const UniformKind& name) const;

		const AttributeMap& getAttributes() const;
		const UniformMap& getUniforms() const;

        bool hasAttribute(const AttributeKind& kind) const;
        bool hasUniform(const UniformKind& kind) const;

        void setUniformValue(const UniformKind& kind,
            const UniformValue& value);
        void setUniformValue(const GLint& location,
            const UniformValue& value);

		const VertexDefinition& getVertexDefinition() const;

    };
}

#endif
