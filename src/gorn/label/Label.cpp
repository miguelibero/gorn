
#include <gorn/label/Label.hpp>
#include <gorn/render/RenderQueue.hpp>
#include <glm/gtx/transform.hpp>

namespace gorn {

    Label::Label()
    {
        init();
    }

    Label::Label(const std::shared_ptr<Font>& font):
    _font(font) 
    {
        init();
    }

    Label::Label(const std::shared_ptr<Font>& font, const std::string& text):
    _font(font), _text(text)
    {
        init();
    }

    void Label::init()
    {
        _dirty = true;
    }

    const std::shared_ptr<Label::Font>& Label::getFont() const
    {
        return _font;
    }

    void Label::setFont(const std::shared_ptr<Font>& font)
    {
        _font = font;
    }

    void Label::setText(const std::string& text)
    {
        if(_text != text)
        {
            _text = text;
            _dirty = true;
        }
    }

    const std::string& Label::getText() const
    {
        return _text;
    }

    void Label::setSize(const glm::vec2& size)
    {
        _size = size;
    }

    const glm::vec2& Label::getSize()
    {
        return _size;
    }
    
    void Label::update(double dt)
    {
        if(_dirty)
        {
            _characters.clear();
            
            std::string name;
            for(auto itr=_text.begin(); itr!=_text.end(); ++itr)
            {
                name += *itr;
                if(_font->hasCharacter(name))
                {
                    _characters.push_back(name);
                    name.clear();
                }
            }

            _dirty = false;
        }
        for(auto& name : _characters)
        {
            _font->getCharacter(name).update();
        }
    }
    
    void Label::render(RenderQueue& queue)
    {
        for(auto& name : _characters)
        {
            auto& chr = _font->getCharacter(name);
            chr.render(queue);
        }
    }

}
