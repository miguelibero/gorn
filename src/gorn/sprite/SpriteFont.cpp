

#include <gorn/sprite/SpriteFont.hpp>

namespace gorn {

    SpriteFont::SpriteFont()
    {
    }

    void SpriteFont::setLetter(
        const std::string& name, const std::shared_ptr<Letter>& letter)
    {
        _letters[name] = letter;
    }

    bool SpriteFont::hasLetter(const std::string& name) const
    {
        return _letters.find(name) != _letters.end();
    }

    const SpriteFont::Letter& SpriteFont::getLetter(
        const std::string& name) const
    {
        return *_letters.at(name);
    }
}

