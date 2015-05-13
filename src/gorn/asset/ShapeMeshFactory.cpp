#include <gorn/asset/ShapeMeshFactory.hpp>
#include <gorn/base/Shapes.hpp>
#include <gorn/base/Rect.hpp>
#include <gorn/base/Frustum.hpp>
#include <gorn/render/RenderKinds.hpp>

namespace gorn
{
    Mesh::Elements getCubeElements(DrawMode mode)
    {
        switch(mode)
        {
        case DrawMode::Quads:
        {
            return Mesh::Elements{
                0, 2, 1, 6, 5, 7, 
                4, 3, 2, 7, 0, 5
            };
            break;
        }
        case DrawMode::Triangles:
        {
            return Mesh::Elements{
                0, 1, 2, 2, 3, 0,
                1, 5, 6, 6, 2, 1,
                5, 4, 7, 7, 6, 5,
                4, 0, 3, 3, 7, 4,
                2, 6, 7, 7, 3, 2,
                0, 4, 5, 5, 1, 0
            };
            break;
        }

        case DrawMode::Lines:
        {
            return Mesh::Elements{
                0, 1, 1, 2, 2, 3, 3, 0,
                4, 5, 5, 6, 6, 7, 7, 4,
                0, 4, 1, 5, 2, 6, 3, 7
            };
            break;
        }
        case DrawMode::Points:
        {
            return Mesh::Elements{
                0, 1, 2, 3, 4, 5, 6, 7
            };
            break;
        }
        default:
            return Mesh::Elements{};
            break;
        }
    }

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
        auto tmin = rect.min();
        auto tmax = rect.max();
        bool tflat = rect.flat();
        Mesh::Elements elements;

        std::vector<glm::vec3> positions{
            glm::vec3(tmin.x, tmin.y, tmin.z),
            glm::vec3(tmax.x, tmin.y, tmin.z),
            glm::vec3(tmin.x, tmax.y, tmin.z),
            glm::vec3(tmax.x, tmax.y, tmin.z)
        };
        std::vector<glm::vec3> normals{
            glm::vec3( 1.0f,  0.0f,  0.0f),
            glm::vec3(-1.0f,  0.0f,  0.0f),
            glm::vec3( 0.0f,  1.0f,  0.0f),
            glm::vec3( 0.0f, -1.0f,  0.0f),
            glm::vec3( 0.0f,  0.0f,  1.0f),
            glm::vec3( 0.0f,  0.0f, -1.0f)
        };
        if(tflat)
        {
            elements = getPlaneElements(mode);
        }
        else
        {
            elements = getCubeElements(mode);
            positions.insert(positions.end(), {
                glm::vec3(tmin.x, tmin.y, tmax.z),
                glm::vec3(tmax.x, tmin.y, tmax.z),
                glm::vec3(tmin.x, tmax.y, tmax.z),
                glm::vec3(tmax.x, tmax.y, tmax.z)
            });
        }

        Mesh mesh;
        mesh.setVertices(AttributeKind::Normal, std::move(normals));
        mesh.setVertices(AttributeKind::Position, std::move(positions));
        mesh.setElements(std::move(elements));
        mesh.setDrawMode(mode);
        return mesh;
    }

    template<>
    Mesh ShapeMeshFactory::create(const Frustum& frustum, DrawMode mode)
    {
        return create(frustum.shape(), mode);
    }

    template<>
    Mesh ShapeMeshFactory::create(const PlaneShape& plane, DrawMode mode)
    {
        Mesh mesh;
        return mesh;
    }

    template<>
    Mesh ShapeMeshFactory::create(const CubeShape& cube, DrawMode mode)
    {
        std::vector<glm::vec3> positions;
        auto cs = cube.corners();
        positions.resize(cs.size());
        std::move(cs.begin(), cs.end(), positions.begin());

        auto elements = getCubeElements(mode);

        Mesh mesh;
        mesh.setVertices(AttributeKind::Position, std::move(positions));
        mesh.setElements(std::move(elements));
        mesh.setDrawMode(mode);
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

