
#include <gorn/render/RenderCommand.hpp>

namespace gorn
{

    RenderCommand::RenderCommand():
    _elementCount(0), _elementType(0),
    _drawMode(GL_TRIANGLES)
    {
    }

    RenderCommand& RenderCommand::withVertexData(Data&& data, const VertexDefinition& def)
    {
        _vertexData = std::move(data);
        _vertexDefinition = def;
        return *this;
    }

    RenderCommand& RenderCommand::withElementData(Data&& data, GLenum type)
    {
        _elementData = std::move(data);
        _elementType = type;
        return *this;
    }

    RenderCommand& RenderCommand::withMaterial(const std::shared_ptr<Material>& material)
    {
        _material = material;
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

