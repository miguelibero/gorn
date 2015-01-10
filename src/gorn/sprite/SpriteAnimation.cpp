
#include <gorn/sprite/SpriteAnimation.hpp>
#include <gorn/render/Material.hpp>

namespace gorn {

    SpriteAnimation::SpriteAnimation():
    _frameDuration(1.0f/30.0f)
    {
    }

    SpriteAnimation::SpriteAnimation(const std::shared_ptr<Material>& material):
    _material(material)
    {
    }

    SpriteAnimation::SpriteAnimation(const std::shared_ptr<Material>& material,
        const Frame& frame):
    _material(material), _frames{frame}
    {
    }
    
    SpriteAnimation& SpriteAnimation::withMaterial(const std::shared_ptr<Material>& material)
    {
        _material = material;
        if(_material != nullptr)
        {
            for(auto& frame : _frames)
            {
                frame.setTotalSize(_material->getSize());
            }
        }
        return *this;
    }

    SpriteAnimation& SpriteAnimation::withFrameDuration(double duration)
    {
        _frameDuration = duration;
        return *this;
    }

    SpriteAnimation& SpriteAnimation::addFrame(const Frame& frame)
    {
        _frames.push_back(frame);
        if(_material != nullptr)
        {
            _frames.back().setTotalSize(_material->getSize());            
        }
        return *this;
    }

    SpriteAnimation& SpriteAnimation::addFrames(const std::vector<Frame>& frames)
    {
        for(auto& frame : frames)
        {
            addFrame(frame);
        }
        return *this;
    }

    const std::shared_ptr<Material>& SpriteAnimation::getMaterial() const
    {
        return _material;
    }

    const SpriteAnimation::Frame& SpriteAnimation::getFrame(double time) const
    {
        size_t num = time / _frameDuration;
        return _frames.at(num % _frames.size());
    }

    double SpriteAnimation::getTotalDuration() const
    {
        return _frames.size()*_frameDuration;
    }

}


