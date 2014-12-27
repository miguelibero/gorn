#ifndef __gorn__Program__
#define __gorn__Program__

#include <gorn/render/Gl.hpp>
#include <gorn/render/Shader.hpp>
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
		GLuint getId() const;
		const Shader& getFragmentShader() const;
		const Shader& getVertexShader() const;
	};
}

#endif