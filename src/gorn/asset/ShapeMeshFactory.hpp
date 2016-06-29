#ifndef __gorn__ShapeMeshFactory__
#define __gorn__ShapeMeshFactory__

#include <vector>
#include <glm/glm.hpp>
#include <gorn/base/Config.hpp>
#include <gorn/gl/Enums.hpp>
#include <gorn/asset/Mesh.hpp>

namespace gorn
{
    class Frustum;
    class PlaneShape;
    class CubeShape;
    class SphereShape;
	class Ray;

    class ShapeMeshFactory
    {
    public:
        ShapeMeshFactory() = delete;

        template<typename S>
        static Mesh create(const S& shape, DrawMode mode=DrawMode::Triangles);

        template<typename S>
        static Mesh create(const std::vector<S>& shapes,
            DrawMode mode=DrawMode::Triangles);

		template<typename S>
		static void reserve(Mesh& mesh, const std::vector<S>& shapes, DrawMode mode);
    };

    template<typename S>
    Mesh ShapeMeshFactory::create(const std::vector<S>& shapes, DrawMode mode)
    {
        Mesh mesh;
        mesh.setDrawMode(mode);
		reserve(mesh, shapes, mode);
        for(auto& shape : shapes)
        {
            mesh += create(shape, mode);
        }
        return mesh;
    }

	template<>
	Mesh ShapeMeshFactory::create(const Rect& rect, DrawMode mode);
    template<>
    Mesh ShapeMeshFactory::create(const Frustum& frustum, DrawMode mode);
    template<>
    Mesh ShapeMeshFactory::create(const PlaneShape& plane, DrawMode mode);
    template<>
    Mesh ShapeMeshFactory::create(const CubeShape& cube, DrawMode mode);
    template<>
    Mesh ShapeMeshFactory::create(const SphereShape& sphere, DrawMode mode);
	template<>
	Mesh ShapeMeshFactory::create(const Ray& ray, DrawMode mode);

	template<>
	void ShapeMeshFactory::reserve(Mesh& mesh, const std::vector<Rect>& shapes, DrawMode mode);
	template<>
	void ShapeMeshFactory::reserve(Mesh& mesh, const std::vector<Frustum>& shapes, DrawMode mode);
	template<>
	void ShapeMeshFactory::reserve(Mesh& mesh, const std::vector<PlaneShape>& shapes, DrawMode mode);
	template<>
	void ShapeMeshFactory::reserve(Mesh& mesh, const std::vector<CubeShape>& shapes, DrawMode mode);
	template<>
	void ShapeMeshFactory::reserve(Mesh& mesh, const std::vector<SphereShape>& shapes, DrawMode mode);
	template<>
	void ShapeMeshFactory::reserve(Mesh& mesh, const std::vector<Ray>& shapes, DrawMode mode);
}

#endif
