
#include <gorn/sprite/Label.hpp>
#include <gorn/render/RenderQueue.hpp>
#include <glm/gtx/transform.hpp>

namespace gorn {

    Label::Label()
    {
        init();
    }

    Label::Label(const SpriteFont& font):
    _font(font) 
    {
        init();
    }

    Label::Label(const SpriteFont& font, const std::string& text):
    _font(font), _text(text)
    {
        init();
    }

    void Label::init()
    {
        _dirtyLetters = true;
    }

    const SpriteFont& Label::getFont() const
    {
        return _font;
    }

    void Label::setFont(const SpriteFont& font)
    {
        _font = font;
    }

    void Label::setText(const std::string& text)
    {
        _text = text;
        _dirtyLetters = true;
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
        if(_dirtyLetters)
        {
            _textLetters.clear();
            
            std::string name;
            for(auto itr=_text.begin(); itr!=_text.end(); ++itr)
            {
                name += *itr;
                if(_font.hasLetter(name))
                {
                    _textLetters.push_back(name);
                    name.clear();
                }
            }

            _dirtyLetters = false;
        }
        for(auto& name : _textLetters)
        {
            _font.getLetter(name).update();
        }
    }
    
    void Label::render(RenderQueue& queue)
    {
        glm::vec3 pos;
        for(auto& name : _textLetters)
        {
            queue.addCommand()
              .withTransformMode(RenderCommand::TransformMode::PushLocal)
              .withTransform(glm::translate(glm::mat4(), pos));

            auto& letter = _font.getLetter(name);
            letter.render(queue);
            
            pos.x += letter.getUnitarySize().x;

            if(_size.x > 0 && pos.x > _size.x)
            {
            }

            queue.addCommand()
              .withTransformMode(RenderCommand::TransformMode::PopLocal);

        }
    }

}
