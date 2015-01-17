
#include <gorn/gorn.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

namespace gorn
{
	RenderContext _render;
    Sprite _sprite1;
    Sprite _sprite2;

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

        _render.getTextures().define("guybrush.png")
            .withParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST)
            .withParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        _render.getMaterials().define("guybrush.png")
            .withProgram(RenderSystem2D::Sprite);

        render2d.getSprites().define("guybrush")
            .withAtlas("guybrush.atlas")
            .withAnimation("walk", SpriteAnimationDefinition()
                .withFrames("gb_walk")
                .withFrameDuration(1.0f/5.0f));

        _render.getQueue().setBaseTransform(
                glm::translate(glm::mat4(),
                glm::vec3(-0.25f, -0.25f, 0.0f)));

        _sprite1 = render2d.getSprites().load("guybrush");
        _sprite1.play("walk");

        _sprite2 = render2d.getSprites().load("guybrush");
        _sprite2.play("walk");
	}

	void Application::unload()
	{
	}

	void Application::update(double dt)
	{
        _sprite1.update(dt);
        _sprite2.update(dt);

        _sprite1.render(_render.getQueue());
        _render.getQueue().addCommand()
            .withTransform(
                glm::translate(glm::mat4(),
                glm::vec3(-0.5f, -0.5f, 0.0f)));
        _sprite2.render(_render.getQueue());
		_render.getQueue().draw();
	}

}
