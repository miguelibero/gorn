

#ifndef __gorn__LabelFont__
#define __gorn__LabelFont__

#include <gorn/label/LabelCharacter.hpp>
#include <map>

namespace gorn {

    class LabelFont
    {
    public:
        typedef LabelCharacter Character;
    private:
        std::map<std::string, Character> _chars;
    public:
        LabelFont();

        void setCharacter(const std::string& name, const Character& chr);
        bool hasCharacter(const std::string& name) const;
        const Character& getCharacter(const std::string& name) const;
        Character& getCharacter(const std::string& name);
    };

}

#endif
