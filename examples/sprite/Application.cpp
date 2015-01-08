
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
        _render.basicSetup();
        RenderSystem2D render2d(_render);

        _render.getMaterials().define("guybrush")
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
        auto& cmd = _render.getQueue().addCommand(RenderSystem2D::Sprite);
        _sprite.render(cmd);
		_render.getQueue().draw();
	}

}
