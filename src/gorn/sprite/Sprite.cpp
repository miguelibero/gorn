
#include <gorn/sprite/Sprite.hpp>
#include <gorn/render/RenderQueue.hpp>
#include <gorn/render/Kinds.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn {

    const char* Sprite::kDefaultAnimation = "default";

    Sprite::Sprite()
    {
    }

    Sprite::Sprite(const Animation& anim):
    _anims({{kDefaultAnimation, anim}})
    {
    }

    Sprite::Sprite(const std::shared_ptr<Material>& material):
    _anims({{kDefaultAnimation, Animation(material)}})
    {
    }

    Sprite::Sprite(const std::shared_ptr<Material>& material, SpriteAtlasRegion region):
    _anims({{kDefaultAnimation, Animation(material, region)}})
    {
    }

    void Sprite::setAnimation(const std::string& name, const Animation& anim)
    {
        _anims[name] = anim;
    }

    Sprite::Animation& Sprite::setAnimation(const std::string& name)
    {
        _anims[name] = Animation();
        return _anims[name];
    }

    void Sprite::play(const std::string& name)
    {
        if(_anims.find(name) == _anims.end())
        {
            throw Exception(std::string("Could not find animation '")+name+"'.");
        }
        if(_currentAnim != name)
        {
            _currentAnim = name;
            _animTime = 0.0;
        }
    }

    void Sprite::update(double dt)
    {
        auto itr = _anims.find(_currentAnim);
        if(itr != _anims.end())
        {
            auto& anim = itr->second;
            _animTime += dt;
            auto duration = anim.getTotalDuration();
            while(_animTime > duration)
            {
                _animTime -= duration;
            }
        }
    }

    void Sprite::render(RenderQueue& queue)
    {
        auto itr = _anims.find(_currentAnim);
        if(itr == _anims.end())
        {
            return;
        }
    
        auto& anim = itr->second;
        auto& frame = anim.getFrame(_animTime);

        queue.addCommand()
            .withMaterial(anim.getMaterial())
            .withAttribute(AttributeKind::Position, 
                frame.getPositionVertices(), GL_FLOAT, 2)
            .withAttribute(AttributeKind::TexCoords, 
                frame.getTextureVertices(), GL_FLOAT, 2)
            .withElements({
                0, 1, 2,
                2, 3, 0
            }, GL_UNSIGNED_INT, 6);
    }

}

