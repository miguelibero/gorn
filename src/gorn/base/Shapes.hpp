#ifndef __gorn__Shapes__
#define __gorn__Shapes__

#include <glm/glm.hpp>
#include <array>

namespace gorn
{
    class PlaneShape
    {
    public:
        typedef std::array<glm::vec3, 4> Corners;

        glm::vec3 xaxis;
        glm::vec3 yaxis;
        glm::vec3 center;

        PlaneShape();
        PlaneShape(const glm::vec3& x,
            const glm::vec3& y,
            const glm::vec3& center);
        PlaneShape(const Corners& cs);

        PlaneShape& withXAxis(const glm::vec3& x);
        PlaneShape& withYAxis(const glm::vec3& y);
        PlaneShape& withCenter(const glm::vec3& center);

        Corners corners() const;
        glm::vec3 normal() const;
    };

    class CubeShape
    {
    public:
        typedef std::array<glm::vec3, 8> Corners;
        typedef std::array<glm::vec3, 6> Normals;
        PlaneShape front;
        PlaneShape back;

        CubeShape();
        CubeShape(const PlaneShape& front, const PlaneShape& back);
        CubeShape(const Corners& cs);

        CubeShape& withFront(const PlaneShape& front);
        CubeShape& withBack(const PlaneShape& back);

        Corners corners() const;
        Normals normals() const;
    };

    class SphereShape
    {
    public:
        size_t rings;
        size_t sectors;
        glm::vec3 center;

        SphereShape();
        SphereShape& withRings(size_t rings);
        SphereShape& withSectors(size_t sectors);
        SphereShape& withCenter(const glm::vec3& center);
    };

}

#endif
