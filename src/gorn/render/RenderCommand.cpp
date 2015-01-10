
#include <gorn/render/RenderCommand.hpp>

namespace gorn
{
    RenderCommandBlock::RenderCommandBlock():
    type(0), count(0)
    {
    }

    RenderCommandBlock::RenderCommandBlock(Data&& data, GLenum type, GLsizei count):
    data(std::move(data)), type(type), count(count)
    {
    }

    RenderCommandBlock::RenderCommandBlock(const Data& data, GLenum type, GLsizei count):
    data(data), type(type), count(count)
    {
    }

    RenderCommand::RenderCommand():
    _drawMode(GL_TRIANGLES)
    {
    }

    RenderCommand& RenderCommand::withMaterial(const std::shared_ptr<Material>& material)
    {
        _material = material;
        return *this;
    }

    RenderCommand& RenderCommand::withAttribute(const std::string& name,
        Data&& data, GLenum type, GLint count)
    {
        _attributes[name] = Block(std::move(data), type, count);
        return *this;
    }

    RenderCommand& RenderCommand::withAttribute(const std::string& name,
        const Data& data, GLenum type, GLint count)
    {
        _attributes[name] = Block(data, type, count);
        return *this;
    }

    RenderCommand& RenderCommand::withElements(Data&& data, GLenum type, GLsizei count)
    {
        _elements = Block(std::move(data), type, count);
        return *this;
    }

    RenderCommand& RenderCommand::withElements(const Data& data, GLenum type, GLsizei count)
    {
        _elements = Block(data, type, count);
        return *this;
    }

    RenderCommand& RenderCommand::withElementCount(GLsizei count)
    {
        _elements.count = count;
        return *this;
    }

    RenderCommand& RenderCommand::withDrawMode(GLenum mode)
    {
        _drawMode = mode;
        return *this;
    }


    RenderCommand::Block& RenderCommand::getElements()
    {
        return _elements;
    }

    const RenderCommand::Block& RenderCommand::getElements() const
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

    GLenum RenderCommand::getDrawMode() const
    {
        return _drawMode;
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
        GLsizei stride = vdef.getElementSize();
        for(auto itr = vdef.getAttributes().begin();
          itr != vdef.getAttributes().end(); ++itr)
        {
            itr->second.withStride(stride);
        }
        return vdef;
    }

    Data RenderCommand::generateVertexData(const VertexDefinition& vdef) const
    {
        Data data;
        DataOutputStream out(data);

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
                size_t writeSize = out.write(block.data, elmSize, n*elmSize);
                out.write(elmSize-writeSize);
                if(writeSize != 0)
                {
                    finished = false;
                }
            }
            n++;
        }
        return data;
    }


}

