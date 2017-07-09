#ifndef __gorn__MaterialDefinition__
#define __gorn__MaterialDefinition__

#include <gorn/gl/Base.hpp>
#include <gorn/gl/UniformValue.hpp>
#include <string>
#include <unordered_map>

namespace gorn
{
    class MaterialDefinition
    {
    public:
        typedef std::unordered_map<UniformKind, std::string> Textures;
    private:
        std::string _program;
        Textures _textures;
        UniformValueMap _uniformValues;

    public:
        MaterialDefinition();
        MaterialDefinition& withProgram(
            const std::string& program);
		MaterialDefinition& withTexture(
			const UniformKind& kind, const std::string& value);
        MaterialDefinition& withUniformValue(
			const UniformKind& kind, const UniformValue& value);

        const std::string& getProgram() const;
        const Textures& getTextures() const;
        const UniformValueMap& getUniformValues() const;

		Textures& getTextures();
		UniformValueMap& getUniformValues();
    };

}

#endif
