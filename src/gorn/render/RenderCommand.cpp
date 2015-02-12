
#include <gorn/render/RenderCommand.hpp>
#include <gorn/render/Kinds.hpp>

namespace gorn
{
    RenderCommandBlock::RenderCommandBlock():
    count(0), type(BasicType::None)
    {
    }

    RenderCommandBlock::RenderCommandBlock(Data&& data, size_t count, BasicType type):
    data(std::move(data)), count(count), type(type)
    {
    }

    RenderCommandBlock::RenderCommandBlock(const Data& data, size_t count, BasicType type):
    data(data), count(count), type(type)
    {
    }

    RenderCommand::RenderCommand():
    _drawMode(DrawMode::Triangles),
    _transformMode(TransformMode::NoChange),
    _lifetime(Lifetime::Frame)
    {
    }

    RenderCommand& RenderCommand::withMaterial(const std::shared_ptr<Material>& material)
    {
        _material = material;
        return *this;
    }

    RenderCommand& RenderCommand::withAttribute(const std::string& name,
        Data&& data, size_t count, BasicType type)
    {
        _attributes[name] = Block(std::move(data), count, type);
        return *this;
    }

    RenderCommand& RenderCommand::withAttribute(const std::string& name,
        const Data& data, size_t count, BasicType type)
    {
        _attributes[name] = Block(data, count, type);
        return *this;
    }

    RenderCommand& RenderCommand::withElements(const std::string& name,
        Data&& data, BasicType type)
    {
        _elements[name] = Block(std::move(data), data.size()/getSize(type), type);
        return *this;
    }

    RenderCommand& RenderCommand::withElements(const std::string& name,
        const Data& data, BasicType type)
    {
        _elements[name] = Block(data, data.size()/getSize(type), type);
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

    RenderCommand& RenderCommand::withLifetime(Lifetime lifetime)
    {
        _lifetime = lifetime;
        return *this;
    }

    RenderCommand::Block& RenderCommand::getElements(const std::string& name)
    {
        return _elements.at(name);
    }

    const RenderCommand::Block& RenderCommand::getElements(const std::string& name) const
    {
        return _elements.at(name);
    }

    bool RenderCommand::hasElements(const std::string& name) const
    {
        return _elements.find(name) != _elements.end();
    }

    std::map<std::string, RenderCommand::Block>& RenderCommand::getElements()
    {
        return _elements;
    }

    const std::map<std::string, RenderCommand::Block>& RenderCommand::getElements() const
    {
        return _elements;
    }

    RenderCommand::Block& RenderCommand::getAttribute(const std::string& name)
    {
        return _attributes.at(name);
    }

    const RenderCommand::Block& RenderCommand::getAttribute(const std::string& name) const
    {
        return _attributes.at(name);
    }

    bool RenderCommand::hasAttribute(const std::string& name) const
    {
        return _attributes.find(name) != _attributes.end();
    }

    std::map<std::string, RenderCommand::Block>& RenderCommand::getAttributes()
    {
        return _attributes;
    }

    const std::map<std::string, RenderCommand::Block>& RenderCommand::getAttributes() const
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

    RenderCommand::Lifetime RenderCommand::getLifetime() const
    {
        return _lifetime;
    }

    VertexDefinition RenderCommand::generateVertexDefinition() const
    {
        VertexDefinition vdef;
        for(auto itr = _attributes.begin();
          itr != _attributes.end(); ++itr)
        {
            auto offset = vdef.getElementSize();
            vdef.setAttribute(itr->first)
                .withType(itr->second.type)
                .withCount(itr->second.count)
                .withOffset(offset);
        }
        size_t stride = vdef.getElementSize();
        for(auto itr = vdef.getAttributes().begin();
          itr != vdef.getAttributes().end(); ++itr)
        {
            itr->second.withStride(stride);
        }
        return vdef;
    }

    size_t RenderCommand::getVertexData(const VertexDefinition& vdef,
        Data& vertData, Data& elmData) const
    {
        DataOutputStream outVert(vertData);
        DataOutputStream outElm(elmData);

        size_t n = 0;
        bool finished = false;
        while(!finished)
        {
            finished = true;
            for(auto itr = vdef.getAttributes().begin();
              itr != vdef.getAttributes().end(); ++itr)
            {
                size_t elmSize = itr->second.getMemSize();
                auto& block = getAttribute(itr->first);
                size_t writeSize = outVert.write(block.data, elmSize, n*elmSize);
                outVert.write(elmSize-writeSize);
                if(writeSize != 0)
                {
                    finished = false;
                }
            }
            n++;
        }
        // TODO: different elements for each attribute
        auto itr = _elements.find(AttributeKind::Position);
        if(itr != _elements.end())
        {
            outElm.write(itr->second.data);
            n = itr->second.count;
        }
        return n;
    }

}

