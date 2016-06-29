#define _USE_MATH_DEFINES
#include <cmath>

#include <gorn/asset/ShapeMeshFactory.hpp>
#include <gorn/base/Shapes.hpp>
#include <gorn/base/Rect.hpp>
#include <gorn/base/Frustum.hpp>
#include <gorn/base/Ray.hpp>
#include <gorn/render/RenderKinds.hpp>

namespace gorn
{
    Mesh::Elements getPlaneElements(DrawMode mode)
    {
        switch(mode)
        {
        case DrawMode::Quads:
        {
            return Mesh::Elements{
                0, 2
            };
            break;
        }
        case DrawMode::Triangles:
        {
            return Mesh::Elements{
                0, 1, 2, 2, 3, 0 
            };
            break;
        }
        case DrawMode::Lines:
        {
            return Mesh::Elements{
                0, 1, 1, 2, 2, 3, 3, 0
            };
            break;
        }
        case DrawMode::Points:
        {
            return Mesh::Elements{
                0, 1, 2, 3
            };
            break;
        }
        default:
            return Mesh::Elements{};
            break;
        }
    }

	size_t getPlaneElementsSize(DrawMode mode)
	{
		switch (mode)
		{
		case DrawMode::Quads:
		{
			return 2;
			break;
		}
		case DrawMode::Triangles:
		{
			return 6;
			break;
		}
		case DrawMode::Lines:
		{
			return 8;
			break;
		}
		case DrawMode::Points:
		{
			return 4;
			break;
		}
		default:
			return 0;
			break;
		}
	}

    template<>
    Mesh ShapeMeshFactory::create(const Rect& rect, DrawMode mode)
    {
		return create(rect.shape(), mode);
    }

    template<>
    Mesh ShapeMeshFactory::create(const Frustum& frustum, DrawMode mode)
    {
        return create(frustum.shape(), mode);
    }

    template<>
    Mesh ShapeMeshFactory::create(const PlaneShape& plane, DrawMode mode)
    {
		auto cs = plane.corners();
		auto n = plane.normal();
		std::vector<glm::vec3> pos(cs.size());
		std::move(cs.begin(), cs.end(), pos.begin());
		std::vector<glm::vec3> norm{
			n, n, n, n
		};
		std::vector<glm::vec2> tex{
			glm::vec2(1, 1), glm::vec2(0, 1),
			glm::vec2(0, 0), glm::vec2(1, 0),
		};
        auto elms = getPlaneElements(mode);

        Mesh mesh;
        mesh.setVertices(AttributeKind::Position, std::move(pos));
        mesh.setVertices(AttributeKind::Normal, std::move(norm));
		mesh.setVertices(AttributeKind::TexCoords, std::move(tex));
        mesh.setElements(std::move(elms));
        mesh.setDrawMode(mode);
        return mesh;
    }

    template<>
    Mesh ShapeMeshFactory::create(const CubeShape& cube, DrawMode mode)
    {
		Mesh mesh;
		mesh.setDrawMode(mode);
		for(auto& side : cube.sides())
		{
			mesh += create(side, mode);
		}
        return mesh;
    }

    template<>
    Mesh ShapeMeshFactory::create(const SphereShape& sphere, DrawMode mode)
    {
        float R = 1.f/(float)(sphere.rings-1);
        float S = 1.f/(float)(sphere.sectors-1);
        float texScale = 1.f;
        size_t n = sphere.rings * sphere.sectors;
        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> texCoords;
        Mesh::Elements elements;
      
        {
            positions.reserve(n);
            texCoords.reserve(n);
            for (int r = 0; r < (int)sphere.rings; r++)
            {
                for (int s = 0; s < (int)sphere.sectors; s++)
                {
                    float u = (float)s*S;
                    float v = (float)r*R;
                    float theta = u * 2.0f * (float)M_PI;
                    float rho = v * (float)M_PI;
                    positions.push_back(sphere.center +
                        glm::vec3(
                            cos(theta) * sin(rho),
                            sin((float)-M_PI_2 + rho),
                            sin(theta) * sin(rho)
                        ));
                    texCoords.push_back(glm::vec2(
                        u*texScale,
                        v*texScale
                    ));
                }
            }
        }
        
        {
            elements.reserve(n * 6);
            for (int r = 0; r < (int)sphere.rings - 1; r++)
            {
                for (int s = 0; s < (int)sphere.sectors - 1; s++)
                {
                    elements.push_back(r * sphere.sectors + s);
                    elements.push_back(r * sphere.sectors + (s+1));
                    elements.push_back((r+1) * sphere.sectors + (s+1));
                    elements.push_back((r+1) * sphere.sectors + (s+1));
                    elements.push_back((r+1) * sphere.sectors + s);
                    elements.push_back(r * sphere.sectors + s);
                }
            }
        }
        
        Mesh mesh;
        mesh.setVertices(AttributeKind::Normal, positions);
        mesh.setVertices(AttributeKind::Position, std::move(positions));
        mesh.setVertices(AttributeKind::TexCoords, std::move(texCoords));
        mesh.setElements(std::move(elements));
        return std::move(mesh);
    } 

	template<>
	Mesh ShapeMeshFactory::create(const Ray& ray, DrawMode mode)
	{
		std::vector<glm::vec3> pos{
			ray.origin, ray.origin + ray.direction
		};
		Mesh mesh;
		mesh.setVertices(AttributeKind::Position, std::move(pos));
		mesh.setElements({ 0, 1 });
		mesh.setDrawMode(mode);
		return mesh;
	}

	void reserveCubesMesh(Mesh& mesh, size_t size, DrawMode mode)
	{
		mesh.reserveVertices<glm::vec3>(AttributeKind::Position, 24 * size);
		mesh.reserveVertices<glm::vec3>(AttributeKind::Normal, 24 * size);
		mesh.reserveVertices<glm::vec3>(AttributeKind::Normal, 24 * size);
		mesh.reserveElements(getPlaneElementsSize(mode) * 6 * size);
	}

	template<>
	void ShapeMeshFactory::reserve(Mesh& mesh, const std::vector<Rect>& shapes, DrawMode mode)
	{
		reserveCubesMesh(mesh, shapes.size(), mode);
	}

	template<>
	void ShapeMeshFactory::reserve(Mesh& mesh, const std::vector<Frustum>& shapes, DrawMode mode)
	{
		reserveCubesMesh(mesh, shapes.size(), mode);
	}

	template<>
	void ShapeMeshFactory::reserve(Mesh& mesh, const std::vector<PlaneShape>& shapes, DrawMode mode)
	{
		auto size = shapes.size();
		mesh.reserveVertices<glm::vec3>(AttributeKind::Position, 4 * size);
		mesh.reserveVertices<glm::vec3>(AttributeKind::Normal, 4 * size);
		mesh.reserveVertices<glm::vec3>(AttributeKind::Normal, 4 * size);
		mesh.reserveElements(getPlaneElementsSize(mode) * size);
	}

	template<>
	void ShapeMeshFactory::reserve(Mesh& mesh, const std::vector<CubeShape>& shapes, DrawMode mode)
	{
		reserveCubesMesh(mesh, shapes.size(), mode);
	}

	template<>
	void ShapeMeshFactory::reserve(Mesh& mesh, const std::vector<SphereShape>& shapes, DrawMode mode)
	{
		size_t vc = 0;
		size_t ec = 0;
		for(auto& shape : shapes)
		{
			vc += shape.rings*shape.sectors;
			ec += (shape.rings-1)*(shape.sectors-1)*6;
		}
		mesh.reserveVertices<glm::vec3>(AttributeKind::Position, vc);
		mesh.reserveVertices<glm::vec3>(AttributeKind::Normal, vc);
		mesh.reserveVertices<glm::vec3>(AttributeKind::TexCoords, vc);
		mesh.reserveElements(ec);
	}

	template<>
	void ShapeMeshFactory::reserve(Mesh& mesh, const std::vector<Ray>& shapes, DrawMode mode)
	{
		auto size = shapes.size();
		mesh.reserveVertices<glm::vec3>(AttributeKind::Position, 2*size);
		mesh.reserveElements(2*size);
	}
}

