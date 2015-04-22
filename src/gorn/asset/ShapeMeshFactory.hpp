#ifndef __gorn__ShapeMeshFactory__
#define __gorn__ShapeMeshFactory__

#include <vector>
#include <glm/glm.hpp>
#include <gorn/base/Config.hpp>
#include <gorn/render/RenderEnums.hpp>

namespace gorn
{
    class Rect;
    class Frustum;
    class Mesh;
    class PlaneShape;
    class CubeShape;
    class SphereShape;

	class ShapeMeshFactory
	{
	public:
		ShapeMeshFactory() = delete;

        static Mesh create(const Rect& rect, DrawMode mode);
        static Mesh create(const Frustum& frustum, DrawMode mode);
        static Mesh create(const CubeShape& cube, DrawMode mode);
        static Mesh create(const SphereShape& sphere);
        static Mesh create(const PlaneShape& plane);
	};
}

#endif
