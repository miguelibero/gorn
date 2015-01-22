#ifndef __gorn__Material__
#define __gorn__Material__

#include <gorn/render/Program.hpp>
#include <gorn/render/Texture.hpp>
#include <gorn/render/UniformValue.hpp>
#include <map>

namespace gorn
{
	class Material
	{
	private:
		std::shared_ptr<Program> _program;
		std::map<GLint, std::shared_ptr<Texture>> _textures;
        std::map<GLint, UniformValue> _uniformValues;

	public:
		Material(const std::shared_ptr<Program>& program);

		void setTexture(const std::string& name, const std::shared_ptr<Texture>& texture);
		void setUniformValue(const std::string& name, const UniformValue& value);

        const glm::vec2& getSize() const;
        float getScale() const;
		const std::shared_ptr<Program>& getProgram() const;
        void activate();
	};

}

#endif
