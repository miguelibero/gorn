#ifndef __gorn__Mesh__
#define __gorn__Mesh__

#include <vector>
#include <glm/glm.hpp>
#include <gorn/base/Config.hpp>

namespace gorn
{
    class RenderCommand;

    struct MeshElement
    {
        typedef size_t elm_t;
        elm_t position;
        elm_t normal;
        elm_t texCoord;

        MeshElement(elm_t p=0, elm_t n=0, elm_t t=0) NOEXCEPT;

        MeshElement& operator=(const MeshElement& other) NOEXCEPT;
        bool operator==(const MeshElement& other) const NOEXCEPT;
        bool operator!=(const MeshElement& other) const NOEXCEPT;
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
		Mesh() NOEXCEPT;

        void setPositions(const Positions& positions) NOEXCEPT;
        void setPositions(Positions&& positions) NOEXCEPT;
        void setNormals(const Normals& normals) NOEXCEPT;
        void setNormals(Normals&& normals) NOEXCEPT;
        void setTexCoords(const TexCoords& coords) NOEXCEPT;
        void setTexCoords(TexCoords&& coords) NOEXCEPT;
        void setElements(const Elements& elms) NOEXCEPT;
        void setElements(Elements&& elms) NOEXCEPT;

        void addPosition(const glm::vec3& pos) NOEXCEPT;
        void addPosition(glm::vec3&& pos) NOEXCEPT;
        void addNormal(const glm::vec3& normal) NOEXCEPT;
        void addNormal(glm::vec3&& normal) NOEXCEPT;
        void addTexCoord(const glm::vec2& coord) NOEXCEPT;
        void addTexCoord(glm::vec2&& coord) NOEXCEPT;
        void addElement(const Element& elm) NOEXCEPT;
        void addElement(Element&& elm) NOEXCEPT;

	    RenderCommand render() const;
	};
}

#endif
