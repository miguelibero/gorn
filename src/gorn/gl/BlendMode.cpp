#include <gorn/gl/BlendMode.hpp>

namespace gorn
{
	BlendMode::BlendMode() :
	_src(BlendFactor::SrcAlpha), _dst(BlendFactor::OneMinusSrcAlpha)
	{
	}

	BlendMode::BlendMode(const BlendMode& other):
	_src(other._src), _dst(other._dst)
	{
	}

	BlendMode::BlendMode(BlendFactor src, BlendFactor dst):
	_src(src), _dst(dst)
	{
	}

	bool BlendMode::operator==(const BlendMode& other) const
	{
		return _src == other._src && _dst == other._dst;
	}

	bool BlendMode::operator!=(const BlendMode& other) const
	{
		return !(*this == other);
	}

	bool BlendMode::enabled() const
	{
		return _src != BlendFactor::None && _dst != BlendFactor::None;
	}

	void BlendMode::apply(const BlendMode& old)
	{
		if(enabled() != old.enabled())
		{
			apply();
		}
		else if(*this != old)
		{
			glBlendFunc(getGlBlendFactor(_src), getGlBlendFactor(_dst));
		}
	}

	void BlendMode::apply()
	{
		if(!enabled())
		{
			glDisable(GL_BLEND);
		}
		else
		{
			glEnable(GL_BLEND);
			glBlendFunc(getGlBlendFactor(_src), getGlBlendFactor(_dst));
		}
	}
}

