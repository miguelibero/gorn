
#include <gorn/render/RenderCommand.hpp>

namespace gorn
{

    RenderCommand::RenderCommand()
    {
    }

    RenderCommand& RenderCommand::withVertexData(Data&& data)
    {
        _vertexData = std::move(data);
        return *this;
    }

    RenderCommand& RenderCommand::withElementData(Data&& data)
    {
        _elementData = std::move(data);
        return *this;
    }

    RenderCommand& RenderCommand::withVertexDefinition(const VertexDefinition& def)
    {
        _vertexDef = def;
        return *this;
    }

    RenderCommand& RenderCommand::withMaterial(const std::shared_ptr<Material>& material)
    {
        _material = material;
        return *this;
    }

    bool RenderCommand::combine(RenderCommand&& other)
    {
        return false;
    }
}

