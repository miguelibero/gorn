
#include <gorn/asset/SpriteRegion.hpp>

namespace gorn {

    SpriteRegion::SpriteRegion() :
    _flipX(false), _flipY(false), _rotate(false)
    {
    }

    const glm::vec2& SpriteRegion::getOrigin() const
    {
        return _origin;
    }

    glm::vec2& SpriteRegion::getOrigin()
    {
        return _origin;
    }

    void SpriteRegion::setOrigin(const glm::vec2& value)
    {
        _origin = value;
    }

    void SpriteRegion::setOrigin(value_type x, value_type y)
    {
        _origin.x = x;
        _origin.y = y;
    }

    const glm::vec2& SpriteRegion::getSize() const
    {
        return _size;
    }

    glm::vec2& SpriteRegion::getSize()
    {
        return _size;
    }

    void SpriteRegion::setSize(const glm::vec2& value)
    {
        _size = value;
    }

    void SpriteRegion::setSize(value_type x, value_type y)
    {
        _size.x = x;
        _size.y = y;
    }

    const glm::vec2& SpriteRegion::getOriginalSize() const
    {
        return _originalSize;
    }

    glm::vec2& SpriteRegion::getOriginalSize()
    {
        return _originalSize;
    }

    void SpriteRegion::setOriginalSize(const glm::vec2& value)
    {
        _originalSize = value;
    }

    void SpriteRegion::setOriginalSize(value_type x, value_type y)
    {
        _originalSize.x = x;
        _originalSize.y = y;
    }

    const glm::vec2& SpriteRegion::getOffset() const
    {
        return _offset;
    }

    glm::vec2& SpriteRegion::getOffset()
    {
        return _offset;
    }

    void SpriteRegion::setOffset(const glm::vec2& value)
    {
        _offset = value;
    }

    void SpriteRegion::setOffset(value_type x, value_type y)
    {
        _offset.x = x;
        _offset.y = y;
    }

    bool SpriteRegion::getFlipX() const
    {
        return _flipX;
    }

    void SpriteRegion::setFlipX(bool enabled)
    {
        _flipX = enabled;
    }

    bool SpriteRegion::getFlipY() const
    {
        return _flipY;
    }

    void SpriteRegion::setFlipY(bool enabled)
    {
        _flipY = enabled;
    }

    bool SpriteRegion::getRotate() const
    {
        return _rotate;
    }

    void SpriteRegion::setRotate(bool enabled)
    {
        _rotate = enabled;
    }
}
