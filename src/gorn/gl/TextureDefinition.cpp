
#include <gorn/gl/TextureDefinition.hpp>

namespace gorn
{
    TextureDefinition::TextureDefinition():
    _target(GL_TEXTURE_2D), _lod(0)
    {
        withParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        withParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        withParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        withParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    TextureDefinition& TextureDefinition::withImage(const std::string& image)
    {
        _imageName = image;
        return *this;
    }

	TextureDefinition& TextureDefinition::withImage(Image&& image)
	{
		return withImage(std::make_shared<Image>(std::move(image)));
	}

	TextureDefinition& TextureDefinition::withImage(const std::shared_ptr<Image>& image)
	{
		_image = image;
		return *this;
	}

    TextureDefinition& TextureDefinition::withTarget(GLenum target)
    {
        _target = target;
        return *this;
    }

    TextureDefinition& TextureDefinition::withLevelOfDetail(GLint lod)
    {
        _lod = lod;
        return *this;
    }

    TextureDefinition& TextureDefinition::withParameter(GLenum name, GLint value)
    {
        _intParams[name] = value;
        return *this;
    }

    TextureDefinition& TextureDefinition::withParameter(GLenum name, GLfloat value)
    {
        _floatParams[name] = value;
        return *this;
    }

    TextureDefinition& TextureDefinition::withParameter(GLenum name, const std::vector<GLint>& value)
    {
        _intVecParams[name] = value;
        return *this;
    }

    TextureDefinition& TextureDefinition::withParameter(GLenum name, const std::vector<GLfloat>& value)
    {
        _floatVecParams[name] = value;
        return *this;
    }

    const std::string& TextureDefinition::getImageName() const
    {
        return _imageName;
    }

	std::shared_ptr<Image> TextureDefinition::getImage() const
	{
		return _image;
	}

    GLenum TextureDefinition::getTarget() const
    {
        return _target;
    }

    GLint TextureDefinition::getLevelOfDetail() const
    {
        return _lod;
    }

    const std::unordered_map<GLenum, GLint>& TextureDefinition::getIntParameters() const
    {
        return _intParams;
    }

    const std::unordered_map<GLenum, GLfloat>& TextureDefinition::getFloatParameters() const
    {
        return _floatParams;
    }

    const std::unordered_map<GLenum, std::vector<GLint>>& TextureDefinition::getIntPointerParameters() const
    {
        return _intVecParams;
    }

    const std::unordered_map<GLenum, std::vector<GLfloat>>& TextureDefinition::getFloatPointerParameters() const
    {
        return _floatVecParams;
    }
}

