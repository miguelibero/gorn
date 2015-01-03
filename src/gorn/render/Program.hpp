#ifndef __gorn__Program__
#define __gorn__Program__

#include <gorn/render/Gl.hpp>
#include <gorn/render/Shader.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <map>

namespace gorn
{
	class Program
	{
    private:
		static GLuint s_currentId;
		GLuint _id;
		std::shared_ptr<Shader> _fragmentShader;
		std::shared_ptr<Shader> _vertexShader;
        mutable std::map<std::string, GLint> _uniforms;
        mutable std::map<std::string, GLint> _attributes;
	public:
		Program(const std::shared_ptr<Shader>& fragmentShader, const std::shared_ptr<Shader>& vertexShader);
		~Program();

        void use() const;
		GLuint getId() const;
		const Shader& getFragmentShader() const;
		const Shader& getVertexShader() const;

        GLint getAttribute(const std::string& name) const;
	    GLint getUniform(const std::string& name) const;

        template<typename V>
        void setUniform(const std::string& uniform, const V& value)
        {
            setUniform<V>(getUniform(uniform), value);
        }

        template<typename V>
	    void setUniform(const GLint& uniform, const V& value);
    };
}

#endif
