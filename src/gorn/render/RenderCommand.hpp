#ifndef __gorn__RenderCommand__
#define __gorn__RenderCommand__

#include <gorn/base/Data.hpp>
#include <gorn/render/VertexDefinition.hpp>
#include <gorn/render/Material.hpp>

namespace gorn
{
    class VertexDefinition;

    struct RenderCommandBlock
    {
        Data data;
        GLenum type;
        GLsizei count;

        RenderCommandBlock();
        RenderCommandBlock(Data&& data, GLenum type, GLsizei count);
        RenderCommandBlock(const Data& data, GLenum type, GLsizei count);
    };

    class RenderCommand
    {
    public:
        typedef RenderCommandBlock Block;
    private:
        std::map<std::string, Block> _attributes;
        Block _elements;
        std::shared_ptr<Material> _material;
        GLenum _drawMode;
    public:
        RenderCommand();
        RenderCommand& withMaterial(const std::shared_ptr<Material>& material);
        RenderCommand& withAttribute(const std::string& name,
            Data&& data, GLenum type, GLsizei count);
        RenderCommand& withAttribute(const std::string& name,
            const Data& data, GLenum type, GLsizei count);
        RenderCommand& withElements(Data&& data, GLenum type, GLsizei count);
        RenderCommand& withElements(const Data& data, GLenum type, GLsizei count);
        RenderCommand& withElementCount(GLsizei count);
        RenderCommand& withDrawMode(GLenum mode);

        Block& getElements();
        const Block& getElements() const;

        Block& getAttribute(const std::string& name);
        const Block& getAttribute(const std::string& name) const;
        bool hasAttribute(const std::string& name) const;
        std::map<std::string, Block>& getAttributes();
        const std::map<std::string, Block>& getAttributes() const;

        const std::shared_ptr<Material>& getMaterial() const;
        GLenum getDrawMode() const;

        VertexDefinition generateVertexDefinition() const;
        Data generateVertexData(const VertexDefinition& vdef) const;

    };
}

#endif
