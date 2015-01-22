
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
            .addLoader<LocalFileLoader>("sprite", "../%s.png");
		_render.getFiles()
            .addLoader<LocalFileLoader>("vsh", "../%s.vsh");
		_render.getFiles()
            .addLoader<LocalFileLoader>("fsh", "../%s.fsh");
		_render.getImages()
            .addLoader<PngImageLoader>("sprite");
#elif GORN_PLATFORM_ANDROID
		_render.getFiles()
            .addLoader<BundleFileLoader>("sprite", "%s.png");
		_render.getFiles()
            .addLoader<BundleFileLoader>("vsh", "%s.vsh");
		_render.getFiles()
            .addLoader<BundleFileLoader>("fsh", "%s.fsh");
		_render.getImages()
            .addLoader<GraphicsImageLoader>("sprite");
#endif

        _render.getMaterials().getDefinitions()
            .set("sprite", [](const std::string& name){
                return MaterialDefinition()
                    .withProgram("sprite")
                    .withTexture(UniformKind::Texture0, name);
            });

	    _render.getPrograms().getDefinitions().get("sprite")
            .withUniform("texture", UniformKind::Texture0)
            .withShaderFile(ShaderType::Vertex, "vsh:shader")
            .withShaderFile(ShaderType::Fragment, "fsh:shader");
	}

	void Application::unload()
	{
	}

	void Application::update(double dt)
	{

        _render.getQueue().addCommand("sprite:kitten")
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

        _render.getQueue().addCommand("sprite:puppy")
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
