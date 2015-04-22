#include <gorn/asset/Mesh.hpp>
#include <gorn/base/Exception.hpp>
#include <gorn/render/RenderKinds.hpp>
#include <gorn/render/RenderCommand.hpp>
#include <algorithm>
#include <buffer_writer.hpp>

namespace gorn
{
    MeshElement::MeshElement(elm_t p, elm_t n, elm_t t) NOEXCEPT:
    position(p), normal(n), texCoord(t)
    {
    }

    MeshElement& MeshElement::operator=(const MeshElement& other) NOEXCEPT
    {
        position = other.position;
        normal = other.normal;
        texCoord = other.texCoord;
        return *this;
    }

    bool MeshElement::operator==(const MeshElement& other) const NOEXCEPT
    {
        return position == other.position
            && normal == other.normal
            && texCoord == other.texCoord;
    }

    bool MeshElement::operator!=(const MeshElement& other) const NOEXCEPT
    {
        return !operator==(other);
    }

	Mesh::Mesh() NOEXCEPT:
    _drawMode(DrawMode::Triangles)
    {
    }

    void Mesh::setDrawMode(DrawMode mode) NOEXCEPT
    {
        _drawMode = mode;
        if(!empty())
        {
            throw Exception("Mesh is not empty");
        }
    }

    void Mesh::setPositions(const Positions& positions) NOEXCEPT
    {
        _positions = positions;
    }

    void Mesh::setPositions(Positions&& positions) NOEXCEPT
    {
        _positions = std::move(positions);
    }

    void Mesh::setNormals(const Normals& normals) NOEXCEPT
    {
        _normals = normals;
    }

    void Mesh::setNormals(Normals&& normals) NOEXCEPT
    {
        _normals = std::move(normals);
    }

    void Mesh::setTexCoords(const TexCoords& coords) NOEXCEPT
    {
        _texCoords = coords;
    }

    void Mesh::setTexCoords(TexCoords&& coords) NOEXCEPT
    {
        _texCoords = std::move(coords);
    }

    void Mesh::setElements(const Elements& elms) NOEXCEPT
    {
        for(auto& elm : elms)
        {
            addElement(elm);
        }
    }

    void Mesh::setElements(Elements&& elms) NOEXCEPT
    {
        for(auto&& elm : elms)
        {
            addElement(std::move(elm));
        }
    }

    const Mesh::Positions& Mesh::getPositions() const NOEXCEPT
    {
        return _positions;
    }

    const Mesh::Normals& Mesh::getNormals() const NOEXCEPT
    {
        return _normals;
    }

    const Mesh::TexCoords& Mesh::getTexCoords() const NOEXCEPT
    {
        return _texCoords;
    }

    const Mesh::Elements& Mesh::getElements() const NOEXCEPT
    {
        return _elements;
    }

    DrawMode Mesh::getDrawMode() const NOEXCEPT
    {
        return _drawMode;
    }

    void Mesh::addPosition(const glm::vec3& pos) NOEXCEPT
    {
        _positions.push_back(pos);
    }

    void Mesh::addPosition(glm::vec3&& pos) NOEXCEPT
    {
        _positions.push_back(std::move(pos));
    }

    void Mesh::addNormal(const glm::vec3& normal) NOEXCEPT
    {
        _normals.push_back(normal);
    }

    void Mesh::addNormal(glm::vec3&& normal) NOEXCEPT
    {
        _normals.push_back(std::move(normal));
    }

    void Mesh::addTexCoord(const glm::vec2& coord) NOEXCEPT
    {
        _texCoords.push_back(coord);
    }

    void Mesh::addTexCoord(glm::vec2&& coord) NOEXCEPT
    {
        _texCoords.push_back(std::move(coord));
    }

    void Mesh::addElement(const Element& elm) NOEXCEPT
    {
        auto itr = std::find(_elements.begin(), _elements.end(), elm);
        if(itr == _elements.end())
        {
            itr = _elements.insert(itr, elm);
        }
        _indices.push_back(std::distance(_elements.begin(), itr));
    }

    void Mesh::addElement(Element&& elm) NOEXCEPT
    {
        auto itr = std::find(_elements.begin(), _elements.end(), elm);
        if(itr == _elements.end())
        {
            itr = _elements.insert(itr, std::move(elm));
        }
        _indices.push_back(std::distance(_elements.begin(), itr));
    }

    Mesh& Mesh::operator+=(const Mesh& other)
    {
        if(getDrawMode() != other.getDrawMode())
        {
            throw Exception("Only meshes with the same draw mode can be added");
        }

        auto posSize = _positions.size();
        auto normSize = _normals.size();
        auto texSize = _texCoords.size();
        for(auto elm : other._elements)
        {
            elm.position += posSize;
            elm.normal += normSize;
            elm.texCoord += texSize;
            addElement(elm);
        }
        _positions.insert(_positions.end(), other._positions.begin(),
            other._positions.end());
        _normals.insert(_normals.end(), other._normals.begin(),
            other._normals.end());
        _texCoords.insert(_texCoords.end(), other._texCoords.begin(),
            other._texCoords.end());
        return *this;
    }

    Mesh Mesh::operator+(const Mesh& other) const
    {
        Mesh sum(*this);
        sum += other;
        return sum;
    }

    void Mesh::clear()
    {
        _positions.clear();
        _normals.clear();
        _texCoords.clear();
        _indices.clear();
        _elements.clear();
    }

    bool Mesh::empty() const
    {
        return _elements.empty();
    }

    RenderCommand Mesh::render() const
    {
        buffer posData;
        buffer normData;
        buffer texData;
        buffer_writer posOut(posData);
        buffer_writer normOut(normData);
        buffer_writer texOut(texData);

        for(const Element& elm : _elements)
        {
            if(_positions.size() > elm.position)
            {
                auto& p = _positions.at(elm.position);
                posOut.write({p.x, p.y, p.z});
            }
            if(_normals.size() > elm.normal)
            {
                auto& n = _normals.at(elm.normal);
                normOut.write({n.x, n.y, n.z});
            }
            if(_texCoords.size() > elm.texCoord)
            {
                auto& t = _texCoords.at(elm.texCoord);
                texOut.write({t.x, t.y});
            }
        }

        RenderCommand cmd;
        cmd.withAttribute(AttributeKind::Position,
            std::move(posData), 3, BasicType::Float);
        cmd.withAttribute(AttributeKind::Normal,
            std::move(normData), 3, BasicType::Float);
        cmd.withAttribute(AttributeKind::TexCoords,
            std::move(texData), 2, BasicType::Float);
        cmd.withElements(_indices);
        cmd.withDrawMode(_drawMode);
        return cmd;
    }

}

