
#include <gorn/gorn.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

namespace gorn
{
	RenderContext _render;
    Sprite _sprite;

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

        _render.getMaterials().define("guybrush.png")
            .withProgram(RenderSystem2D::Sprite)
            .withTexture(UniformKind::Texture0, "guybrush.png");

        auto atlas = render2d.getSpriteAtlases().load("guybrush.atlas").get();
        _sprite.setMaterial(atlas->getMaterial());
        _sprite.setRegion(atlas->getRegion("gb_walk", 0));
	}

	void Application::unload()
	{
	}

	void Application::update(double dt)
	{
        _sprite.render(_render.getQueue());
		_render.getQueue().draw();
	}

}
