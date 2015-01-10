
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

        render2d.getSprites().setDefaultProgram(RenderSystem2D::Sprite);
        render2d.getSprites().define("guybrush")
            .withAtlas("guybrush.atlas")
            .withAnimation("walk", SpriteAnimationDefinition()
                .withFrames("gb_walk")
                .withFrameDuration(1.0f/5.0f));

        _sprite = render2d.getSprites().load("guybrush");
        _sprite.play("walk");
	}

	void Application::unload()
	{
	}

	void Application::update(double dt)
	{
        _sprite.update(dt);
        _sprite.render(_render.getQueue());
		_render.getQueue().draw();
	}

}
