#define _USE_MATH_DEFINES
#include <cmath>

#include <gorn/asset/ShapeMeshFactory.hpp>
#include <gorn/base/Shapes.hpp>
#include <gorn/base/Rect.hpp>
#include <gorn/base/Frustum.hpp>
#include <gorn/base/Ray.hpp>

namespace gorn
{
	static Mesh::Elements planeElementsQuads{
		0, 2
	};

	static Mesh::Elements planeElementsTris{
		0, 1, 2, 2, 3, 0
	};

	static Mesh::Elements planeElementsLines{
		0, 1, 1, 2, 2, 3, 3, 0
	};

	static Mesh::Elements planeElementsPoints{
		0, 1, 2, 3
	};

	static Mesh::Elements planeElementsEmpty{
		0, 1, 2, 3
	};

    const Mesh::Elements& getPlaneElements(DrawMode mode)
    {
        switch(mode)
        {
        case DrawMode::Quads:
        {
            return planeElementsQuads;
            break;
        }
        case DrawMode::Triangles:
        {
            return planeElementsTris;
            break;
        }
        case DrawMode::Lines:
        {
            return planeElementsLines;
            break;
        }
        case DrawMode::Points:
        {
            return planeElementsPoints;
            break;
        }
        default:
            return planeElementsEmpty;
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

	void reserveCubesMesh(Mesh& mesh, size_t size, DrawMode mode)
	{
		mesh.reserveVertices<glm::vec3>(AttributeType::Position, 24 * size);
		mesh.reserveVertices<glm::vec3>(AttributeType::Normal, 24 * size);
		mesh.reserveVertices<glm::vec3>(AttributeType::TexCoords, 24 * size);
		mesh.reserveElements(getPlaneElementsSize(mode) * 6 * size);
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

	static std::vector<glm::vec2> planeTexCoords{
		glm::vec2(1, 1), glm::vec2(0, 1),
		glm::vec2(0, 0), glm::vec2(1, 0),
	};

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

        auto elms = getPlaneElements(mode);

        Mesh mesh;

        mesh.setVertices(AttributeType::Position, std::move(pos));
        mesh.setVertices(AttributeType::Normal, std::move(norm));
		mesh.setVertices(AttributeType::TexCoords, std::move(planeTexCoords));

        mesh.setElements(std::move(elms));
        mesh.setDrawMode(mode);
        return mesh;
    }

    template<>
    Mesh ShapeMeshFactory::create(const CubeShape& cube, DrawMode mode)
    {
		Mesh mesh;
		mesh.setDrawMode(mode);
		reserveCubesMesh(mesh, 1, mode);
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
            for (Mesh::idx_t r = 0; r < (Mesh::idx_t)sphere.rings - 1; r++)
            {
                for (Mesh::idx_t s = 0; s < (Mesh::idx_t)sphere.sectors - 1; s++)
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
        mesh.setVertices(AttributeType::Normal, positions);
        mesh.setVertices(AttributeType::Position, std::move(positions));
        mesh.setVertices(AttributeType::TexCoords, std::move(texCoords));
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
		mesh.setVertices(AttributeType::Position, std::move(pos));
		mesh.setElements({ 0, 1 });
		mesh.setDrawMode(mode);
		return mesh;
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
		mesh.reserveVertices<glm::vec3>(AttributeType::Position, 4 * size);
		mesh.reserveVertices<glm::vec3>(AttributeType::Normal, 4 * size);
		mesh.reserveVertices<glm::vec3>(AttributeType::TexCoords, 4 * size);
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
		mesh.reserveVertices<glm::vec3>(AttributeType::Position, vc);
		mesh.reserveVertices<glm::vec3>(AttributeType::Normal, vc);
		mesh.reserveVertices<glm::vec3>(AttributeType::TexCoords, vc);
		mesh.reserveElements(ec);
	}

	template<>
	void ShapeMeshFactory::reserve(Mesh& mesh, const std::vector<Ray>& shapes, DrawMode mode)
	{
		auto size = shapes.size();
		mesh.reserveVertices<glm::vec3>(AttributeType::Position, 2*size);
		mesh.reserveElements(2*size);
	}
}

