

#include <gorn/label/LabelFont.hpp>

namespace gorn {

    LabelFont::LabelFont()
    {
    }

    void LabelFont::setCharacter(
        const std::string& name, const Character& chr)
    {
        _chars[name] = chr;
    }

    bool LabelFont::hasCharacter(const std::string& name) const
    {
        return _chars.find(name) != _chars.end();
    }

    const LabelFont::Character& LabelFont::getCharacter(
        const std::string& name) const
    {
        return _chars.at(name);
    }

    LabelFont::Character& LabelFont::getCharacter(
        const std::string& name)
    {
        return _chars.at(name);
    }
}

