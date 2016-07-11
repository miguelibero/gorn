#include <gorn/gl/Capabilities.hpp>
#include <algorithm>

namespace gorn
{
	Capabilities::CapabilityChanges Capabilities::_defaultCapabilities = {
		{ CapabilityType::DepthTest, false },
		{ CapabilityType::StencilTest, false }
	};

	Capabilities::MaskChanges Capabilities::_defaultMasks = {
		{ MaskType::Depth, true },
		{ MaskType::Red, true },
		{ MaskType::Green, true },
		{ MaskType::Blue, true },
		{ MaskType::Alpha, true }
	};

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

    void Capabilities::apply() const
    {
		auto caps = _capabilities;
		caps.insert(_defaultCapabilities.begin(), _defaultCapabilities.end());

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
		auto masks = _masks;
		masks.insert(_defaultMasks.begin(), _defaultMasks.end());
        glDepthMask(masks[MaskType::Depth] ? GL_TRUE : GL_FALSE);
        glColorMask(
			masks[MaskType::Red] ? GL_TRUE : GL_FALSE,
			masks[MaskType::Green] ? GL_TRUE : GL_FALSE,
			masks[MaskType::Blue] ? GL_TRUE : GL_FALSE,
			masks[MaskType::Alpha] ? GL_TRUE : GL_FALSE);
		glLineWidth(_lineWidth);
    }
}
