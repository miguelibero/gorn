
#include <gorn/view/Sprite.hpp>
#include <gorn/render/RenderCommand.hpp>

namespace gorn {


    Sprite::Sprite(const std::shared_ptr<Material>& material):
    _material(material)
    {
        init();
    }

    Sprite::Sprite(const std::shared_ptr<Material>& material, const Region& region):
    _material(material), _region(region)
    {
        init();
    }

    void Sprite::init()
    {
        _dirty = true;
    }

    void Sprite::setMaterial(const std::shared_ptr<Material>& material)
    {
        _material = material;
    }

    const std::shared_ptr<Material>& Sprite::getMaterial() const
    {
        return _material;
    }

    const Sprite::Region& Sprite::getRegion() const
    {
        return _region;
    }

    void Sprite::setRegion(const Region& region)
    {
        _region = region;
    }

    void Sprite::render(RenderCommand& cmd)
    {
    }

}

