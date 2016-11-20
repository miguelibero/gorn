#ifndef __gorn__TextureDefinition__
#define __gorn__TextureDefinition__

#include <gorn/gl/Base.hpp>
#include <gorn/asset/Image.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

namespace gorn
{
    class Image;

    class TextureDefinition
    {
    private:
        std::string _imageName;
		std::shared_ptr<Image> _image;
        GLenum _target;
        GLint _lod;
        std::unordered_map<GLenum, GLint> _intParams;
        std::unordered_map<GLenum, GLfloat> _floatParams;
        std::unordered_map<GLenum, std::vector<GLint>> _intVecParams;
        std::unordered_map<GLenum, std::vector<GLfloat>> _floatVecParams;
    public:
        TextureDefinition();
        TextureDefinition& withImage(const std::string& image);
		TextureDefinition& withImage(Image&& image);
		TextureDefinition& withImage(const std::shared_ptr<Image>& image);
        TextureDefinition& withTarget(GLenum target);
        TextureDefinition& withLevelOfDetail(GLint lod);
        TextureDefinition& withParameter(GLenum name, GLint value);
        TextureDefinition& withParameter(GLenum name, GLfloat value);
        TextureDefinition& withParameter(GLenum name, const std::vector<GLint>& value);
        TextureDefinition& withParameter(GLenum name, const std::vector<GLfloat>& value);

        const std::string& getImageName() const;
		std::shared_ptr<Image> getImage() const;
        GLenum getTarget() const;
        GLint getLevelOfDetail() const;
        const std::unordered_map<GLenum, GLint>& getIntParameters() const;
        const std::unordered_map<GLenum, GLfloat>& getFloatParameters() const;
        const std::unordered_map<GLenum, std::vector<GLint>>& getIntPointerParameters() const;
        const std::unordered_map<GLenum, std::vector<GLfloat>>& getFloatPointerParameters() const;

    };
}

#endif
