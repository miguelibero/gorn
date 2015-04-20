#include <gorn/asset/ShapeMeshFactory.hpp>
#include <gorn/asset/Mesh.hpp>
#include <gorn/base/Shapes.hpp>
#include <gorn/base/Rect.hpp>
#include <gorn/base/Frustum.hpp>

namespace gorn
{
    Mesh::Elements getCubeElements(DrawMode mode)
    {
        switch(mode)
        {
        case DrawMode::Quads:
        {
            return Mesh::Elements{
                0, 3, 4, 7,
                1, 2, 5, 6
            };
            break;
        }
        case DrawMode::Triangles:
        {
            return Mesh::Elements{
                0, 1, 3, 3, 2, 0,
                0, 2, 4, 4, 5, 0,
                0, 5, 7, 7, 1, 0,
                1, 7, 6, 6, 3, 1,
                6, 4, 2, 2, 3, 6,
                4, 6, 7, 7, 5, 4
            };
            break;
        }
        case DrawMode::Lines:
        {
            return Mesh::Elements{
                0, 1, 1, 3, 3, 2, 2, 0,
                4, 5, 5, 7, 7, 6, 6, 4,
                0, 4, 1, 5, 3, 7, 2, 6
            };
            break;
        }
        case DrawMode::Points:
        {
            return Mesh::Elements{
                0, 1, 3, 2, 4, 5, 7, 6
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


    Mesh ShapeMeshFactory::create(const Rect& rect, DrawMode mode)
    {
        auto tmin = rect.min();
        auto tmax = rect.max();
        bool tflat = rect.flat();
        Mesh::Elements elements;

        Mesh::Positions positions{
            glm::vec3(tmin.x, tmin.y, tmin.z),
            glm::vec3(tmax.x, tmin.y, tmin.z),
            glm::vec3(tmax.x, tmax.y, tmin.z),
            glm::vec3(tmin.x, tmax.y, tmin.z)
        };
        Mesh::Normals normals{
            glm::vec3( 1.0f,  0.0f,  0.0f),
            glm::vec3(-1.0f,  0.0f,  0.0f),
            glm::vec3( 0.0f,  1.0f,  0.0f),
            glm::vec3( 0.0f, -1.0f,  0.0f),
            glm::vec3( 0.0f,  0.0f,  1.0f),
            glm::vec3( 0.0f,  0.0f, -1.0f),
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
                glm::vec3(tmax.x, tmax.y, tmax.z),
                glm::vec3(tmin.x, tmax.y, tmax.z),
            });
        }

        Mesh mesh;
        mesh.setNormals(std::move(normals));
        mesh.setPositions(std::move(positions));
        mesh.setElements(std::move(elements));
        mesh.setDrawMode(mode);
        return mesh;
    }

    Mesh ShapeMeshFactory::create(const Frustum& frustum, DrawMode mode)
    {
        return create(frustum.shape(), mode);
    }

    Mesh ShapeMeshFactory::create(const PlaneShape& plane)
    {
        Mesh mesh;
        return mesh;
    }

    Mesh ShapeMeshFactory::create(const CubeShape& cube, DrawMode mode)
    {
        Mesh::Elements elements;
        Mesh::Positions positions;

        auto cs = cube.corners();
        positions.resize(cs.size());
        std::move(cs.begin(), cs.end(), positions.begin());

        elements = getCubeElements(mode);

        Mesh mesh;
        mesh.setPositions(std::move(positions));
        mesh.setElements(std::move(elements));
        mesh.setDrawMode(mode);
        return mesh;
    }

    Mesh ShapeMeshFactory::create(const SphereShape& sphere)
    {
        float R = 1.f/(float)(sphere.rings-1);
        float S = 1.f/(float)(sphere.sectors-1);
        float texScale = 1.f;
        size_t n = sphere.rings * sphere.sectors;
        Mesh::Positions positions;
        Mesh::TexCoords texCoords;
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
        mesh.setNormals(Mesh::Normals(positions));
        mesh.setPositions(std::move(positions));
        mesh.setTexCoords(std::move(texCoords));
        mesh.setElements(std::move(elements));
        return std::move(mesh);
    } 

}

