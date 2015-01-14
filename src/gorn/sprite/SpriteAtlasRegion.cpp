
#include <gorn/sprite/SpriteAtlasRegion.hpp>

namespace gorn {

    SpriteAtlasRegion::SpriteAtlasRegion() :
    _page(0), _origin(Origin::BottomLeft),
    _flipX(false), _flipY(false), _rotate(false)
    {
    }

    bool SpriteAtlasRegion::operator==(const SpriteAtlasRegion& other) const
    {
        return _page == other._page
            && _origin == other._origin
            && _position == other._position
            && _size == other._size
            && _originalSize == other._originalSize
            && _offset == other._offset
            && _flipX == other._flipX
            && _flipY == other._flipY
            && _rotate == other._rotate;
    }

    bool SpriteAtlasRegion::operator!=(const SpriteAtlasRegion& other) const
    {
        return !operator==(other);
    }


    size_t SpriteAtlasRegion::getPage() const
    {
        return _page;
    }

    void SpriteAtlasRegion::setPage(size_t value)
    {
        _page = value;
    }

    SpriteAtlasRegion::Origin SpriteAtlasRegion::getOrigin() const
    {
        return _origin;
    }

    void SpriteAtlasRegion::setOrigin(Origin value)
    {
        _origin = value;
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
        _size = value;
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
        _originalSize = value;
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
        _offset = value;
    }

    void SpriteAtlasRegion::setOffset(value_type x, value_type y)
    {
        setOffset(glm::vec2(x, y));
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

}
