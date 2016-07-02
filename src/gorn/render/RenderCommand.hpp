#ifndef __gorn__RenderCommand__
#define __gorn__RenderCommand__

#include <buffer.hpp>
#include <gorn/gl/VertexDefinition.hpp>
#include <gorn/gl/Material.hpp>
#include <gorn/gl/Stencil.hpp>
#include <gorn/gl/ClearAction.hpp>
#include <gorn/gl/StateChange.hpp>
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
        typedef std::map<std::string, Attribute> AttributeMap;
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
        StateChange _stateChange;
		BlendMode _blendMode;
		Layers _layers;
		StackAction _boundingStackAction;
		StackAction _layersStackAction;
		StackAction _blendStackAction;
    public:
        RenderCommand();
		RenderCommand& withUniformValue(const std::string& name, const UniformValue& value);
        RenderCommand& withMaterial(const std::shared_ptr<Material>& material);
        RenderCommand& withAttribute(const std::string& name,
            buffer&& data, size_t count = 0);
        RenderCommand& withAttribute(const std::string& name,
            const buffer& data, size_t count = 0);
		RenderCommand& withRepeatAttribute(const std::string& name,
			buffer&& data);
		RenderCommand& withRepeatAttribute(const std::string& name,
			const buffer& data);

        RenderCommand& withElements(Elements&& elms);
        RenderCommand& withElements(const Elements& elms);
        RenderCommand& withDrawMode(DrawMode mode);
        RenderCommand& withTransform(const glm::mat4& trans,
            TransformStackAction action=TransformStackAction::PushLocal);
        RenderCommand& withTransformAction(TransformStackAction mode);

        RenderCommand& withBounding(const Rect& rect);
        RenderCommand& withBoundingAction(StackAction action);

        RenderCommand& withStencil(const Stencil& stencil);
        RenderCommand& withClearAction(const ClearAction& clear);
        RenderCommand& withStateChange(const StateChange& change);

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

        const Stencil& getStencil() const;
        const ClearAction& getClearAction() const;
        const StateChange& getStateChange() const;
		const BlendMode& getBlendMode() const;
		StackAction getBlendStackAction() const;

		const Layers& getLayers() const;
		StackAction getLayersStackAction() const;

    };
}

#endif
