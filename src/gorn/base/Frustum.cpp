#include <gorn/base/Frustum.hpp>
#include <gorn/base/Rect.hpp>
#include <gorn/base/Ray.hpp>
#include <gorn/base/Shapes.hpp>
#include <buffer_writer.hpp>
#include <glm/gtc/matrix_inverse.hpp>

namespace gorn
{
    Frustum::Frustum(const glm::mat4& matrix):
    _matrix(matrix)
    {
        init();
    }

    Frustum& Frustum::operator=(const glm::mat4& matrix)
    {
        _matrix = matrix;
        init();
        return *this;
    }

    Frustum& Frustum::operator*=(const glm::mat4& transform)
    {
        _matrix *= transform;
        init();
        return *this;
    }

    Frustum Frustum::operator*(const glm::mat4& transform) const
    {
        Frustum result(*this);
        result *= transform;
        return result;
    }

    void Frustum::init()
    {
        auto& m = _matrix;
        _inverse = glm::inverse(m);
        _planes[static_cast<size_t>(PlaneType::Right)] = glm::vec4(
                                    m[0][3] - m[0][0],
                                    m[1][3] - m[1][0],
                                    m[2][3] - m[2][0],
                                    m[3][3] - m[3][0]);

        _planes[static_cast<size_t>(PlaneType::Left)] = glm::vec4(
                                    m[0][3] + m[0][0],
                                    m[1][3] + m[1][0],
                                    m[2][3] + m[2][0],
                                    m[3][3] + m[3][0]);

        _planes[static_cast<size_t>(PlaneType::Bottom)] = glm::vec4(
                                    m[0][3] + m[0][1],
                                    m[1][3] + m[1][1],
                                    m[2][3] + m[2][1],
                                    m[3][3] + m[3][1]);

        _planes[static_cast<size_t>(PlaneType::Top)] = glm::vec4(
                                    m[0][3] - m[0][1],
                                    m[1][3] - m[1][1],
                                    m[2][3] - m[2][1],
                                    m[3][3] - m[3][1]);

        _planes[static_cast<size_t>(PlaneType::Far)] = glm::vec4(
                                    m[0][3] - m[0][2],
                                    m[1][3] - m[1][2],
                                    m[2][3] - m[2][2],
                                    m[3][3] - m[3][2]);

        _planes[static_cast<size_t>(PlaneType::Near)] = glm::vec4(
                                    m[0][3] + m[0][2],
                                    m[1][3] + m[1][2],
                                    m[2][3] + m[2][2],
                                    m[3][3] + m[3][2]);
        for(auto& plane : _planes)
        {
            plane /= glm::length(glm::vec3(plane));
        }
    }

    Frustum::MatchType Frustum::matches(const Rect& rect) const
    {
        MatchType mtype = MatchType::Inside;
        for(size_t i = 0; i < _planes.size(); ++i)
        {
			glm::vec3 p;
            auto& plane = _planes[i];
            auto pnorm = glm::vec3(plane);
			p = rect.exterior(pnorm);
			float dext = glm::dot(p, pnorm) + plane.w;
			if (dext < 0)
			{
				return MatchType::Outside;
			}
			p = rect.exterior(-pnorm);
			float dint = glm::dot(p, pnorm) + plane.w;
			if (dint < 0)
			{
				mtype = MatchType::Partial;
			}
        }
        return mtype;
    }

    bool Frustum::sees(const Rect& rect) const
    {
        auto m = matches(rect);
        return m == MatchType::Inside || m == MatchType::Partial;
    }

    bool Frustum::sees(const glm::vec3& point) const
    {
        for(size_t i = 0; i < _planes.size(); ++i)
        {
            auto& plane = _planes[i];
            auto pnorm = glm::vec3(plane);
            float dext = glm::dot(point, pnorm) + plane.w;
            if(dext < 0)
            {
                return false;
            }
        }
        return true;
    }

	Ray Frustum::getPointRay(const glm::vec2& p) const
	{
		glm::vec4 near4(_inverse * glm::vec4(p.x, p.y, 1.0f, 1.0f));
		glm::vec4 far4(_inverse * glm::vec4(p.x, p.y, -1.0f, 1.0f));
		glm::vec3 near(near4 / near4.w);
		glm::vec3 far(far4 / far4.w);
		return Ray(near, far - near);
	}

	glm::vec2 Frustum::getRayPoint(const Ray& r) const
	{
		return glm::vec2(_matrix * glm::vec4(r.origin, 1.0f));
	}

    const glm::mat4& Frustum::getMatrix() const
    {
        return _matrix;
    }

    const glm::mat4& Frustum::getInverse() const
    {
        return _inverse;
    }

    CubeShape Frustum::shape() const
    {
        CubeShape::Corners corners{{
            glm::vec3(-1.0f, -1.0f,  1.0f),
            glm::vec3( 1.0f, -1.0f,  1.0f),
            glm::vec3( 1.0f,  1.0f,  1.0f),
            glm::vec3(-1.0f,  1.0f,  1.0f),
            glm::vec3(-1.0f, -1.0f, -1.0f),
            glm::vec3( 1.0f, -1.0f, -1.0f),
            glm::vec3( 1.0f,  1.0f, -1.0f),
            glm::vec3(-1.0f,  1.0f, -1.0f)
        }};

        for(auto& c : corners)
        {
            auto tc = _inverse * glm::vec4(c, 1.0f);
            c = glm::vec3( tc / tc.w );
        }
        return CubeShape(corners);
    }

}
