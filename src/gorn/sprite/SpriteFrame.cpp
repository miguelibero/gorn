
#include <gorn/sprite/SpriteFrame.hpp>
#include <gorn/sprite/SpriteAtlasRegion.hpp>
#include <gorn/render/RenderQueue.hpp>
#include <gorn/render/Material.hpp>
#include <gorn/render/Kinds.hpp>

namespace gorn {

    SpriteFrame::SpriteFrame()
    {
        init();
    }

    SpriteFrame::SpriteFrame(
        const std::shared_ptr<Material>& material):
    _material(material)
    {
        _region.setSize(material->getSize());
        init();
    }

    SpriteFrame::SpriteFrame(
        const std::shared_ptr<Material>& material, const Region& region):
    _material(material), _region(region)
    {
        init();
    }

    void SpriteFrame::init()
    {
        _dirtyTexVerts = true;
        _dirtyPosVerts = true;
        _dirtyElmVerts = true;
    }

    void SpriteFrame::setMaterial(
        const std::shared_ptr<Material>& material)
    {
        if(_material != material)
        {
            _material = material;
            _dirtyTexVerts = true;
        }
    }

    const std::shared_ptr<Material>& SpriteFrame::getMaterial() const
    {
        return _material;
    }

    void SpriteFrame::setRegion(const Region& region)
    {
        if(_region != region)
        {
            _region = region;
            _dirtyTexVerts = true;
            _dirtyPosVerts = true;
        }
    }

    const SpriteFrame::Region& SpriteFrame::getRegion() const
    {
        return _region;
    }

    void SpriteFrame::update()
    {
        updateElementData();
        updatePositionData();
        updateTextureData();
    }

    void SpriteFrame::updateElementData()
    {
        if(_dirtyElmVerts)
        {
            _elmVerts = {
                0, 1, 2,
                2, 3, 0
            };
            _dirtyElmVerts = false;
        }
    }

    void SpriteFrame::updatePositionData()
    {
        if(!_dirtyPosVerts)
        {
            return;
        }
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
        _dirtyPosVerts = false;
    }

    void SpriteFrame::updateTextureData()
    {
        if(!_dirtyTexVerts)
        {
            return;
        }

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
        _dirtyTexVerts = false;
    }

    void SpriteFrame::render(RenderQueue& queue) const
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
