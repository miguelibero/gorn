#ifndef __gorn__Mesh__
#define __gorn__Mesh__

#include <vector>
#include <unordered_map>
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
		typedef AttributeKind Kind;
        typedef RenderCommand::elm_t idx_t;
        typedef std::unordered_map<Kind, idx_t> IndicesMap;
        static const idx_t npos;
    private:
        IndicesMap _indices;
        idx_t _defval;
    public:
        MeshElement(idx_t defval = npos) NOEXCEPT;
        idx_t get(const Kind& kind) const;
        void set(const Kind& kind, idx_t idx) NOEXCEPT;
        bool has(const Kind& kind) const NOEXCEPT;
        idx_t getDefault() const NOEXCEPT;
        bool hasDefault() const NOEXCEPT;
        void setDefault(idx_t defval) NOEXCEPT;
        void update(const IndicesMap& indices);
        bool operator==(const MeshElement& other) const NOEXCEPT;
        bool operator!=(const MeshElement& other) const NOEXCEPT;

		MeshElement& operator+=(idx_t idx);
		MeshElement operator+(idx_t idx) const;
		MeshElement& operator-=(idx_t idx);
		MeshElement operator-(idx_t idx) const;
    };

    template<typename V>
    class MeshVertices
    {
    public:
        typedef MeshElement Element;
        typedef std::vector<Element> Elements;
        typedef MeshElement::IndicesMap IndicesMap;
        typedef MeshElement::idx_t idx_t;
		typedef AttributeKind Kind;
    private:
        std::unordered_map<Kind, std::vector<V>> _data;
    public:

        void set(const Kind& kind,
            const std::vector<V>& vtx) NOEXCEPT;
        void set(const Kind& kind,
            std::vector<V>&& vtx) NOEXCEPT;
        const std::vector<V>& get(
			const Kind& kind) const;
        bool has(const Kind& kind) const NOEXCEPT;
        void add(const Kind& kind, const V& vtx) NOEXCEPT;

        void sizes(IndicesMap& sizes) const NOEXCEPT;
        void sizes(IndicesMap& sizes, idx_t value) const NOEXCEPT;

        MeshVertices<V>& operator+=(const MeshVertices<V>& other) NOEXCEPT;
        MeshVertices<V> operator+(const MeshVertices<V>& other) const NOEXCEPT;
        MeshVertices<V>& operator+=(MeshVertices<V>&& other) NOEXCEPT;
        MeshVertices<V> operator+(MeshVertices<V>&& other) const NOEXCEPT;
        void clear() NOEXCEPT;
        bool empty() const NOEXCEPT;

        void render(RenderCommand& cmd, const Elements& elms) const NOEXCEPT;
		void reserve(const Kind& kind, size_t size);
    };

    template<typename V>
    void MeshVertices<V>::set(const Kind& kind,
        const std::vector<V>& vtx) NOEXCEPT
    {
        _data[kind] = vtx;
    }

    template<typename V>
    void MeshVertices<V>::set(const Kind& kind,
        std::vector<V>&& vtx) NOEXCEPT
    {
        _data[kind] = std::move(vtx);
    }

    template<typename V>
    const std::vector<V>& MeshVertices<V>::get(
		const Kind& kind) const
    {
        return _data.at(kind);
    }

    template<typename V>
    bool MeshVertices<V>::has(const Kind& kind) const NOEXCEPT
    {
        return _data.find(kind) != _data.end();
    }

    template<typename V>
    void MeshVertices<V>::add(const Kind& kind, const V& vtx) NOEXCEPT
    {
        _data[kind].push_back(vtx);
    }

	template<typename V>
	void MeshVertices<V>::reserve(const Kind& kind, size_t size)
	{
		_data[kind].reserve(size);
	}

    template<typename V>
    void MeshVertices<V>::sizes(
        IndicesMap& sizes) const NOEXCEPT
    {
        for(auto itr = _data.begin();
            itr != _data.end(); ++itr)
        {
            sizes[itr->first] = (idx_t)itr->second.size();
        }
    }

    template<typename V>
    void MeshVertices<V>::sizes(
        IndicesMap& sizes, idx_t value) const NOEXCEPT
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
                if(elm.has(n) && v.size() > elm.get(n))
                {
                    auto& p = v.at(elm.get(n));
                    out.write(&p, sizeof(V));
                }
                else if(elm.hasDefault() && v.size() > elm.getDefault())
                {
                    auto& p = v.at(elm.getDefault());
                    out.write(&p, sizeof(V));
                }
            }
            cmd.withAttribute(n, std::move(data), sizeof(V) / sizeof(float));
        }
    }

    class Mesh
    {
    public:
        typedef MeshElement::idx_t idx_t;
        typedef MeshElement Element;
        typedef MeshElement::IndicesMap IndicesMap;
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
        Elements& getElements() NOEXCEPT;
        void setElements(const Elements& elms) NOEXCEPT;
        void setElements(Elements&& elms) NOEXCEPT;

        const Indices& getIndices() const NOEXCEPT;
        Indices& getIndices() NOEXCEPT;
        void setIndices(const Indices& idxs) NOEXCEPT;
        void setIndices(Indices&& idxs) NOEXCEPT;

        void addFace(const std::vector<Element>& face) NOEXCEPT;

        template<typename V>
        const Mesh::Vertices<V>& getVertices() const NOEXCEPT;
        template<typename V>
        Mesh::Vertices<V>& getVertices() NOEXCEPT;

        template<typename V>
        void setVertices(const AttributeKind& kind,
            const std::vector<V>& vtx) NOEXCEPT;
        template<typename V>
        void setVertices(const AttributeKind& kind,
            std::vector<V>&& vtx) NOEXCEPT;
        template<typename V>
        const std::vector<V>& getVertices(
			const AttributeKind& kind) const;
        template<typename V>
        bool hasVertices(const AttributeKind& kind) const NOEXCEPT;
		template<typename V>
		void reserveVertices(const AttributeKind& kind, size_t size) NOEXCEPT;
        template<typename V>
        void addVertex(const AttributeKind& kind, const V& vtx) NOEXCEPT;

        void setDrawMode(DrawMode mode) NOEXCEPT;
        DrawMode getDrawMode() const NOEXCEPT;

        RenderCommand render() const NOEXCEPT;
		Mesh getNormalsMesh() const NOEXCEPT;
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
    void Mesh::setVertices(const AttributeKind& kind,
        const std::vector<V>& vtx) NOEXCEPT
    {
        return getVertices<V>().set(kind, vtx);
    }

    template<typename V>
    void Mesh::setVertices(const AttributeKind& kind,
        std::vector<V>&& vtx) NOEXCEPT
    {
        return getVertices<V>().set(kind, std::move(vtx));
    }

    template<typename V>
    const std::vector<V>& Mesh::getVertices(
		const AttributeKind& kind) const
    {
        return getVertices<V>().get(kind);
    }

    template<typename V>
    bool Mesh::hasVertices(const AttributeKind& kind) const NOEXCEPT
    {
        return getVertices<V>().has(kind);
    }

	template<typename V>
	void Mesh::reserveVertices(const AttributeKind& kind, size_t size) NOEXCEPT
	{
		getVertices<V>().reserve(kind, size);
	}

    template<typename V>
    void Mesh::addVertex(const AttributeKind& kind, const V& vtx) NOEXCEPT
    {
        return getVertices<V>().add(kind, vtx);
    }

}

#endif
