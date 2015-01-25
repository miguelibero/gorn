#ifndef __gorn__Program__
#define __gorn__Program__

#include <gorn/render/Gl.hpp>
#include <gorn/render/Shader.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <map>

namespace gorn
{
    class UniformValue;

	class Program
	{
    private:
		static GLuint s_currentId;
		GLuint _id;
		std::shared_ptr<Shader> _vertexShader;
		std::shared_ptr<Shader> _fragmentShader;
        mutable std::map<std::string, GLint> _uniforms;
        mutable std::map<std::string, GLint> _attributes;
	public:
		Program(const std::shared_ptr<Shader>& vertexShader,
            const std::shared_ptr<Shader>& fragmentShader);
		~Program();

        void use() const;
		GLuint getId() const;
		const Shader& getFragmentShader() const;
		const Shader& getVertexShader() const;

        GLint loadAttribute(const std::string& name, const std::string& alias);
        GLint loadUniform(const std::string& name, const std::string& alias);

        GLint getAttribute(const std::string& name) const;
	    GLint getUniform(const std::string& name) const;

        void setUniformValue(const std::string& name,
            const UniformValue& value);
	    void setUniformValue(const GLint& location, const UniformValue& value);

    };
}

#endif
