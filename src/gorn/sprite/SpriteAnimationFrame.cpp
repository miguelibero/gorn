
#include <gorn/sprite/SpriteAnimationFrame.hpp>
#include <gorn/sprite/SpriteAtlasRegion.hpp>
#include <gorn/render/RenderQueue.hpp>
#include <gorn/render/Material.hpp>
#include <gorn/render/Kinds.hpp>

namespace gorn {

    SpriteAnimationFrame::SpriteAnimationFrame():
    _dirty(true)
    {
    }

    SpriteAnimationFrame::SpriteAnimationFrame(
        const std::shared_ptr<Material>& material):
    _material(material), _dirty(true)
    {
        _region.setSize(material->getSize());
    }

    SpriteAnimationFrame::SpriteAnimationFrame(
        const std::shared_ptr<Material>& material, const Region& region):
    _material(material), _region(region), _dirty(true)
    {
    }

    void SpriteAnimationFrame::setMaterial(
        const std::shared_ptr<Material>& material)
    {
        _material = material;
    }

    const std::shared_ptr<Material>& SpriteAnimationFrame::getMaterial() const
    {
        return _material;
    }

    void SpriteAnimationFrame::setRegion(const Region& region)
    {
        _region = region;
    }

    const SpriteAnimationFrame::Region& SpriteAnimationFrame::getRegion() const
    {
        return _region;
    }

    void SpriteAnimationFrame::update()
    {
        if(_dirty)
        {
            updateElementData();
            updatePositionData();
            updateTextureData();
            _dirty = false;
        }
    }

    void SpriteAnimationFrame::updateElementData()
    {
        _elmVerts = {
            0, 1, 2,
            2, 3, 0
        };
    }

    void SpriteAnimationFrame::updatePositionData()
    {
        auto bl = _region.getOriginalSize()-_region.getSize();
        bl = bl*0.5f+_region.getOffset();
        bl /= _material->getSize();
        auto tr = bl + _region.getSize()/_region.getOriginalSize();

        _posVerts = {
            bl.x, tr.y,
            tr.x, tr.y,
            tr.x, bl.y,
            bl.x, bl.y
        };
    }

    void SpriteAnimationFrame::updateTextureData()
    {
        auto bl = _region.getPosition();
        auto origin = _region.getOrigin();
        auto rsize = _region.getSize();
        auto msize = _material->getSize();
        auto rotate = _region.getRotate();
        if(rotate)
        {
            std::swap(rsize.x, rsize.y);
        }
        if(origin == Region::Origin::TopLeft || origin == Region::Origin::TopRight)
        {
            bl.y = msize.y - rsize.y - bl.y;
        }
        if(origin == Region::Origin::BottomRight || origin == Region::Origin::TopRight)
        {
            bl.x = msize.x - rsize.x - bl.x;
        }
        auto tr = bl+rsize;
        tr /= msize;
        bl /= msize;

        if(rotate)
        {
            _texVerts = {
                bl.x, bl.y,
                bl.x, tr.y,
                tr.x, tr.y,
                tr.x, bl.y
            };
        }
        else
        {
            _texVerts = {
                bl.x, tr.y,
                tr.x, tr.y,
                tr.x, bl.y,
                bl.x, bl.y
            };
        }
    }

    void SpriteAnimationFrame::render(RenderQueue& queue) const
    {
        queue.addCommand()
            .withMaterial(_material)
            .withAttribute(AttributeKind::Position, 
                _posVerts, GL_FLOAT, 2)
            .withAttribute(AttributeKind::TexCoords, 
                _texVerts, GL_FLOAT, 2)
            .withElements(
                _elmVerts, GL_UNSIGNED_INT, 6);
    }
}
