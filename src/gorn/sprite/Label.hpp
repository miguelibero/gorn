

#ifndef __gorn__Label__
#define __gorn__Label__

#include <gorn/sprite/SpriteFont.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace gorn {

    class RenderQueue;

    class Label
    {
    private:

        SpriteFont _font;
        std::string _text;
        glm::vec2 _size;
        bool _dirtyLetters;
        std::vector<std::string> _textLetters;

        void init();

    public:
        Label();
        Label(const SpriteFont& font);
        Label(const SpriteFont& font, const std::string& text);

        const SpriteFont& getFont() const;
        void setFont(const SpriteFont& font);

        const std::string& getText() const;
        void setText(const std::string& text);

        const glm::vec2& getSize();
        void setSize(const glm::vec2& size);
        
        void update(double dt);
        void render(RenderQueue& queue);
    };

}

#endif
