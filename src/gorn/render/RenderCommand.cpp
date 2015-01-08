
#include <gorn/render/RenderCommand.hpp>

namespace gorn
{

    RenderCommand::RenderCommand(const VertexDefinition& def):
    _vertexDefinition(def),  
    _elementCount(0), _elementType(0),
    _drawMode(GL_TRIANGLES)
    {
    }

    RenderCommand& RenderCommand::withMaterial(const std::shared_ptr<Material>& material)
    {
        _material = material;
        return *this;
    }

    RenderCommand& RenderCommand::withVertexData(Data&& data)
    {
        _vertexData = std::move(data);
        return *this;
    }

    RenderCommand& RenderCommand::withAttributeData(const std::string& name, Data&& data)
    {
        return *this;
    }

    RenderCommand& RenderCommand::withElementData(Data&& data, GLenum type)
    {
        _elementData = std::move(data);
        _elementType = type;
        return *this;
    }

    RenderCommand& RenderCommand::withElementCount(GLsizei count)
    {
        _elementCount = count;
        return *this;
    }

    RenderCommand& RenderCommand::withDrawMode(GLenum mode)
    {
        _drawMode = mode;
        return *this;
    }

    Data& RenderCommand::getVertexData()
    {
        return _vertexData;
    }

    const Data& RenderCommand::getVertexData() const
    {
        return _vertexData;
    }

    VertexDefinition& RenderCommand::getVertexDefinition()
    {
        return _vertexDefinition;
    }

    const VertexDefinition& RenderCommand::getVertexDefinition() const
    {
        return _vertexDefinition;
    }

    Data& RenderCommand::getElementData()
    {
        return _elementData;
    }

    const Data& RenderCommand::getElementData() const
    {
        return _elementData;
    }

    const std::shared_ptr<Material>& RenderCommand::getMaterial() const
    {
        return _material;
    }

    GLsizei RenderCommand::getElementCount() const
    {
        return _elementCount;
    }

    GLenum RenderCommand::getElementType() const
    {
        return _elementType;
    }

    GLenum RenderCommand::getDrawMode() const
    {
        return _drawMode;
    }

}

