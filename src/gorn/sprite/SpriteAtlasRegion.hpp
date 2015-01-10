

#ifndef __gorn__SpriteAtlasRegion__
#define __gorn__SpriteAtlasRegion__

#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <gorn/base/Data.hpp>

namespace gorn {

    enum class SpriteAtlasRegionOrigin
    {
        BottomLeft,
        TopLeft,
        BottomRight,
        TopRight
    };

    class SpriteAtlasRegion
    {
    public:
        typedef glm::vec2::value_type value_type;
        typedef SpriteAtlasRegionOrigin Origin;
    private:
        Origin _origin;
        glm::vec2 _position;
        glm::vec2 _size;
        glm::vec2 _originalSize;
        glm::vec2 _totalSize;
        glm::vec2 _offset;
        bool _flipX;
        bool _flipY;
        bool _rotate;
        mutable Data _texVerts;
        mutable Data _posVerts;
        mutable bool _texVertsDirty;
        mutable bool _posVertsDirty;
    public:
        SpriteAtlasRegion();

        Origin getOrigin() const;
        void setOrigin(Origin value);

        const glm::vec2& getPosition() const;
        glm::vec2& getPosition();
        void setPosition(const glm::vec2& value);
        void setPosition(value_type x, value_type y);

        const glm::vec2& getSize() const;
        glm::vec2& getSize();
        void setSize(const glm::vec2& value);
        void setSize(value_type x, value_type y);

        const glm::vec2& getOriginalSize() const;
        glm::vec2& getOriginalSize();
        void setOriginalSize(const glm::vec2& value);
        void setOriginalSize(value_type x, value_type y);

        const glm::vec2& getOffset() const;
        glm::vec2& getOffset();
        void setOffset(const glm::vec2& value);
        void setOffset(value_type x, value_type y);

        const glm::vec2& getTotalSize() const;
        glm::vec2& getTotalSize();
        void setTotalSize(const glm::vec2& value);
        void setTotalSize(value_type x, value_type y);

        const Data& getPositionVertices() const;
        const Data& getTextureVertices() const;

        bool getFlipX() const;
        void setFlipX(bool enabled);
        bool getFlipY() const;
        void setFlipY(bool enabled);
        bool getRotate() const;
        void setRotate(bool enabled);

    };

}

#endif
