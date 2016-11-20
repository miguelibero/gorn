#ifndef __gorn__Material__
#define __gorn__Material__

#include <gorn/gl/Program.hpp>
#include <gorn/gl/Texture.hpp>
#include <gorn/gl/UniformValue.hpp>
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

        void setTexture(const UniformKind& kind,
            const std::shared_ptr<Texture>& texture);
		void setUniformValues(const UniformValueMap& values);
        void setUniformValue(const UniformKind& kind,
            const UniformValue& value);

        const glm::vec2& getSize() const;
        const std::shared_ptr<Program>& getProgram() const;
        void activate();
    };

}

#endif
