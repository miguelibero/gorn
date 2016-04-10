#include <gorn/gl/StateChange.hpp>
#include <algorithm>

namespace gorn
{
    StateChange::StateChange()
    {
    }

    StateChange& StateChange::withEnable(TestType type)
    {
        _tests[type] = true;
        return *this;
    }

    StateChange& StateChange::withDisable(TestType type)
    {
        _tests[type] = false;
        return *this;
    }

    StateChange& StateChange::withEnable(MaskType type)
    {
        _masks[type] = true;
        return *this;
    }

    StateChange& StateChange::withDisable(MaskType type)
    {
        _masks[type] = false;
        return *this;
    }

    bool StateChange::operator==(const StateChange& other) const
    {
        return true
            && std::is_permutation(_tests.begin(),
                _tests.end(), other._tests.begin())
            && std::is_permutation(_masks.begin(),
                _masks.end(), other._masks.begin());
    }

    bool StateChange::operator!=(const StateChange& other) const
    {
        return !(*this == other);
    }

	void StateChange::apply(const StateChange& old)
	{
		// TODO: just apply differences
		apply();
	}

    void StateChange::apply()
    {
        for(auto itr = _tests.begin(); itr != _tests.end(); ++itr)
        {            
            auto glf = getGlTest(itr->first);
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
        {
            auto itr = _masks.find(MaskType::Stencil);
            if(itr != _masks.end())
            {
                glStencilMask(itr->second?0xFF:0x00);
            }
        }
        {
            auto itr = _masks.find(MaskType::Depth);
            if(itr != _masks.end())
            {
                glDepthMask(itr->second?GL_TRUE:GL_FALSE);
            }
        }
        {
            GLboolean colors[4];
            glGetBooleanv(GL_COLOR_WRITEMASK, colors);
            MaskType masks[] = { MaskType::Red, MaskType::Green,
                MaskType::Blue, MaskType::Alpha };
            for(int i=0; i<4; i++)
            {
                auto itr = _masks.find(masks[i]);
                if(itr != _masks.end())
                {
                    colors[i] = itr->second?GL_TRUE:GL_FALSE;
                }
            }
            glColorMask(colors[0], colors[1], colors[2], colors[3]);
        }
    }
}
