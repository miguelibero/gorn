#ifndef __gorn__Rect__
#define __gorn__Rect__

#include <array>
#include <glm/glm.hpp>
#include <gorn/render/VertexArray.hpp>

class buffer;

namespace gorn
{
    enum class RectMatchType
    {
        Contain,
        Intersect,
        Overlap
    };

    struct RectMatch;
    struct RectVertices;

    struct Rect
    {
        typedef std::array<glm::vec3,8> Corners;
        typedef RectMatchType MatchType;
        typedef gorn::DrawMode DrawMode;
        glm::vec3 origin;
        glm::vec3 size;
        
        Rect(const glm::vec3& origin=glm::vec3(0.0f),
            const glm::vec3& size=glm::vec3(0.0f));
        Rect(const glm::vec2& origin, const glm::vec2& size=glm::vec2(0.0f));

        // Axis Aligned Bounding Box
        Rect operator*(const glm::mat4& transform) const;
        Rect& operator*=(const glm::mat4& transform);

        std::vector<Rect> divide(const glm::vec3& divisions) const;

        Corners corners() const;
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

        buffer getVertices(DrawMode mode=DrawMode::Triangles) const;
        static size_t getVertexCount(DrawMode mode=DrawMode::Triangles);
    };

    struct RectMatch
    {
        typedef RectMatchType Type;
        Rect rect;
        Type type;

        RectMatch(const Rect& r, Type t=Type::Overlap);
        bool matches(const Rect& other) const;
    };
}

#endif
