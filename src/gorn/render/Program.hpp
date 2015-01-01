#ifndef __gorn__Program__
#define __gorn__Program__

#include <gorn/render/Gl.hpp>
#include <gorn/render/Shader.hpp>
#include <glm/glm.hpp>
#include <memory>

namespace gorn
{
	class Program
	{
		GLuint _id;
		std::shared_ptr<Shader> _fragmentShader;
		std::shared_ptr<Shader> _vertexShader;
	public:
		Program(const std::shared_ptr<Shader>& fragmentShader, const std::shared_ptr<Shader>& vertexShader);
		~Program();

        void use() const;
		GLuint getId() const;
		const Shader& getFragmentShader() const;
		const Shader& getVertexShader() const;

        GLint getAttribute(const std::string& name) const;
	    GLint getUniform(const std::string& name) const;
	    void setUniform(const GLint& uniform, int value);
	    void setUniform(const GLint& uniform, float value);
	    void setUniform(const GLint& uniform, const glm::vec2& value);
	    void setUniform(const GLint& uniform, const glm::vec3& value);
	    void setUniform(const GLint& uniform, const glm::vec4& value);
	    void setUniform(const GLint& uniform, const std::vector<float>& values);
	    void setUniform(const GLint& uniform, const std::vector<glm::vec2>& values);
	    void setUniform(const GLint& uniform, const std::vector<glm::vec3>& values);
	    void setUniform(const GLint& uniform, const std::vector<glm::vec4>& values);
	    void setUniform(const GLint& uniform, const glm::mat3& value);
	    void setUniform(const GLint& uniform, const glm::mat4& value);
    };
}

#endif
