#define _USE_MATH_DEFINES
#include <cmath>

#include <gorn/asset/ShapeMeshFactory.hpp>
#include <gorn/base/Shapes.hpp>
#include <gorn/base/Rect.hpp>
#include <gorn/base/Frustum.hpp>
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

}

