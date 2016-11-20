#ifndef __gorn__RenderCommand__
#define __gorn__RenderCommand__

#include <buffer.hpp>
#include <gorn/gl/VertexDefinition.hpp>
#include <gorn/gl/Material.hpp>
#include <gorn/gl/Stencil.hpp>
#include <gorn/gl/ClearAction.hpp>
#include <gorn/gl/Capabilities.hpp>
#include <gorn/gl/BlendMode.hpp>
#include <gorn/base/Rect.hpp>
#include <glm/glm.hpp>
#include <functional>


class buffer_writer;

namespace gorn
{
    class VertexDefinition;
    class Program;

    enum class RenderTransformStackAction
    {
        None,
        PushLocal,
        PopLocal,
        SetGlobal,
        PushCheckpoint,
        PopCheckpoint
    };

    enum class RenderStackAction
    {
        None,
        Push,
        Pop
    };

	struct RenderCommandAttribute
	{
		buffer data;
		size_t count;
		bool repeat;
	};

    class RenderCommand
    {
    public:
		typedef RenderCommandAttribute Attribute;
        typedef RenderTransformStackAction TransformStackAction;
        typedef RenderStackAction StackAction;
        typedef std::unordered_map<AttributeKind, Attribute> AttributeMap;
        typedef unsigned int elm_t;
        typedef std::vector<elm_t> Elements;
		typedef std::vector<int> Layers;

    private:
		UniformValueMap _uniforms;
        AttributeMap _attributes;
        Elements _elements;
        std::shared_ptr<Material> _material;
        DrawMode _drawMode;
        glm::mat4 _transform;
        TransformStackAction _transformMode;
        Rect _boundingBox;
        Stencil _stencil;
        ClearAction _clearAction;
        Capabilities _capabilities;
		BlendMode _blendMode;
		Layers _layers;
		StackAction _boundingStackAction;
		StackAction _layersStackAction;
		StackAction _blendStackAction;
		StackAction _stencilStackAction;
		StackAction _capabilitiesStackAction;
    public:
        RenderCommand();
		RenderCommand& withUniformValue(const std::string& name, const UniformValue& value);
        RenderCommand& withMaterial(const std::shared_ptr<Material>& material);
        RenderCommand& withAttribute(const AttributeKind& kind,
            buffer&& data, size_t count = 0);
        RenderCommand& withAttribute(const AttributeKind& kind,
            const buffer& data, size_t count = 0);

		RenderCommand& withRepeatAttribute(const AttributeKind& kind,
			buffer&& data);
		RenderCommand& withRepeatAttribute(const AttributeKind& kind,
			const buffer& data);

        RenderCommand& withElements(Elements&& elms);
        RenderCommand& withElements(const Elements& elms);
        RenderCommand& withDrawMode(DrawMode mode);
        RenderCommand& withTransform(const glm::mat4& trans,
            TransformStackAction action=TransformStackAction::PushLocal);
        RenderCommand& withTransformAction(TransformStackAction mode);

        RenderCommand& withBounding(const Rect& rect);
        RenderCommand& withBoundingAction(StackAction action);

		RenderCommand& withClearAction(const ClearAction& clear);

        RenderCommand& withStencil(const Stencil& stencil);
		RenderCommand& withStencilAction(StackAction action);

        RenderCommand& withCapabilities(const Capabilities& caps);
		RenderCommand& withCapabilitiesAction(StackAction action);

		RenderCommand& withBlendMode(const BlendMode& mode);
		RenderCommand& withBlendModeAction(StackAction action);

		RenderCommand& withLayer(int layer);
		RenderCommand& withLayers(const Layers& layers);
		RenderCommand& withLayersAction(StackAction action);

		UniformValueMap& getUniformValues();
		const UniformValueMap& getUniformValues() const;

        Elements& getElements();
        const Elements& getElements() const;
        bool hasElements() const;

        const Attribute& getAttribute(const std::string& name) const;
        bool hasAttribute(const std::string& name) const;
        const AttributeMap& getAttributes() const;

        const std::shared_ptr<Material>& getMaterial() const;
        DrawMode getDrawMode() const;

        void dumpVertexData(buffer& data, Elements& elms,
            const glm::mat4& transform=glm::mat4(1.0f)) const;

        const glm::mat4& getTransform() const;
        TransformStackAction getTransformMode() const;

        StackAction getBoundingStackAction() const;
        const Rect& getBoundingBox() const;

		const ClearAction& getClearAction() const;

        const Stencil& getStencil() const;
		StackAction getStencilStackAction() const;
        
        const Capabilities& getCapabilities() const;
		StackAction getCapabilitiesStackAction() const;

		const BlendMode& getBlendMode() const;
		StackAction getBlendStackAction() const;

		const Layers& getLayers() const;
		StackAction getLayersStackAction() const;

    };
}

#endif
