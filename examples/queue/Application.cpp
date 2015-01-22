
#include <gorn/gorn.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

namespace gorn
{
	RenderContext _render;

	Application::Application()
	{
	}

	void Application::load()
	{
#ifdef GORN_PLATFORM_LINUX
		_render.getFiles()
            .addDefaultLoader<LocalFileLoader>("../%s");
		_render.getImages()
            .addLoader<PngImageLoader>();
#elif GORN_PLATFORM_ANDROID
		_render.getFiles()
            .addDefaultLoader<BundleFileLoader>("%s");
		_render.getImages()
            .addLoader<GraphicsImageLoader>();
#endif

	    _render.getPrograms().define("shader")
            .withUniform("texture", UniformKind::Texture0)
            .withShaderFile(ShaderType::Vertex, "shader.vsh")
            .withShaderFile(ShaderType::Fragment, "shader.fsh");
        _render.getMaterials().define("kitten")
            .withProgram("shader")
            .withTexture(UniformKind::Texture0, "kitten.png");
        _render.getMaterials().define("puppy")
            .withProgram("shader")
            .withTexture(UniformKind::Texture0, "puppy.png");

	}

	void Application::unload()
	{
	}

	void Application::update(double dt)
	{

        _render.getQueue().addCommand("kitten")
            .withAttribute(AttributeKind::Position, {
                -0.75f,  0.75f,
                 0.25f,  0.75f,
                 0.25f, -0.25f,
                -0.75f, -0.25f,
                 0.66f
            }, GL_FLOAT, 2)
            .withAttribute(AttributeKind::TexCoords, {
                0.0f, 1.0f,
                1.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f
            }, GL_FLOAT, 2)
            .withElements({
                0, 1, 2,
                2, 3, 0
            }, GL_UNSIGNED_INT, 6);

        _render.getQueue().addCommand("puppy")
            .withAttribute(AttributeKind::Position, {
                -0.25f,  0.25f,
                 0.75f,  0.25f,
                 0.75f, -0.75f,
                -0.25f, -0.75f
            }, GL_FLOAT, 2)
            .withAttribute(AttributeKind::TexCoords, {
                0.0f, 1.0f,
                1.0f, 1.0f,
                1.0f, 0.0f,
                0.0f, 0.0f
            }, GL_FLOAT, 2)
            .withElements({
                0, 1, 2,
                2, 3, 0
            }, GL_UNSIGNED_INT, 6);

		_render.getQueue().draw();
	}

}
