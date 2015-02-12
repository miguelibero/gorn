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
        typedef RenderCommandLifetime Lifetime;
    private:
        std::map<std::string, Block> _attributes;
        std::map<std::string, Block> _elements;
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
        RenderCommand& withElements(const std::string& name, Data&& data,
            BasicType type=BasicType::UnsignedInteger);
        RenderCommand& withElements(const std::string& name, const Data& data, 
            BasicType type=BasicType::UnsignedInteger);
        RenderCommand& withDrawMode(DrawMode mode);
        RenderCommand& withTransform(const glm::mat4& trans,
            TransformMode mode=TransformMode::PushLocal);
        RenderCommand& withTransformMode(TransformMode mode);
        RenderCommand& withLifetime(Lifetime lifetime);

        Block& getElements(const std::string& name);
        const Block& getElements(const std::string& name) const;
        bool hasElements(const std::string& name) const;
        std::map<std::string, Block>& getElements();
        const std::map<std::string, Block>& getElements() const;

        Block& getAttribute(const std::string& name);
        const Block& getAttribute(const std::string& name) const;
        bool hasAttribute(const std::string& name) const;
        std::map<std::string, Block>& getAttributes();
        const std::map<std::string, Block>& getAttributes() const;

        const std::shared_ptr<Material>& getMaterial() const;
        DrawMode getDrawMode() const;

        VertexDefinition generateVertexDefinition() const;
        size_t getVertexData(const VertexDefinition& vdef,
            Data& vertData, Data& elmData) const;

        const glm::mat4& getTransform() const;
        TransformMode getTransformMode() const;

        Lifetime getLifetime() const;

    };
}

#endif
