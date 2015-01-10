
#include <gorn/sprite/SpriteAtlasRegion.hpp>

namespace gorn {

    SpriteAtlasRegion::SpriteAtlasRegion() :
    _origin(Origin::BottomLeft), _flipX(false),
    _flipY(false), _rotate(false),
    _texVerts(8*sizeof(float)),
    _posVerts(8*sizeof(float)),
    _texVertsDirty(true),
    _posVertsDirty(true)
    {
    }

    SpriteAtlasRegion::Origin SpriteAtlasRegion::getOrigin() const
    {
        return _origin;
    }

    void SpriteAtlasRegion::setOrigin(Origin value)
    {
        if(_origin != value)
        {
            _origin = value;
            _texVertsDirty = true;
        }
    }

    const glm::vec2& SpriteAtlasRegion::getPosition() const
    {
        return _position;
    }

    glm::vec2& SpriteAtlasRegion::getPosition()
    {
        return _position;
    }

    void SpriteAtlasRegion::setPosition(const glm::vec2& value)
    {
        _position = value;
    }

    void SpriteAtlasRegion::setPosition(value_type x, value_type y)
    {
        setPosition(glm::vec2(x, y));
    }

    const glm::vec2& SpriteAtlasRegion::getSize() const
    {
        return _size;
    }

    glm::vec2& SpriteAtlasRegion::getSize()
    {
        return _size;
    }

    void SpriteAtlasRegion::setSize(const glm::vec2& value)
    {
        if(_size != value)
        {
            _size = value;
            _texVertsDirty = true;
        }
    }

    void SpriteAtlasRegion::setSize(value_type x, value_type y)
    {
        setSize(glm::vec2(x, y));
    }

    const glm::vec2& SpriteAtlasRegion::getOriginalSize() const
    {
        return _originalSize;
    }

    glm::vec2& SpriteAtlasRegion::getOriginalSize()
    {
        return _originalSize;
    }

    void SpriteAtlasRegion::setOriginalSize(const glm::vec2& value)
    {
        if(_originalSize != value)
        {
            _originalSize = value;
            _posVertsDirty = true;
        }
    }

    void SpriteAtlasRegion::setOriginalSize(value_type x, value_type y)
    {
        setOriginalSize(glm::vec2(x, y));
    }

    const glm::vec2& SpriteAtlasRegion::getOffset() const
    {
        return _offset;
    }

    glm::vec2& SpriteAtlasRegion::getOffset()
    {
        return _offset;
    }

    void SpriteAtlasRegion::setOffset(const glm::vec2& value)
    {
        if(_offset != value)
        {
            _offset = value;
            _posVertsDirty = true;
        }
    }

    void SpriteAtlasRegion::setOffset(value_type x, value_type y)
    {
        setOffset(glm::vec2(x, y));
    }

    const glm::vec2& SpriteAtlasRegion::getTotalSize() const
    {
        return _totalSize;
    }

    glm::vec2& SpriteAtlasRegion::getTotalSize()
    {
        return _totalSize;
    }

    void SpriteAtlasRegion::setTotalSize(const glm::vec2& value)
    {
        if(_totalSize != value)
        {
            _totalSize = value;
            _texVertsDirty = true;
        }
    }

    void SpriteAtlasRegion::setTotalSize(value_type x, value_type y)
    {
        setTotalSize(glm::vec2(x, y));
    }

    bool SpriteAtlasRegion::getFlipX() const
    {
        return _flipX;
    }

    void SpriteAtlasRegion::setFlipX(bool enabled)
    {
        _flipX = enabled;
    }

    bool SpriteAtlasRegion::getFlipY() const
    {
        return _flipY;
    }

    void SpriteAtlasRegion::setFlipY(bool enabled)
    {
        _flipY = enabled;
    }

    bool SpriteAtlasRegion::getRotate() const
    {
        return _rotate;
    }

    void SpriteAtlasRegion::setRotate(bool enabled)
    {
        _rotate = enabled;
    }

    const Data& SpriteAtlasRegion::getPositionVertices() const
    {
        auto bl = (_originalSize-_size)*0.5f+_offset;
        bl /= _totalSize;
        auto tr = bl + _size/_originalSize;
        if(_posVertsDirty)
        {
            _posVerts = {
                bl.x, tr.y,
                tr.x, tr.y,
                tr.x, bl.y,
                bl.x, bl.y
            };
            _posVertsDirty = false;
        }
        return _posVerts;
    }

    const Data& SpriteAtlasRegion::getTextureVertices() const
    {
        if(_texVertsDirty)
        {
            glm::vec2 bl = _position;
            if(_origin == Origin::TopLeft || _origin == Origin::TopRight)
            {
                bl.y = _totalSize.y - bl.y;
            }
            if(_origin == Origin::BottomRight || _origin == Origin::TopRight)
            {
                bl.x = _totalSize.x - bl.x;
            }
            auto rsize = _size;
            if(_rotate)
            {
                std::swap(rsize.x, rsize.y);
            }
            auto tr = bl+rsize;
            tr /= _totalSize;
            bl /= _totalSize;

            if(_rotate)
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
            _texVertsDirty = false;
        }
        return _texVerts;
    }
}
