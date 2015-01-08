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
        VertexDefinition _vertexDefinition;
        std::shared_ptr<Material> _material;
        GLsizei _elementCount;
        GLenum _elementType;
        GLenum _drawMode;
    public:
        RenderCommand(const VertexDefinition& def);
        RenderCommand& withMaterial(const std::shared_ptr<Material>& material);
        RenderCommand& withVertexData(Data&& data);
        RenderCommand& withAttributeData(const std::string& name, Data&& data);
        RenderCommand& withElementData(Data&& data, GLenum type);
        RenderCommand& withElementCount(GLsizei count);
        RenderCommand& withDrawMode(GLenum mode);

        Data& getVertexData();
        const Data& getVertexData() const;

        VertexDefinition& getVertexDefinition();
        const VertexDefinition& getVertexDefinition() const;

        Data& getElementData();
        const Data& getElementData() const;

        const std::shared_ptr<Material>& getMaterial() const;

        GLsizei getElementCount() const;
        GLenum getElementType() const;
        GLenum getDrawMode() const;

    };
}

#endif
