
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

    size_t RenderCommandAttribute::write(buffer_writer& out,
        const Definition& def, size_t pos) const
    {
        size_t elmSize = def.getElementSize();
        return out.write(data, elmSize, pos*elmSize);
    }

    size_t RenderCommandAttribute::write(buffer_writer& out,
        const Definition& def, size_t pos, const glm::mat4& t) const
    {
        if(def.getType() != BasicType::Float)
        {
            throw Exception("Only transformable floats supported.");
        }
        auto count = def.getCount();
        size_t elmSize = def.getElementSize();
        if(elmSize*pos >= data.size())
        {
            return 0;
        }
        if(count == 3)
        {
            auto vecs = reinterpret_cast<const glm::vec3*>(data.data());
            auto vec = glm::vec3(t*glm::vec4(vecs[pos], 1.0f));
            return out.write(glm::value_ptr(vec), elmSize);
        }
        else if(count == 2)
        {
            auto vecs = reinterpret_cast<const glm::vec2*>(data.data());
            auto vec = glm::vec2(t*glm::vec4(vecs[pos], 0.0f, 1.0f));
            return out.write(glm::value_ptr(vec), elmSize);
        }
        else
        {
            throw Exception("Only transformable vec2 or vec3 supported.");
        }
    }

    RenderCommand::RenderCommand():
    _drawMode(DrawMode::Triangles),
    _transformMode(TransformMode::NoChange),
    _boundingMode(BoundingMode::None)
    {
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
        TransformMode mode)
    {
        _transform = trans;
        _transformMode = mode;
        return *this;
    }
    
    RenderCommand& RenderCommand::withTransformMode(TransformMode mode)
    {
        _transformMode = mode;
        return *this;
    }

    RenderCommand& RenderCommand::withBounding(const Rect& bb,
        BoundingMode mode)
    {
        _boundingBox = bb;
        _boundingMode = mode;
        return *this;
    }

    RenderCommand& RenderCommand::withBoundingMode(BoundingMode mode)
    {
        _boundingMode = mode;
        return *this;
    }


    RenderCommand& RenderCommand::withStencil(const Stencil& stencil)
    {
        _stencil = stencil;
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

    RenderCommand::TransformMode RenderCommand::getTransformMode() const
    {
        return _transformMode;
    }

    const Stencil& RenderCommand::getStencil() const
    {
        return _stencil;
    }

    VertexDefinition RenderCommand::getVertexDefinition(const Program& prog) const
    {
        VertexDefinition vdef;
        for(auto itr = _attributes.begin();
          itr != _attributes.end(); ++itr)
        {
            if(prog.hasAttribute(itr->first))
            {
                auto offset = vdef.getElementSize();
                auto trans = prog.hasTransformableAttribute(itr->first);
                vdef.setAttribute(itr->first)
                    .withType(itr->second.type)
                    .withCount(itr->second.count)
                    .withOffset(offset)
                    .withTransformable(trans);
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
        while(!finished)
        {
            finished = true;
            for(auto itr = vdef.getAttributes().begin();
              itr != vdef.getAttributes().end(); ++itr)
            {
                auto& block = getAttribute(itr->first);
                auto& def = itr->second;
                size_t writeSize = 0;
                if(itr->second.getTransformable())
                {
                    writeSize = block.write(out, def, n, transform);
                }
                else
                {
                    writeSize = block.write(out, def, n);
                }
                size_t elmSize = def.getElementSize();
                out.fill(0, elmSize-writeSize);
                if(writeSize != 0)
                {
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

    RenderCommand::BoundingMode RenderCommand::getBoundingMode() const
    {
        return _boundingMode;
    }

    const Rect& RenderCommand::getBoundingBox() const
    {
        return _boundingBox;
    }

}

