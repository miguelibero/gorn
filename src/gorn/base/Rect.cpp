#include <gorn/base/Rect.hpp>
#include <gorn/base/Shapes.hpp>
#include <gorn/base/Math.hpp>
#include <buffer.hpp>
#include <limits>

namespace gorn
{
    Rect::Rect(const glm::vec3& origin, const glm::vec3& size):
    origin(origin), size(size)
    {
    }

    Rect::Rect(const glm::vec2& origin, const glm::vec2& size):
    origin(origin.x, origin.y, 0.0f), size(size.x, size.y, 0.0f)
    {
    }

    glm::vec3 Rect::min() const
    {
        return origin;
    }

    glm::vec3 Rect::max() const
    {
        return origin+size;
    }

    glm::vec3 Rect::exterior(const glm::vec3& normal) const
    {
        int idx = 0;
        if( normal.y >= 0)
        {
            if( normal.x >= 0)
            {
                idx = 1;
            }
            else
            {
                idx = 0;
            }
        }
        else
        {
            if( normal.x >= 0)
            {
                idx = 2;
            }
            else
            {
                idx = 3;
            }
        }
        if( normal.z >= 0 )
        {
            idx += 4;
        }
        return corners()[idx];
    }

	bool Rect::empty() const
	{
		return Math::isZero(size);
	}

    bool Rect::flat() const
    {
        return Math::isZero(origin.z) && Math::isZero(size.z);
    }

    bool Rect::contains(const glm::vec2& point) const
    {
        auto tmin = min();
        auto tmax = max();
        return point.x >= tmin.x && point.x <= tmax.x
            && point.y >= tmin.y && point.y <= tmax.y;
    }

    bool Rect::contains(const glm::vec3& point) const
    {
        auto tmin = min();
        auto tmax = max();
        return point.x >= tmin.x && point.x <= tmax.x
            && point.y >= tmin.y && point.y <= tmax.y
            && point.z >= tmin.z && point.z <= tmax.z;
    }

    bool Rect::contains(const Rect& other) const
    {
        return contains(other.min()) && contains(other.max());
    }

    bool Rect::intersects(const Rect& other) const
    {
        auto tmin = min();
        auto tmax = max();
        auto omin = other.min();
        auto omax = other.max();
        return !(
            tmax.x < omin.x ||
            omax.x < tmin.x ||
            tmax.y < omin.y ||
            omax.y < tmin.y ||
            tmax.z < omin.z ||
            omax.z < tmin.z
        );
    }

    bool Rect::overlaps(const Rect& other) const
    {
        return contains(other.min()) || contains(other.max());
    }

    bool Rect::matches(const Rect& other, MatchType type) const
    {
        switch(type)
        {
        case MatchType::Contain:
            return contains(other);
        case MatchType::Overlap:
            return overlaps(other);
        case MatchType::Intersect:
            return intersects(other);
        default:
            return false;
        }
    }

    bool Rect::matches(const RectMatch& match) const
    {
        return matches(match.rect, match.type);
    }

    float Rect::area() const
    {
        return size.x*size.y;
    }

    Rect::Corners Rect::corners() const
    {
        return Corners{
            glm::vec3(origin.x + size.x, origin.y + size.y, origin.z),
            glm::vec3(origin.x,          origin.y + size.y, origin.z),
            glm::vec3(origin.x,          origin.y,          origin.z),
            glm::vec3(origin.x + size.x, origin.y,          origin.z),
            glm::vec3(origin.x,          origin.y + size.y, origin.z + size.z),
            glm::vec3(origin.x + size.x, origin.y + size.y, origin.z + size.z),
            glm::vec3(origin.x + size.x, origin.y,          origin.z + size.z),
            glm::vec3(origin.x,          origin.y,          origin.z + size.z)
        };
    }

    CubeShape Rect::shape() const
    {
        return CubeShape(corners());
    }

    Rect Rect::operator*(const glm::mat4& t) const
    {
        Rect r(*this);
        r *= t;
        return r;
    }

    Rect& Rect::operator*=(const glm::mat4& t)
    {
        auto cs = corners();
        glm::vec3 max;
        glm::vec3 min;
        bool init = false;
        for(auto& p : cs)
        {
            p = glm::vec3(t*glm::vec4(p, 1.0f));
            if(init)
            {
                min.x = glm::min(min.x, p.x);
                min.y = glm::min(min.y, p.y);
                min.z = glm::min(min.z, p.z);
                max.x = glm::max(max.x, p.x);
                max.y = glm::max(max.y, p.y);
                max.z = glm::max(max.z, p.z);
            }
            else
            {
                min = p;
                max = p;
                init = true;
            }
        }
        origin = min;
        size = max - min;
        return *this;
    }

    std::vector<Rect> Rect::divide(const glm::vec3& divs) const
    {
        auto fdivs = glm::round(glm::max(divs, glm::vec3(1.0f)));
        std::vector<Rect> parts;
        parts.reserve((size_t)(fdivs.x*fdivs.y*fdivs.z));
        auto tmin = min();
        auto tmax = max();
        auto tsize = size/fdivs;
        auto p = tmin;

        for(p.z=tmin.z;p.z<tmax.z||p.z==tmin.z;p.z+=tsize.z)
        {
            for(p.y=tmin.y;p.y<tmax.y||p.y==tmin.y;p.y+=tsize.y)
            {
                for(p.x=tmin.x;p.x<tmax.x||p.x==tmin.x;p.x+=tsize.x)
                {
                    parts.push_back(Rect(p, tsize));
                    if(tsize.x == 0.0f)
                    {
                        break;
                    }
                }
                if(tsize.y == 0.0f)
                {
                    break;
                }
            }
            if(tsize.z == 0.0f)
            {
                break;
            }
        }

        return parts;
    }

    RectMatch::RectMatch(const Rect& r, Type t):
    rect(r), type(t)
    {
    }

    bool RectMatch::matches(const Rect& other) const
    {
        return rect.matches(other, type);
    }
}
