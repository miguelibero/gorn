#include <gorn/asset/Mesh.hpp>
#include <gorn/base/Exception.hpp>
#include <gorn/render/RenderKinds.hpp>
#include <algorithm>
#include <buffer_writer.hpp>

namespace gorn
{
    const MeshElement::idx_t MeshElement::npos = -1;

    MeshElement::MeshElement(idx_t defval) NOEXCEPT:
    _defval(defval)
    {
    }

    MeshElement::idx_t MeshElement::getDefault() const NOEXCEPT
    {
        return _defval;
    }

    bool MeshElement::hasDefault() const NOEXCEPT
    {
        return _defval != npos;
    }

    void MeshElement::setDefault(idx_t defval) NOEXCEPT
    {
        _defval = defval;
    }

    MeshElement::idx_t MeshElement::get(const std::string& name) const
    {
        return _indices.at(name);
    }

    bool MeshElement::has(const std::string& name) const NOEXCEPT
    {
        auto itr = _indices.find(name);
        return itr != _indices.end();
    }

    void MeshElement::set(const std::string& name, idx_t idx) NOEXCEPT
    {
        _indices[name] = idx;
    }

    bool MeshElement::operator==(const MeshElement& other) const NOEXCEPT
    {
        return _indices.size() == other._indices.size()
            && _defval == other._defval
            && std::equal(_indices.begin(), _indices.end(),
                      other._indices.begin());
    }

    bool MeshElement::operator!=(const MeshElement& other) const NOEXCEPT
    {
        return !(*this==other);
    }

    void MeshElement::update(std::map<std::string, idx_t> indices)
    {
        for(auto itr = indices.begin(); itr != indices.end(); ++itr)
        {
            auto& n = itr->first;
            auto v = itr->second;
            if(has(n))
            {
                v += get(n);
            }
            else if(hasDefault())
            {
                v += getDefault();
            }
            set(n, v);
        }
        setDefault(npos);
    }

	Mesh::Mesh() NOEXCEPT:
    _drawMode(DrawMode::Triangles)
    {
    }

    void Mesh::setDrawMode(DrawMode mode) NOEXCEPT
    {
        _drawMode = mode;
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

    const Mesh::Elements& Mesh::getElements() const NOEXCEPT
    {
        return _elements;
    }

    DrawMode Mesh::getDrawMode() const NOEXCEPT
    {
        return _drawMode;
    }

    void Mesh::addElement(const Element& elm) NOEXCEPT
    {
        auto itr = std::find(_elements.begin(), _elements.end(), elm);
        if(itr == _elements.end())
        {
            itr = _elements.insert(itr, elm);
        }
        _indices.push_back((idx_t)std::distance(_elements.begin(), itr));
    }

    template<>
    const Mesh::Vertices<float>& Mesh::getVertices() const NOEXCEPT
    {
        return _vertices1;
    }

    template<>
    const Mesh::Vertices<glm::vec2>& Mesh::getVertices() const NOEXCEPT
    {
        return _vertices2;
    }

    template<>
    const Mesh::Vertices<glm::vec3>& Mesh::getVertices() const NOEXCEPT
    {
        return _vertices3;
    }


    template<>
    Mesh::Vertices<float>& Mesh::getVertices() NOEXCEPT
    {
        return _vertices1;
    }

    template<>
    Mesh::Vertices<glm::vec2>& Mesh::getVertices() NOEXCEPT
    {
        return _vertices2;
    }

    template<>
    Mesh::Vertices<glm::vec3>& Mesh::getVertices() NOEXCEPT
    {
        return _vertices3;
    }

    Mesh& Mesh::operator+=(const Mesh& other)
    {
        if(getDrawMode() != other.getDrawMode())
        {
            throw Exception("Only meshes with the same draw mode can be added");
        }

        std::map<std::string, size_t> sizes;
        other._vertices1.sizes(sizes, 0);
        other._vertices2.sizes(sizes, 0);
        other._vertices3.sizes(sizes, 0);
        _vertices1.sizes(sizes);
        _vertices2.sizes(sizes);
        _vertices3.sizes(sizes);

        _vertices1 += other._vertices1;
        _vertices2 += other._vertices2;
        _vertices3 += other._vertices3;

        auto elmSize = _elements.size();
        _elements.reserve(elmSize+other._elements.size());
        for(auto elm : other._elements)
        {
            elm.update(sizes);
            _elements.push_back(elm);
        }
        _indices.reserve(_indices.size()+other._indices.size());
        for(auto& idx : other._indices)
        {
            _indices.push_back((idx_t)(idx+elmSize));
        }

        return *this;
    }

    Mesh Mesh::operator+(const Mesh& other) const
    {
        Mesh sum(*this);
        sum += other;
        return sum;
    }
    
    Mesh& Mesh::operator+=(Mesh&& other)
    {
        if(getDrawMode() != other.getDrawMode())
        {
            throw Exception("Only meshes with the same draw mode can be added");
        }
        
        std::map<std::string, size_t> sizes;
        other._vertices1.sizes(sizes, 0);
        other._vertices2.sizes(sizes, 0);
        other._vertices3.sizes(sizes, 0);
        _vertices1.sizes(sizes);
        _vertices2.sizes(sizes);
        _vertices3.sizes(sizes);
        
        _vertices1 += std::move(other._vertices1);
        _vertices2 += std::move(other._vertices2);
        _vertices3 += std::move(other._vertices3);
        
        auto elmSize = _elements.size();
        _elements.reserve(elmSize+other._elements.size());
        for(auto elm : other._elements)
        {
            elm.update(sizes);
            _elements.push_back(elm);
        }
        _indices.reserve(_indices.size()+other._indices.size());
        for(auto& idx : other._indices)
        {
            _indices.push_back((idx_t)(idx+elmSize));
        }
        return *this;
    }
    
    Mesh Mesh::operator+(Mesh&& other) const
    {
        Mesh sum(*this);
        sum += std::move(other);
        return sum;
    }

    void Mesh::clear() NOEXCEPT
    {
        _vertices1.clear();
        _vertices2.clear();
        _vertices3.clear();
        _indices.clear();
        _elements.clear();
    }

    bool Mesh::empty() const NOEXCEPT
    {
        return _indices.empty();
    }

    RenderCommand Mesh::render() const NOEXCEPT
    {
        RenderCommand cmd;
        _vertices1.render(cmd, _elements);
        _vertices2.render(cmd, _elements);
        _vertices3.render(cmd, _elements);
        cmd.withElements(_indices);
        cmd.withDrawMode(_drawMode);
        return cmd;
    }

}

