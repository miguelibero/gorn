
#include <gorn/sprite/Label.hpp>

namespace gorn {

    Label::Label(const SpriteFont& font):
    _font(font)
    {
    }

    Label::Label(const SpriteFont& font, const std::string& text):
    _font(font), _text(text)
    {
    }

    void Label::setText(const std::string& text)
    {
        _text = text;
    }
    
    void Label::update(double dt)
    {
    }
    
    void Label::render(RenderQueue& queue)
    {
    }

}
