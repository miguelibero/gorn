#include <gorn/asset/Mesh.hpp>
#include <gorn/render/Kinds.hpp>
#include <gorn/render/RenderCommand.hpp>
#include <algorithm>

namespace gorn
{
    MeshElement::MeshElement(elm_t p, elm_t n, elm_t t):
    position(p), normal(n), texCoord(t)
    {
    }

    MeshElement& MeshElement::operator=(const MeshElement& other)
    {
        position = other.position;
        normal = other.normal;
        texCoord = other.texCoord;
        return *this;
    }

    bool MeshElement::operator==(const MeshElement& other) const
    {
        return position == other.position
            && normal == other.normal
            && texCoord == other.texCoord;
    }

    bool MeshElement::operator!=(const MeshElement& other) const
    {
        return !operator==(other);
    }

	Mesh::Mesh()
    {
    }

    void Mesh::setPositions(const Positions& positions)
    {
        _positions = positions;
    }

    void Mesh::setPositions(Positions&& positions)
    {
        _positions = std::move(positions);
    }

    void Mesh::setNormals(const Normals& normals)
    {
        _normals = normals;
    }

    void Mesh::setNormals(Normals&& normals)
    {
        _normals = std::move(normals);
    }

    void Mesh::setTexCoords(const TexCoords& coords)
    {
        _texCoords = coords;
    }

    void Mesh::setTexCoords(TexCoords&& coords)
    {
        _texCoords = std::move(coords);
    }

    void Mesh::setElements(const Elements& elms)
    {
        for(auto& elm : elms)
        {
            addElement(elm);
        }
    }

    void Mesh::setElements(Elements&& elms)
    {
        for(auto&& elm : elms)
        {
            addElement(std::move(elm));
        }
    }

    void Mesh::addPosition(const glm::vec3& pos)
    {
        _positions.push_back(pos);
    }

    void Mesh::addPosition(glm::vec3&& pos)
    {
        _positions.push_back(std::move(pos));
    }

    void Mesh::addNormal(const glm::vec3& normal)
    {
        _normals.push_back(normal);
    }

    void Mesh::addNormal(glm::vec3&& normal)
    {
        _normals.push_back(std::move(normal));
    }

    void Mesh::addTexCoord(const glm::vec2& coord)
    {
        _texCoords.push_back(coord);
    }

    void Mesh::addTexCoord(glm::vec2&& coord)
    {
        _texCoords.push_back(std::move(coord));
    }

    void Mesh::addElement(const Element& elm)
    {
        auto itr = std::find(_elements.begin(), _elements.end(), elm);
        if(itr == _elements.end())
        {
            itr = _elements.insert(itr, elm);
        }
        _indices.push_back(std::distance(_elements.begin(), itr));
    }

    void Mesh::addElement(Element&& elm)
    {
        auto itr = std::find(_elements.begin(), _elements.end(), elm);
        if(itr == _elements.end())
        {
            itr = _elements.insert(itr, std::move(elm));
        }
        _indices.push_back(std::distance(_elements.begin(), itr));
    }

    RenderCommand Mesh::render() const
    {
        Data posData;
        Data normData;
        Data texData;
        DataOutputStream posOut(posData);
        DataOutputStream normOut(normData);
        DataOutputStream texOut(texData);

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
        cmd.withElements(_indices, BasicType::UnsignedInteger);
        return cmd;
    }   

}

