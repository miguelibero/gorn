#ifndef __gorn__Mesh__
#define __gorn__Mesh__

#include <vector>
#include <glm/glm.hpp>

namespace gorn
{
    
    class RenderCommand;

    struct MeshElement
    {
        typedef size_t elm_t;
        elm_t position;
        elm_t normal;
        elm_t texCoord;

        MeshElement(elm_t p=0, elm_t n=0, elm_t t=0);

        MeshElement& operator=(const MeshElement& other);
        bool operator==(const MeshElement& other) const;
        bool operator!=(const MeshElement& other) const;
    };

	class Mesh
	{
    public:
        typedef unsigned idx_t;
        typedef std::vector<glm::vec3> Positions;
        typedef std::vector<glm::vec3> Normals;
        typedef std::vector<glm::vec2> TexCoords;
        typedef MeshElement Element;
        typedef std::vector<Element> Elements;
        typedef std::vector<idx_t> Indices;
	private:
        Positions _positions;
        Normals _normals;
        TexCoords _texCoords;
        Elements _elements;
        Indices _indices;

	public:
		Mesh();

        void setPositions(const Positions& positions);
        void setPositions(Positions&& positions);
        void setNormals(const Normals& normals);
        void setNormals(Normals&& normals);
        void setTexCoords(const TexCoords& coords);
        void setTexCoords(TexCoords&& coords);
        void setElements(const Elements& elms);
        void setElements(Elements&& elms);

        void addPosition(const glm::vec3& pos);
        void addPosition(glm::vec3&& pos);
        void addNormal(const glm::vec3& normal);
        void addNormal(glm::vec3&& normal);
        void addTexCoord(const glm::vec2& coord);
        void addTexCoord(glm::vec2&& coord);
        void addElement(const Element& elm);
        void addElement(Element&& elm);

	    RenderCommand render() const;
	};
}

#endif
