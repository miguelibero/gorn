
#include <gorn/gorn.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

namespace gorn
{
	Context _ctx;

	Application::Application()
	{
	}

	void Application::load()
	{
#ifdef GORN_PLATFORM_LINUX
		_ctx.getFiles()
            .addLoader<LocalFileLoader>("sprite", "../assets/%s.png");
		_ctx.getFiles()
            .addLoader<LocalFileLoader>("vsh", "../assets/%s.vsh");
		_ctx.getFiles()
            .addLoader<LocalFileLoader>("fsh", "../assets/%s.fsh");
		_ctx.getImages()
            .addDataLoader<PngImageLoader>("sprite");
#elif GORN_PLATFORM_ANDROID
		_ctx.getFiles()
            .addLoader<AssetFileLoader>("sprite", "%s.png");
		_ctx.getFiles()
            .addLoader<AssetFileLoader>("vsh", "%s.vsh");
		_ctx.getFiles()
            .addLoader<AssetFileLoader>("fsh", "%s.fsh");
		_ctx.getImages()
            .addDataLoader<GraphicsImageLoader>("sprite");
#endif

        _ctx.getMaterials().getDefinitions()
            .set("sprite", [](const std::string& name){
                return MaterialDefinition()
                    .withProgram("sprite")
                    .withTexture(UniformKind::Texture0, name);
            });

	    _ctx.getPrograms().getDefinitions().get("sprite")
            .withUniform("texture", UniformKind::Texture0)
            .withShaderFile(ShaderType::Vertex, "vsh:shader")
            .withShaderFile(ShaderType::Fragment, "fsh:shader");
	}

	void Application::background()
	{
	}

    void Application::foreground()
    {
    }

	void Application::unload()
	{
	}

	void Application::update(double dt)
	{
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        _ctx.getQueue().addCommand("sprite:kitten")
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

        _ctx.getQueue().addCommand("sprite:puppy")
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

		_ctx.getQueue().draw();
	}

}
