#ifndef __gorn__RenderCommand__
#define __gorn__RenderCommand__

#include <gorn/base/Data.hpp>
#include <gorn/render/VertexDefinition.hpp>
#include <gorn/render/Material.hpp>

namespace gorn
{
    class RenderCommand
    {
    private:
        Data _vertexData;
        Data _elementData;
        VertexDefinition _vertexDef;
        std::shared_ptr<Material> _material;
    public:
        RenderCommand();
        RenderCommand& withVertexData(Data&& data);
        RenderCommand& withElementData(Data&& data);
        RenderCommand& withVertexDefinition(const VertexDefinition& def);
        RenderCommand& withMaterial(const std::shared_ptr<Material>& material);

        bool combine(RenderCommand&& other);
    };
}

#endif
