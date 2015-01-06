#ifndef __gorn__TextureDefinition__
#define __gorn__TextureDefinition__

#include <gorn/render/Gl.hpp>
#include <map>
#include <vector>
#include <string>

namespace gorn
{
	class Image;

	class TextureDefinition
	{
	private:
        std::string _imageName;
        GLenum _target;
        GLint _lod;
        std::map<GLenum, GLint> _intParams;
        std::map<GLenum, GLfloat> _floatParams;
        std::map<GLenum, std::vector<GLint>> _intVecParams;
        std::map<GLenum, std::vector<GLfloat>> _floatVecParams;
	public:
		TextureDefinition();
        TextureDefinition& withImage(const std::string& image);
        TextureDefinition& withTarget(GLenum target);
        TextureDefinition& withLevelOfDetail(GLint lod);
        TextureDefinition& withParameter(GLenum name, GLint value);
        TextureDefinition& withParameter(GLenum name, GLfloat value);
        TextureDefinition& withParameter(GLenum name, const std::vector<GLint>& value);
        TextureDefinition& withParameter(GLenum name, const std::vector<GLfloat>& value);

        const std::string& getImageName() const;
        GLenum getTarget() const;
        GLint getLevelOfDetail() const;
        const std::map<GLenum, GLint>& getIntParameters() const;
        const std::map<GLenum, GLfloat>& getFloatParameters() const;
        const std::map<GLenum, std::vector<GLint>>& getIntPointerParameters() const;
        const std::map<GLenum, std::vector<GLfloat>>& getFloatPointerParameters() const;

	};
}

#endif
