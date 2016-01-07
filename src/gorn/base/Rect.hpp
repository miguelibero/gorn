#ifndef __gorn__Rect__
#define __gorn__Rect__

#include <vector>
#include <glm/glm.hpp>

class buffer;

namespace gorn
{
    enum class RectMatchType
    {
        Contain,
        Intersect,
        Overlap
    };

    class RectMatch;
    class CubeShape;

    class Rect
    {
    public:
        typedef RectMatchType MatchType;
        glm::vec3 origin;
        glm::vec3 size;

        Rect(const glm::vec3& origin=glm::vec3(0.0f),
            const glm::vec3& size=glm::vec3(0.0f));
        Rect(const glm::vec2& origin, const glm::vec2& size=glm::vec2(0.0f));

        Rect operator*(const glm::mat4& transform) const;
        Rect& operator*=(const glm::mat4& transform);

        std::vector<Rect> divide(const glm::vec3& divisions) const;

        CubeShape shape() const;
        bool contains(const glm::vec3& point) const;
        bool contains(const glm::vec2& point) const;
        bool contains(const Rect& other) const;
        bool intersects(const Rect& other) const;
        bool overlaps(const Rect& other) const;
        bool matches(const Rect& other, MatchType type) const;
        bool matches(const RectMatch& match) const;
        float area() const;

        bool flat() const;
        glm::vec3 min() const;
        glm::vec3 max() const;
        glm::vec3 exterior(const glm::vec3& normal) const;
    };

    class RectMatch
    {
    public:
        typedef RectMatchType Type;
        Rect rect;
        Type type;

        RectMatch(const Rect& r, Type t=Type::Overlap);
        bool matches(const Rect& other) const;
    };
}

#endif
