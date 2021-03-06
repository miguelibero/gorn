#ifndef __gorn__Frustum__
#define __gorn__Frustum__

#include <array>
#include <glm/glm.hpp>

namespace gorn
{
    enum class FrustumPlaneType : size_t
    {
        Right = 0,
        Left,
        Bottom,
        Top,
        Far,
        Near
    };

    enum class FrustumMatchType
    {
        Inside,
        Outside,
        Partial
    };

    class Rect;
	class Ray;
    class CubeShape;

    class Frustum
    {
    private:
        typedef FrustumPlaneType PlaneType;
        typedef FrustumMatchType MatchType;
        typedef std::array<glm::vec4,6> Planes;
        glm::mat4 _matrix;    
        glm::mat4 _inverse;
        Planes _planes;

        void init();
    public:
        Frustum(const glm::mat4& matrix=glm::mat4());
        Frustum& operator=(const glm::mat4& matrix);

        CubeShape shape() const;

        const glm::mat4& getMatrix() const;
        const glm::mat4& getInverse() const;

        Ray getPointRay(const glm::vec2& p) const;
		glm::vec2 getRayPoint(const Ray& r) const;

        Frustum& operator*=(const glm::mat4& transform);
        Frustum operator*(const glm::mat4& transform) const;

        MatchType matches(const Rect& rect) const;
        bool sees(const Rect& rect) const;
        bool sees(const glm::vec3& point) const;
    };

   
}

#endif
