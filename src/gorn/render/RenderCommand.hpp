#ifndef __gorn__RenderCommand__
#define __gorn__RenderCommand__

#include <buffer.hpp>
#include <gorn/render/VertexDefinition.hpp>
#include <gorn/render/VertexArray.hpp>
#include <gorn/render/Material.hpp>
#include <glm/glm.hpp>


class buffer_writer;

namespace gorn
{
    class VertexDefinition;
    class Program;

    struct RenderCommandAttribute
    {
        typedef AttributeDefinition Definition;
        buffer data;
        size_t count;
        BasicType type;

        RenderCommandAttribute();
        RenderCommandAttribute(buffer&& data, size_t count, BasicType type);
        RenderCommandAttribute(const buffer& data, size_t count, BasicType type);

        size_t write(buffer_writer& out, const Definition& def, size_t pos) const;
        size_t write(buffer_writer& out, const Definition& def, size_t pos,
            const glm::mat4& transform) const;
    };

    enum class RenderCommandTransformMode
    {
        NoChange,
        PushLocal,
        PopLocal,
        SetGlobal,
        PushCheckpoint,
        PopCheckpoint
    };

    class RenderCommand
    {
    public:
        typedef RenderCommandTransformMode TransformMode;
        typedef RenderCommandAttribute Attribute;
        typedef std::map<std::string, Attribute> AttributeMap;
        typedef unsigned elm_t;
        typedef std::vector<elm_t> Elements;
    private:
        AttributeMap _attributes;
        Elements _elements;
        std::shared_ptr<Material> _material;
        DrawMode _drawMode;
        glm::mat4 _transform;
        TransformMode _transformMode;

    public:
        RenderCommand();
        RenderCommand& withMaterial(const std::shared_ptr<Material>& material);
        RenderCommand& withAttribute(const std::string& name,
            buffer&& data, size_t count, BasicType type=BasicType::Float);
        RenderCommand& withAttribute(const std::string& name,
            const buffer& data, size_t count, BasicType type=BasicType::Float);
        RenderCommand& withElements(Elements&& elms);
        RenderCommand& withElements(const Elements& elms);
        RenderCommand& withDrawMode(DrawMode mode);
        RenderCommand& withTransform(const glm::mat4& trans,
            TransformMode mode=TransformMode::PushLocal);
        RenderCommand& withTransformMode(TransformMode mode);

        Elements& getElements();
        const Elements& getElements() const;
        bool hasElements() const;

        Attribute& getAttribute(const std::string& name);
        const Attribute& getAttribute(const std::string& name) const;
        bool hasAttribute(const std::string& name) const;
        AttributeMap& getAttributes();
        const AttributeMap& getAttributes() const;

        const std::shared_ptr<Material>& getMaterial() const;
        DrawMode getDrawMode() const;

        VertexDefinition getVertexDefinition(const Program& prog) const;
        void getVertexData(buffer& data, Elements& elms,
            const VertexDefinition& vdef,            
            const glm::mat4& transform=glm::mat4(1.0f)) const;

        const glm::mat4& getTransform() const;
        TransformMode getTransformMode() const;

    };
}

#endif
