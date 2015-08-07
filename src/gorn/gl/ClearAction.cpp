#include <gorn/gl/ClearAction.hpp>
#include <algorithm>

namespace gorn
{
    ClearAction::ClearAction()
    {
    }

    ClearAction& ClearAction::withColor(const glm::vec4& color)
    {
        _color = color;
        return *this;
    }

    ClearAction& ClearAction::withType(Type type)
    {
        auto itr = std::find(_types.begin(),
            _types.end(), type);
        if(itr == _types.end())
        {
            _types.insert(itr, type);
        }
        return *this;
    }

    bool ClearAction::empty() const
    {
        return _color[3] <= 0.0f && _types.empty();
    }

    void ClearAction::apply()
    {
        if(_color[3] > 0.0f)
        {
            glClearColor(_color[0],_color[1],
                _color[2],_color[3]);
        }
        GLbitfield clearBitfield = 0;
        for(auto& t : _types)
        {
            clearBitfield |= getGlClearBufferBit(t);
        }
        glClear(clearBitfield);
    }

}
