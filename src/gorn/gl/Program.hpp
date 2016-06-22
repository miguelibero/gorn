#ifndef __gorn__Program__
#define __gorn__Program__

#include <gorn/gl/Base.hpp>
#include <gorn/gl/Shader.hpp>
#include <gorn/gl/VertexDefinition.hpp>
#include <glm/glm.hpp>
#include <buffer.hpp>
#include <memory>
#include <map>
#include <vector>

namespace gorn
{
    class UniformValue;
    class ProgramDefinition;

    class Program
    {
    public:
        typedef ProgramDefinition Definition;
		typedef std::map<std::string, GLint> UniformMap;
		typedef std::map<std::string, GLint> AttributeMap;
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

		GLint getAttribute(const std::string& name) const;
        GLint getUniform(const std::string& name) const;

		const AttributeMap& getAttributes() const;
		const UniformMap& getUniforms() const;

        bool hasAttribute(const std::string& name) const;
        bool hasUniform(const std::string& name) const;

        void setUniformValue(const std::string& name,
            const UniformValue& value);
        void setUniformValue(const GLint& location,
            const UniformValue& value);

		const VertexDefinition& getVertexDefinition() const;

    };
}

#endif
