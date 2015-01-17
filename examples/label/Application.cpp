
#include <gorn/gorn.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

namespace gorn
{
	RenderContext _render;
    Label _label;

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

        RenderSystem2D render2d(_render);

        _render.getQueue().setBaseTransform(
                glm::translate(glm::mat4(),
                glm::vec3(-0.5f, -0.5f, 0.0f)));

        _render.getMaterials().define("font.png")
            .withProgram(RenderSystem2D::Sprite);

        _label = render2d.getLabels().load("font.fnt");
        _label.setText("This is a label!");

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Application::unload()
	{
	}

	void Application::update(double dt)
	{
        _label.update(dt);
        _label.render(_render.getQueue());
		_render.getQueue().draw();
	}

}
