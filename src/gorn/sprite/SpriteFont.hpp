

#ifndef __gorn__SpriteFont__
#define __gorn__SpriteFont__

#include <gorn/sprite/SpriteFrame.hpp>
#include <map>

namespace gorn {

    class SpriteFont
    {
    public:
        typedef SpriteFrame Letter;
    private:
        std::map<std::string, std::shared_ptr<Letter>> _letters;
    public:
        SpriteFont();

        void setLetter(const std::string& name, const std::shared_ptr<Letter>& letter);
        bool hasLetter(const std::string& name) const;
        const Letter& getLetter(const std::string& name) const;
    };

}

#endif
