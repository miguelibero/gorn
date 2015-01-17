
#include <gorn/render/RenderSystem2D.hpp>
#include <gorn/render/RenderContext.hpp>
#include <gorn/render/ProgramManager.hpp>
#include <gorn/render/Kinds.hpp>
#include <gorn/asset/FileManager.hpp>
#include <gorn/sprite/CocosSpriteAtlasLoader.hpp>
#include <gorn/sprite/GdxSpriteAtlasLoader.hpp>
#include <gorn/sprite/FntSpriteAtlasLoader.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gorn
{
    const char* RenderSystem2D::Sprite = "sprite";

    RenderSystem2D::RenderSystem2D(RenderContext& context):
    _context(context),
    _sprites(context.getMaterials(), context.getFiles()),
    _labels(context.getMaterials(), context.getFiles())
    {
        _sprites.getAtlases().addLoader<GdxSpriteAtlasLoader>();
        _sprites.getAtlases().addLoader<CocosSpriteAtlasLoader>();
        _labels.getAtlases().addLoader<FntSpriteAtlasLoader>();

	    context.getPrograms().define(Sprite)
            .withShaderData(ShaderType::Vertex, R"(#version 100

precision highp float;

attribute vec2 position;
attribute vec2 texCoords;

varying vec2 TexCoords;

uniform mat4 transform;

void main()
{
    TexCoords = texCoords;
    gl_Position = transform*vec4(position, 0.0, 1.0);
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
            .withUniform("transform", UniformKind::Transform)
            .withUniform("texture", UniformKind::Texture0)
            .withAttribute("position", AttributeKind::Position)
            .withAttribute("texCoords", AttributeKind::TexCoords);
    }

    const SpriteManager& RenderSystem2D::getSprites() const
    {
        return _sprites;
    }

    SpriteManager& RenderSystem2D::getSprites()
    {
        return _sprites;
    }

    const LabelManager& RenderSystem2D::getLabels() const
    {
        return _labels;
    }

    LabelManager& RenderSystem2D::getLabels()
    {
        return _labels;
    }
}

