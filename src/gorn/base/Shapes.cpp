
#include <gorn/base/Shapes.hpp>

namespace gorn
{
    PlaneShape::PlaneShape()
    {
    }

    PlaneShape::PlaneShape(const glm::vec3& bl,  
        const glm::vec3& br,
        const glm::vec3& tr,
        const glm::vec3& tl):
    bottomleft(bl), bottomright(br), topright(tr), topleft(tl)
    {
    }

    PlaneShape::PlaneShape(const Corners& corners):
    bottomleft(corners[0]), bottomright(corners[1]),
    topright(corners[2]), topleft(corners[3])
    {
    }

    PlaneShape& PlaneShape::withTopLeft(const glm::vec3& p)
    {
        topleft = p;
        return *this;
    }

    PlaneShape& PlaneShape::withTopRight(const glm::vec3& p)
    {
        topright = p;
        return *this;
    }

    PlaneShape& PlaneShape::withBottomLeft(const glm::vec3& p)
    {
        bottomleft = p;
        return *this;
    }

    PlaneShape& PlaneShape::withBottomRight(const glm::vec3& p)
    {
        bottomright = p;
        return *this;
    }

    PlaneShape::Corners PlaneShape::corners() const
    {
        return Corners{
            bottomleft,
            bottomright,
            topright,
            topleft
        };  
    }

    CubeShape::CubeShape()
    {
    }

    CubeShape::CubeShape(const PlaneShape& f, const PlaneShape& b):
    front(f), back(b)
    {
    }

    CubeShape::CubeShape(const Corners& cs):
    front(cs[0], cs[1], cs[2], cs[3]),
    back(cs[4], cs[5], cs[6], cs[7])
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
