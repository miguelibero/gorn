

#ifndef __gorn__Label__
#define __gorn__Label__

#include <gorn/sprite/SpriteFont.hpp>

namespace gorn {

    class RenderQueue;

    class Label
    {
    private:
        SpriteFont _font;
        std::string _text;
    public:
        Label(const SpriteFont& font);
        Label(const SpriteFont& font, const std::string& text);

        void setText(const std::string& text);
        
        void update(double dt);
        void render(RenderQueue& queue);
    };

}

#endif
