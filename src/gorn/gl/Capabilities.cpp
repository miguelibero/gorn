#include <gorn/gl/Capabilities.hpp>
#include <algorithm>
#include <array>

namespace gorn
{
    Capabilities::Capabilities():
	_lineWidth(1.0f)
    {
    }

	Capabilities& Capabilities::with(CapabilityType type, bool enabled)
    {
        _capabilities[type] = enabled;
        return *this;
    }


	Capabilities& Capabilities::with(MaskType type, bool enabled)
    {
        _masks[type] = enabled;
        return *this;
    }
   
	Capabilities& Capabilities::withLineWidth(float w)
	{
		_lineWidth = w;
		return *this;
	}

    bool Capabilities::operator==(const Capabilities& other) const
    {
        return true
			&& _capabilities.size() == other._capabilities.size()
			&& _masks.size() == other._masks.size()
            && std::equal(_capabilities.begin(),
				_capabilities.end(), other._capabilities.begin())
            && std::equal(_masks.begin(),
                _masks.end(), other._masks.begin())
			&& _lineWidth == other._lineWidth;
    }

    bool Capabilities::operator!=(const Capabilities& other) const
    {
        return !(*this == other);
    }

    const Capabilities::MaskChanges defaultColorMasks = {
        { MaskType::Red, true },
        { MaskType::Green, true },
        { MaskType::Blue, true },
        { MaskType::Alpha, true }
    };

    void Capabilities::apply() const
    {
		auto& caps = _capabilities;

        for(auto itr = caps.begin(); itr != caps.end(); ++itr)
        {
            auto glf = getGlCapability(itr->first);
            if(glf != 0)
            {
                if(itr->second)
                {
                    glEnable(glf);
                }
                else
                {
                    glDisable(glf);
                }
            }
        }

		auto itr = _masks.find(MaskType::Depth);
		if(itr != _masks.end())
		{
			glDepthMask(itr->second ? GL_TRUE : GL_FALSE);
		}
        auto colors = defaultColorMasks;
        colors.insert(_masks.begin(), _masks.end());
        glColorMask(
			colors[MaskType::Red] ? GL_TRUE : GL_FALSE,
			colors[MaskType::Green] ? GL_TRUE : GL_FALSE,
			colors[MaskType::Blue] ? GL_TRUE : GL_FALSE,
			colors[MaskType::Alpha] ? GL_TRUE : GL_FALSE);
		if(_lineWidth >= 0.0f)
		{
			glLineWidth(_lineWidth);
		}
    }
}
