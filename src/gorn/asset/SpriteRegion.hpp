

#ifndef __gorn__SpriteRegion__
#define __gorn__SpriteRegion__

#include <glm/glm.hpp>
#include <string>
#include <memory>

namespace gorn {

    class SpriteRegion
    {
    public:
        typedef glm::vec2::value_type value_type;
    private:
        glm::vec2 _origin;
        glm::vec2 _size;
        glm::vec2 _originalSize;
        glm::vec2 _offset;
        bool _flipX;
        bool _flipY;
        bool _rotate;
    public:
        SpriteRegion();

        const glm::vec2& getOrigin() const;
        glm::vec2& getOrigin();
        void setOrigin(const glm::vec2& value);
        void setOrigin(value_type x, value_type y);

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

        bool getFlipX() const;
        void setFlipX(bool enabled);
        bool getFlipY() const;
        void setFlipY(bool enabled);
        bool getRotate() const;
        void setRotate(bool enabled);

    };

}

#endif
