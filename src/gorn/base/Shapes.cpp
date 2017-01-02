
#include <gorn/base/Shapes.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{
    PlaneShape::PlaneShape()
    {
    }

    PlaneShape::PlaneShape(const glm::vec3& x,
        const glm::vec3& y,
        const glm::vec3& c):
    xaxis(x), yaxis(y), center(c)
    {
    }

    PlaneShape::PlaneShape(const Corners& cs)
    {
        xaxis = cs[0] - cs[1];
        yaxis = cs[1] - cs[2];
        center = cs[2] + 0.5f*xaxis + 0.5f*yaxis;
    }

    PlaneShape& PlaneShape::withXAxis(const glm::vec3& x)
    {
        xaxis = x;
        return *this;
    }

    PlaneShape& PlaneShape::withYAxis(const glm::vec3& y)
    {
        yaxis = y;
        return *this;
    }

    PlaneShape& PlaneShape::withCenter(const glm::vec3& c)
    {
        center = c;
        return *this;
    }

    PlaneShape::Corners PlaneShape::corners() const
    {
        return Corners{
            center - 0.5f*xaxis - 0.5f*yaxis,
            center + 0.5f*xaxis - 0.5f*yaxis,
            center + 0.5f*xaxis + 0.5f*yaxis,
            center - 0.5f*xaxis + 0.5f*yaxis
        };
    }

    glm::vec3 PlaneShape::normal() const
    {
        return glm::normalize(glm::cross(yaxis, xaxis));
    }

    QuadShape PlaneShape::quad() const
    {
        return QuadShape(corners());
    }

    QuadShape::QuadShape():
    corners({
        glm::vec3(-1.0f, -1.0f, 0.0f),
        glm::vec3( 1.0f, -1.0f, 0.0f),
        glm::vec3( 1.0f,  1.0f, 0.0f),
        glm::vec3(-1.0f,  1.0f, 0.0f)
    })
    {
    }

    QuadShape::QuadShape(const Corners& cs):
    corners(cs)
    {
    }

    PlaneShape QuadShape::plane() const
    {
        return PlaneShape(corners);
    }

    glm::vec3 QuadShape::normal() const
    {
        return plane().normal();
    }

    CubeShape::CubeShape()
    {
    }

    CubeShape::CubeShape(const PlaneShape& front, const PlaneShape& back)
    {
        auto fc = front.corners();
		auto bc = back.corners();
        corners[0] = fc[0];
        corners[1] = fc[1];
        corners[2] = fc[2];
        corners[3] = fc[3];
        corners[4] = bc[0];
        corners[5] = bc[1];
        corners[6] = bc[2];
        corners[7] = bc[3];
    }

    CubeShape::CubeShape(const Corners& cs) :
    corners(cs)
    {
    }

	CubeShape::Sides CubeShape::sides() const
	{
		Sides sides;
        auto& cs = corners;
		sides[0] = QuadShape({ cs[0], cs[1], cs[2], cs[3] });
        sides[1] = QuadShape({ cs[4], cs[5], cs[6], cs[7] });
        sides[2] = QuadShape({ cs[0], cs[1], cs[4], cs[5] });
        sides[3] = QuadShape({ cs[1], cs[4], cs[7], cs[2] });
        sides[4] = QuadShape({ cs[5], cs[0], cs[3], cs[6] });
        sides[5] = QuadShape({ cs[6], cs[7], cs[2], cs[3] });
		return sides;
	}

    SphereShape::SphereShape():
    rings(10), sectors(10)
    {
    }

    SphereShape& SphereShape::withRings(idx_t val)
    {
        rings = val;
        return *this;
    }

    SphereShape& SphereShape::withSectors(idx_t val)
    {
        sectors = val;
        return *this;
    }

    SphereShape& SphereShape::withCenter(const glm::vec3& val)
    {
        center = val;
        return *this;
    }

}
