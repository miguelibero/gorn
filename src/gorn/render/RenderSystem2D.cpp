
#include <gorn/render/RenderSystem2D.hpp>
#include <gorn/render/RenderContext.hpp>
#include <gorn/render/ProgramManager.hpp>
#include <gorn/asset/FileManager.hpp>
#include <gorn/asset/GdxSpriteAtlasLoader.hpp>

namespace gorn
{
    const char* RenderSystem2D::Sprite = "sprite";

    RenderSystem2D::RenderSystem2D(RenderContext& context):
    _context(context),
    _spriteAtlases(context.getFiles())
    {
        _spriteAtlases.addLoader<GdxSpriteAtlasLoader>(_context.getMaterials());

	    context.getPrograms().define(Sprite)
            .withShaderData(ShaderType::Vertex, "#version 100"

"precision highp float;"

"attribute vec2 position;"
"attribute vec2 texCoords;"

"varying vec2 TexCoords;"

"void main()"
"{"
"    TexCoords = texCoords;"
"    gl_Position = vec4(position, 0.0, 1.0);"
"}")
            .withShaderData(ShaderType::Fragment, "#version 100"

"precision highp float;"

"varying vec2 TexCoords;"

"uniform sampler2D texture;"

"void main()"
"{"
"    gl_FragColor = texture2D(texture, TexCoords);"
"}")
            .withUniform("texture", UniformKind::Texture0)
            .withAttribute("position", AttributeKind::Position)
            .withAttribute("texCoords", AttributeKind::TexCoords);

        auto& vdef = context.getVertexDefinitions().preload(Sprite);
        vdef.setAttribute(AttributeKind::Position)
            .withType(GL_FLOAT)
            .withSize(2)
            .withStride(4*sizeof(GLfloat));
        vdef.setAttribute(AttributeKind::TexCoords)
            .withType(GL_FLOAT)
            .withSize(2)
            .withStride(4*sizeof(GLfloat))
            .withOffset(2*sizeof(GLfloat));
    }

    const AssetManager<SpriteAtlas>& RenderSystem2D::getSpriteAtlases() const
    {
        return _spriteAtlases;
    }

    AssetManager<SpriteAtlas>& RenderSystem2D::getSpriteAtlases()
    {
        return _spriteAtlases;
    }
}

