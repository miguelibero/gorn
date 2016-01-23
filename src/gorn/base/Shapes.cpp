
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
        yaxis = cs[0] - cs[3];
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
            center + 0.5f*xaxis + 0.5f*yaxis,
            center - 0.5f*xaxis + 0.5f*yaxis,
            center - 0.5f*xaxis - 0.5f*yaxis,
            center + 0.5f*xaxis - 0.5f*yaxis
        };  
    }

    glm::vec3 PlaneShape::normal() const
    {
        return glm::cross(xaxis, yaxis);
    }

    CubeShape::CubeShape()
    {
    }

    CubeShape::CubeShape(const PlaneShape& f, const PlaneShape& b):
    front(f), back(b)
    {
    }

    CubeShape::CubeShape(const Corners& cs) :
        front({ cs[0], cs[1], cs[2], cs[3] }),
        back({ cs[4], cs[5], cs[6], cs[7] })
    {
    }

    CubeShape& CubeShape::withFront(const PlaneShape& val)
    {
        front = val;
        return *this;
    }

    CubeShape& CubeShape::withBack(const PlaneShape& val)
    {
        front = val;
        return *this;
    }

    CubeShape::Corners CubeShape::corners() const
    {
        Corners corners;
        auto fcorners = front.corners();
        auto bcorners = back.corners();
        std::move(bcorners.begin(), bcorners.end(), corners.begin()+fcorners.size());
        std::move(fcorners.begin(), fcorners.end(), corners.begin());
        return corners;
    }

    CubeShape::Normals CubeShape::normals() const
    {
        Normals normals;
        front.normal();
        back.normal();
        return normals;
    }

    SphereShape::SphereShape():
    rings(10), sectors(10)
    {
    }

    SphereShape& SphereShape::withRings(size_t val)
    {
        rings = val;
        return *this;
    }

    SphereShape& SphereShape::withSectors(size_t val)
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
