#ifndef __gorn__ProgramDefinition__
#define __gorn__ProgramDefinition__

#include <gorn/render/Gl.hpp>
#include <string>
#include <vector>
#include <initializer_list>

namespace gorn
{

	class ProgramDefinition
	{
	private:
		std::string _vertexShader;
		std::string _fragmentShader;
		std::vector<std::string> _uniforms;
		std::vector<std::string> _attributes;

	public:
		ProgramDefinition();
        ProgramDefinition& withShader(const std::string& shader);
        ProgramDefinition& withVertexShader(const std::string& shader);
        ProgramDefinition& withFragmentShader(const std::string& shader);
		ProgramDefinition& withUniforms(std::initializer_list<std::string> list);
		ProgramDefinition& withAttributes(std::initializer_list<std::string> list);

		const std::string& getVertexShader() const;
		const std::string& getFragmentShader() const;
		const std::vector<std::string> getUniforms() const;
		const std::vector<std::string> getAttributes() const;
	};

}

#endif
