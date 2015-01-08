
#include <gorn/view/Sprite.hpp>
#include <gorn/render/RenderQueue.hpp>
#include <gorn/render/Kinds.hpp>

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

    void Sprite::render(RenderQueue& queue)
    {
        queue.addCommand()
            .withMaterial(_material)
            .withAttribute(AttributeKind::Position, {
                 0.0f, 1.0f,
                 1.0f, 1.0f,
                 1.0f, 0.0f,
                 0.0f, 0.0f,
            }, GL_FLOAT, 2)
            .withAttribute(AttributeKind::TexCoords, {
                0.0f, 1.0f,
                1.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f
            }, GL_FLOAT, 2)
            .withElements({
                0, 1, 2,
                2, 3, 0
            }, GL_UNSIGNED_INT, 6);
    }

}

