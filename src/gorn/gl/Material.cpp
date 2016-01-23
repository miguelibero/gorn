#include <gorn/gl/Material.hpp>
#include <gorn/gl/UniformValue.hpp>

namespace gorn
{
    Material::Material(const std::shared_ptr<Program>& program):
    _program(program)
    {
    }

    void Material::setTexture(const std::string& name,
        const std::shared_ptr<Texture>& texture)
    {
        _textures[_program->getUniform(name)] = texture;
    }

    void Material::setUniformValue(const std::string& name,
        const UniformValue& value)
    {
        _uniformValues[_program->getUniform(name)] = value;
    }

    const glm::vec2& Material::getSize() const
    {
        if(_textures.empty())
        {
            static glm::vec2 size;
            return size;
        }
        else
        {
            return _textures.begin()->second->getSize();
        }
    }

    const std::shared_ptr<Program>& Material::getProgram() const
    {
        return _program;
    }

    void Material::activate()
    {
        _program->use();
        size_t i = 0;
        for(auto itr = _textures.begin();
            itr != _textures.end(); ++itr)
        {
            _program->setUniformValue(itr->first, (GLint)i);
            itr->second->activate(i);
            ++i;
        }
        for(auto itr = _uniformValues.begin();
            itr != _uniformValues.end(); ++itr)
        {
            itr->second.set(itr->first);
        }
    }


}
