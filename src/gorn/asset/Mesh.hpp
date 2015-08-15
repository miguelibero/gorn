#ifndef __gorn__Mesh__
#define __gorn__Mesh__

#include <vector>
#include <map>
#include <buffer.hpp>
#include <buffer_writer.hpp>
#include <glm/glm.hpp>
#include <gorn/base/Config.hpp>
#include <gorn/gl/Enums.hpp>
#include <gorn/render/RenderCommand.hpp>

namespace gorn
{
    class RenderCommand;

    class MeshElement
    {
    public:
        typedef size_t idx_t;
        static const idx_t npos;
    private:
        std::map<std::string, idx_t> _indices;
        idx_t _defval;
    public:
        MeshElement(idx_t defval = npos) NOEXCEPT;
        idx_t get(const std::string& name) const;
        void set(const std::string& name, idx_t idx) NOEXCEPT;
        bool has(const std::string& name) const NOEXCEPT;
        idx_t getDefault() const NOEXCEPT;
        bool hasDefault() const NOEXCEPT;
        void setDefault(idx_t defval) NOEXCEPT;
        void update(std::map<std::string, idx_t> indices);
        bool operator==(const MeshElement& other) const NOEXCEPT;
        bool operator!=(const MeshElement& other) const NOEXCEPT;
    };

    template<typename V>
	class MeshVertices
	{
    public:
        typedef MeshElement Element;
        typedef std::vector<Element> Elements;
    private:
        std::map<std::string, std::vector<V>> _data;
    public:

        void set(const std::string& name,
            const std::vector<V>& vtx) NOEXCEPT;
        void set(const std::string& name,
            std::vector<V>&& vtx) NOEXCEPT;
        const std::vector<V>& get(
            const std::string& name) const;
        bool has(const std::string& name) const NOEXCEPT;
        void add(const std::string& name, const V& vtx) NOEXCEPT;

        void sizes(std::map<std::string,size_t>& sizes) const NOEXCEPT;
        void sizes(std::map<std::string,size_t>& sizes, size_t value) const NOEXCEPT;

        MeshVertices<V>& operator+=(const MeshVertices<V>& other) NOEXCEPT;
        MeshVertices<V> operator+(const MeshVertices<V>& other) const NOEXCEPT;
        MeshVertices<V>& operator+=(MeshVertices<V>&& other) NOEXCEPT;
        MeshVertices<V> operator+(MeshVertices<V>&& other) const NOEXCEPT;
        void clear() NOEXCEPT;
        bool empty() const NOEXCEPT;

        void render(RenderCommand& cmd, const Elements& elms) const NOEXCEPT;
    };
    
    template<typename V>
    void MeshVertices<V>::set(const std::string& name,
        const std::vector<V>& vtx) NOEXCEPT
    {
        _data[name] = vtx;
    }

    template<typename V>
    void MeshVertices<V>::set(const std::string& name,
        std::vector<V>&& vtx) NOEXCEPT
    {
        _data[name] = std::move(vtx);
    }

    template<typename V>
    const std::vector<V>& MeshVertices<V>::get(
        const std::string& name) const
    {
        return _data.at(name);
    }

    template<typename V>
    bool MeshVertices<V>::has(const std::string& name) const NOEXCEPT
    {
        return _data.find(name) != _data.end();
    }

    template<typename V>
    void MeshVertices<V>::add(const std::string& name, const V& vtx) NOEXCEPT
    {
        _data[name].push_back(vtx);
    }

    template<typename V>
    void MeshVertices<V>::sizes(
        std::map<std::string,size_t>& sizes) const NOEXCEPT
    {
        for(auto itr = _data.begin();
            itr != _data.end(); ++itr)
        {
            sizes[itr->first] = itr->second.size();
        }
    }

    template<typename V>
    void MeshVertices<V>::sizes(
        std::map<std::string,size_t>& sizes, size_t value) const NOEXCEPT
    {
        for(auto itr = _data.begin();
            itr != _data.end(); ++itr)
        {
            sizes[itr->first] = value;
        }
    }

    template<typename V>
    MeshVertices<V>& MeshVertices<V>::operator+=(
        const MeshVertices<V>& other) NOEXCEPT
    {
        for(auto itr = other._data.begin();
            itr != other._data.end(); ++itr)
        {
            auto& data = _data[itr->first];
            data.reserve(data.size()+itr->second.size());
            data.insert(data.end(), itr->second.begin(), itr->second.end());
        }
        return *this;
    }

    template<typename V>
    MeshVertices<V> MeshVertices<V>::operator+(
        const MeshVertices<V>& other) const NOEXCEPT
    {
        MeshVertices sum(*this);
        sum += other;
        return sum;
    }
    
    template<typename V>
    MeshVertices<V>& MeshVertices<V>::operator+=(
        MeshVertices<V>&& other) NOEXCEPT
    {
        for(auto itr = other._data.begin();
            itr != other._data.end(); ++itr)
        {
            auto& data = _data[itr->first];
            data.reserve(data.size()+itr->second.size());
            data.insert(data.end(),
                std::make_move_iterator(itr->second.begin()),
                std::make_move_iterator(itr->second.end()));
        }
        return *this;
    }
    
    template<typename V>
    MeshVertices<V> MeshVertices<V>::operator+(
        MeshVertices<V>&& other) const NOEXCEPT
    {
        MeshVertices sum(*this);
        sum += std::move(other);
        return sum;
    }

    template<typename V>
    void MeshVertices<V>::clear() NOEXCEPT
    {
        _data.clear();
    }

    template<typename V>    
    bool MeshVertices<V>::empty() const NOEXCEPT
    {
        return _data.empty();
    }

    template<typename V>
    void MeshVertices<V>::render(RenderCommand& cmd,
        const Elements& elms) const NOEXCEPT
    {
        for(auto itr = _data.begin(); itr != _data.end(); ++itr)
        {
            buffer data;
            data.capacity(elms.size()*sizeof(V));
            buffer_writer out(data);
            auto& n = itr->first;
            auto& v = itr->second;
            for(const Element& elm : elms)
            {
                if(elm.has(n))
                {
                    auto& p = v.at(elm.get(n));
                    out.write(&p, sizeof(V));
                }
                else if(elm.hasDefault())
                {
                    auto& p = v.at(elm.getDefault());
                    out.write(&p, sizeof(V));
                }
            }
            cmd.withAttribute(n, std::move(data),
                sizeof(V)/sizeof(float), BasicType::Float);
        }
    }

	class Mesh
	{
    public:
        typedef unsigned idx_t;
        typedef MeshElement Element;
        typedef std::vector<Element> Elements;
        typedef std::vector<idx_t> Indices;
        template<typename V> using Vertices = MeshVertices<V>;
	private:
        Vertices<glm::vec3> _vertices3;
        Vertices<glm::vec2> _vertices2;
        Vertices<float> _vertices1;
        Elements _elements;
        Indices _indices;
        DrawMode _drawMode;

	public:
		Mesh() NOEXCEPT;

        Mesh& operator+=(const Mesh& other);
        Mesh operator+(const Mesh& other) const;
        Mesh& operator+=(Mesh&& other);
        Mesh operator+(Mesh&& other) const;
        void clear() NOEXCEPT;
        bool empty() const NOEXCEPT;

        const Elements& getElements() const NOEXCEPT;
        void setElements(const Elements& elms) NOEXCEPT;
        void setElements(Elements&& elms) NOEXCEPT;
        void addElement(const Element& elm) NOEXCEPT;

        template<typename V>
        const Mesh::Vertices<V>& getVertices() const NOEXCEPT;
        template<typename V>
        Mesh::Vertices<V>& getVertices() NOEXCEPT;

        template<typename V>
        void setVertices(const std::string& name,
            const std::vector<V>& vtx) NOEXCEPT;
        template<typename V>
        void setVertices(const std::string& name,
            std::vector<V>&& vtx) NOEXCEPT;
        template<typename V>
        const std::vector<V>& getVertices(
            const std::string& name) const;
        template<typename V>
        bool hasVertices(const std::string& name) const NOEXCEPT;
        template<typename V>
        void addVertex(const std::string& name, const V& vtx) NOEXCEPT;

        void setDrawMode(DrawMode mode) NOEXCEPT;
        DrawMode getDrawMode() const NOEXCEPT;

	    RenderCommand render() const NOEXCEPT;
	};

    template<>
    const Mesh::Vertices<float>& Mesh::getVertices() const NOEXCEPT;
    template<>
    const Mesh::Vertices<glm::vec2>& Mesh::getVertices() const NOEXCEPT;
    template<>
    const Mesh::Vertices<glm::vec3>& Mesh::getVertices() const NOEXCEPT;
    template<>
    Mesh::Vertices<float>& Mesh::getVertices() NOEXCEPT;
    template<>
    Mesh::Vertices<glm::vec2>& Mesh::getVertices() NOEXCEPT;
    template<>
    Mesh::Vertices<glm::vec3>& Mesh::getVertices() NOEXCEPT;

    template<typename V>
    void Mesh::setVertices(const std::string& name,
        const std::vector<V>& vtx) NOEXCEPT
    {
        return getVertices<V>().set(name, vtx);
    }

    template<typename V>
    void Mesh::setVertices(const std::string& name,
        std::vector<V>&& vtx) NOEXCEPT
    {
        return getVertices<V>().set(name, std::move(vtx));
    }

    template<typename V>
    const std::vector<V>& Mesh::getVertices(
        const std::string& name) const
    {
        return getVertices<V>().get(name);
    }

    template<typename V>
    bool Mesh::hasVertices(const std::string& name) const NOEXCEPT
    {
        return getVertices<V>().has(name);
    }

    template<typename V>
    void Mesh::addVertex(const std::string& name, const V& vtx) NOEXCEPT
    {
        return getVertices<V>().add(name, vtx);
    }

}

#endif
