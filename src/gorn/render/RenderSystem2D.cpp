
#include <gorn/render/RenderSystem2D.hpp>
#include <gorn/render/RenderContext.hpp>
#include <gorn/render/ProgramManager.hpp>
#include <gorn/render/Kinds.hpp>
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
            .withShaderData(ShaderType::Vertex, R"(#version 100

precision highp float;

attribute vec2 position;
attribute vec2 texCoords;

varying vec2 TexCoords;

void main()
{
    TexCoords = texCoords;
    gl_Position = vec4(position, 0.0, 1.0);
}

)")
            .withShaderData(ShaderType::Fragment, R"(#version 100

precision highp float;

varying vec2 TexCoords;

uniform sampler2D texture;

void main()
{
    gl_FragColor = texture2D(texture, TexCoords);
}

)")
            .withUniform("texture", UniformKind::Texture0)
            .withAttribute("position", AttributeKind::Position)
            .withAttribute("texCoords", AttributeKind::TexCoords);
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

