
#include <gorn/render/RenderCommand.hpp>
#include <gorn/render/RenderKinds.hpp>
#include <gorn/gl/Program.hpp>
#include <gorn/base/Exception.hpp>
#include <buffer_writer.hpp>
#include <iostream>

namespace gorn
{
    RenderCommandAttribute::RenderCommandAttribute():
    count(0), type(BasicType::None)
    {
    }

    RenderCommandAttribute::RenderCommandAttribute(
        buffer&& data, size_t count, BasicType type):
    data(std::move(data)), count(count), type(type)
    {
    }

    RenderCommandAttribute::RenderCommandAttribute(
        const buffer& data, size_t count, BasicType type):
    data(data), count(count), type(type)
    {
    }

    RenderCommand::RenderCommand():
    _drawMode(DrawMode::Triangles),
    _transformMode(TransformStackAction::None),
	_boundingStackAction(StackAction::None),
	_layersStackAction(StackAction::None),
	_blendStackAction(StackAction::None)
    {
    }

	RenderCommand& RenderCommand::withUniformValue(const std::string& name,
		const UniformValue& value)
	{
		_uniforms[name] = value;
		return *this;
	}

    RenderCommand& RenderCommand::withMaterial(
        const std::shared_ptr<Material>& material)
    {
        _material = material;
        return *this;
    }

    RenderCommand& RenderCommand::withAttribute(const std::string& name,
        buffer&& data, size_t count, BasicType type)
    {
        _attributes[name] = Attribute(std::move(data), count, type);
        return *this;
    }

    RenderCommand& RenderCommand::withAttribute(const std::string& name,
        const buffer& data, size_t count, BasicType type)
    {
        _attributes[name] = Attribute(data, count, type);
        return *this;
    }

    RenderCommand& RenderCommand::withElements(Elements&& elms)
    {
         _elements = std::move(elms);
        return *this;
    }

    RenderCommand& RenderCommand::withElements(const Elements& elms)
    {
         _elements = elms;
        return *this;
    }

    RenderCommand& RenderCommand::withDrawMode(DrawMode mode)
    {
        _drawMode = mode;
        return *this;
    }

    RenderCommand& RenderCommand::withTransform(const glm::mat4& trans,
        TransformStackAction mode)
    {
        _transform = trans;
        _transformMode = mode;
        return *this;
    }

    RenderCommand& RenderCommand::withTransformAction(TransformStackAction mode)
    {
        _transformMode = mode;
        return *this;
    }

    RenderCommand& RenderCommand::withBounding(const Rect& bb)
    {
        _boundingBox = bb;
        _boundingStackAction = StackAction::Push;
        return *this;
    }

    RenderCommand& RenderCommand::withBoundingAction(StackAction action)
    {
        _boundingStackAction = action;
        return *this;
    }

    RenderCommand& RenderCommand::withStencil(const Stencil& stencil)
    {
        _stencil = stencil;
        return *this;
    }

    RenderCommand& RenderCommand::withClearAction(const ClearAction& clear)
    {
        _clearAction = clear;
        return *this;
    }

    RenderCommand& RenderCommand::withStateChange(const StateChange& change)
    {
        _stateChange = change;
        return *this;
    }

	RenderCommand& RenderCommand::withBlendMode(const BlendMode& mode)
	{
		_blendMode = mode;
		_blendStackAction = StackAction::Push;
		return *this;
	}

	RenderCommand& RenderCommand::withBlendModeAction(StackAction action)
	{
		_blendStackAction = action;
		return *this;
	}

	RenderCommand& RenderCommand::withLayer(int layer)
	{
		_layers.push_back(layer);
		_layersStackAction = StackAction::Push;
		return *this;
	}

	RenderCommand& RenderCommand::withLayers(const Layers& layers)
	{
		_layers.insert(_layers.end(), layers.begin(), layers.end());
		_layersStackAction = StackAction::Push;
		return *this;
	}

	RenderCommand& RenderCommand::withLayersAction(StackAction action)
	{
		_layersStackAction = action;
		return *this;
	}

    RenderCommand::Elements& RenderCommand::getElements()
    {
        return _elements;
    }

    const RenderCommand::Elements& RenderCommand::getElements() const
    {
        return _elements;
    }

    bool RenderCommand::hasElements() const
    {
        return !_elements.empty();
    }

    RenderCommand::Attribute& RenderCommand::getAttribute(const std::string& name)
    {
        return _attributes.at(name);
    }

    const RenderCommand::Attribute& RenderCommand::getAttribute(const std::string& name) const
    {
        return _attributes.at(name);
    }

    bool RenderCommand::hasAttribute(const std::string& name) const
    {
        return _attributes.find(name) != _attributes.end();
    }

    RenderCommand::AttributeMap& RenderCommand::getAttributes()
    {
        return _attributes;
    }

    const RenderCommand::AttributeMap& RenderCommand::getAttributes() const
    {
        return _attributes;
    }

	UniformValueMap& RenderCommand::getUniformValues()
	{
		return _uniforms;
	}

	const UniformValueMap& RenderCommand::getUniformValues() const
	{
		return _uniforms;
	}

    const std::shared_ptr<Material>& RenderCommand::getMaterial() const
    {
        return _material;
    }

    DrawMode RenderCommand::getDrawMode() const
    {
        return _drawMode;
    }

    const glm::mat4& RenderCommand::getTransform() const
    {
        return _transform;
    }

    RenderCommand::TransformStackAction RenderCommand::getTransformMode() const
    {
        return _transformMode;
    }

    const Stencil& RenderCommand::getStencil() const
    {
        return _stencil;
    }

    const ClearAction& RenderCommand::getClearAction() const
    {
        return _clearAction;
    }

    const StateChange& RenderCommand::getStateChange() const
    {
        return _stateChange;
    }

	const BlendMode& RenderCommand::getBlendMode() const
	{
		return _blendMode;
	}

	RenderCommand::StackAction RenderCommand::getBlendStackAction() const
	{
		return _blendStackAction;
	}

    RenderCommand::StackAction RenderCommand::getBoundingStackAction() const
    {
        return _boundingStackAction;
    }

    const Rect& RenderCommand::getBoundingBox() const
    {
        return _boundingBox;
    }

	const RenderCommand::Layers& RenderCommand::getLayers() const
	{
		return _layers;
	}

	RenderCommand::StackAction RenderCommand::getLayersStackAction() const
	{
		return _layersStackAction;
	}

    VertexDefinition RenderCommand::getVertexDefinition(const Program& prog) const
    {
        VertexDefinition vdef;
        for(auto itr = _attributes.begin(); itr != _attributes.end(); ++itr)
        {
            if(prog.hasAttribute(itr->first))
            {
                auto offset = vdef.getElementSize();
                auto trans = prog.getAttributeTransformation(itr->first);
                vdef.setAttribute(itr->first)
                    .withType(itr->second.type)
                    .withCount(itr->second.count)
                    .withOffset(offset)
                    .withTransformation(trans);
            }
        }
        size_t stride = vdef.getElementSize();
        for(auto itr = vdef.getAttributes().begin();
          itr != vdef.getAttributes().end(); ++itr)
        {
            itr->second.withStride(stride);
        }
        return vdef;
    }

    void RenderCommand::getVertexData(buffer& data, Elements& elms,
        const VertexDefinition& vdef, const glm::mat4& transform) const
    {
        elm_t e = vdef.getElementSize();
        if(e == 0)
        {
            return;
        }
        buffer_writer out(data);
        out.advance(data.size());
        elm_t s = (elm_t)data.size()/e;
        elm_t n = 0;

        bool finished = false;
		std::map<std::string, buffer> transAttrs;
		std::vector<std::pair<const buffer*,size_t>> attrsData;
		// transform attributes
		for(auto itr = vdef.getAttributes().begin(); itr != vdef.getAttributes().end(); ++itr)
		{
			auto& def = itr->second;
			auto itr2 = _attributes.find(itr->first);
			if(itr2 != _attributes.end())
			{
				auto& block = itr2->second;
				const buffer* attrBuffer = &block.data;
				if(def.isTransformed())
				{
					buffer data(block.data);
					def.transform(data, transform);
					auto itr3 = transAttrs.insert(transAttrs.end(), { itr->first, std::move(data) });
					attrBuffer = &itr3->second;
				}
				attrsData.push_back(std::make_pair(
					attrBuffer,
					def.getElementSize()
					));
			}
		}
        while(!finished)
        {
            finished = true;
            for(auto itr = attrsData.begin();
              itr != attrsData.end(); ++itr)
            {
				auto& data = itr->first;
				auto elmSize = itr->second;
                auto writeSize = out.write(*data, elmSize, elmSize*n);
                if(writeSize != 0)
                {
                    out.fill(0, elmSize - writeSize);
                    finished = false;
                }
            }
            if(!finished)
            {
                n++;
            }
        }
        if(hasElements())
        {
            const Elements& nelms = getElements();
            elms.reserve(elms.size()+nelms.size());
            for(auto itr = nelms.begin(); itr != nelms.end(); ++itr)
            {
                elms.push_back(s+*itr);
            }
        }
        else
        {
            elms.reserve(elms.size()+n);
            for(unsigned int i=0;i<n;i++)
            {
                elms.push_back(s+i);
            }
        }
    }

}
