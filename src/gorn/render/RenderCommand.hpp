#ifndef __gorn__RenderCommand__
#define __gorn__RenderCommand__

#include <gorn/base/Data.hpp>
#include <gorn/render/VertexDefinition.hpp>
#include <gorn/render/VertexArray.hpp>
#include <gorn/render/Material.hpp>
#include <glm/glm.hpp>

namespace gorn
{
    class VertexDefinition;
    class Program;

    struct RenderCommandBlock
    {
        Data data;
        size_t count;
        BasicType type;

        RenderCommandBlock();
        RenderCommandBlock(Data&& data, size_t count, BasicType type);
        RenderCommandBlock(const Data& data, size_t count, BasicType type);
    };

    enum class RenderCommandTransformMode
    {
        NoChange,
        PushLocal,
        PopLocal,
        SetGlobal,
        SetNone,
        PushCheckpoint,
        PopCheckpoint
    };

    enum class RenderCommandLifetime
    {
        Frame,
        Forever
    };

    class RenderCommand
    {
    public:
        typedef RenderCommandTransformMode TransformMode;
        typedef RenderCommandBlock Block;
        typedef std::map<std::string, Block> BlockMap;
        typedef RenderCommandLifetime Lifetime;
    private:
        BlockMap _attributes;
        Block _elements;
        std::shared_ptr<Material> _material;
        DrawMode _drawMode;
        glm::mat4 _transform;
        TransformMode _transformMode;
        Lifetime _lifetime;

    public:
        RenderCommand();
        RenderCommand& withMaterial(const std::shared_ptr<Material>& material);
        RenderCommand& withAttribute(const std::string& name,
            Data&& data, size_t count, BasicType type=BasicType::Float);
        RenderCommand& withAttribute(const std::string& name,
            const Data& data, size_t count, BasicType type=BasicType::Float);
        RenderCommand& withElements(Data&& data,
            BasicType type=BasicType::UnsignedInteger);
        RenderCommand& withElements(const Data& data,
            BasicType type=BasicType::UnsignedInteger);
        RenderCommand& withDrawMode(DrawMode mode);
        RenderCommand& withTransform(const glm::mat4& trans,
            TransformMode mode=TransformMode::PushLocal);
        RenderCommand& withTransformMode(TransformMode mode);
        RenderCommand& withLifetime(Lifetime lifetime);

        Block& getElements();
        const Block& getElements() const;
        bool hasElements() const;

        Block& getAttribute(const std::string& name);
        const Block& getAttribute(const std::string& name) const;
        bool hasAttribute(const std::string& name) const;
        BlockMap& getAttributes();
        const BlockMap& getAttributes() const;

        const std::shared_ptr<Material>& getMaterial() const;
        DrawMode getDrawMode() const;

        VertexDefinition getVertexDefinition(const Program& prog) const;
        size_t getVertexData(const VertexDefinition& vdef,
            Data& vertData, Data& elmData) const;

        const glm::mat4& getTransform() const;
        TransformMode getTransformMode() const;

        Lifetime getLifetime() const;

    };
}

#endif
