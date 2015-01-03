
#include <gorn/gorn.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

namespace gorn
{
	RenderContext _render;
    Scene _scene;

	Application::Application()
	{
	}

	void Application::load()
	{

#ifdef GORN_PLATFORM_LINUX
		_render.getFileManager()
            ->addDefaultLoader<LocalFileLoader>("../%s");
		_render.getImageManager()
            ->addLoader<PngImageLoader>();
#elif GORN_PLATFORM_ANDROID
		_render.getFileManager()
            ->addDefaultLoader<BundleFileLoader>("%s");
		_render.getImageManager()
            ->addLoader<GraphicsImageLoader>();
#endif

	    _render.getPrograms().define("shader")
            .withVertexShader("shader.vsh")
            .withFragmentShader("shader.fsh")
            .withUniforms({"transform"});

        _render.getMaterials().define("guybrush")
            .withProgram("shader")
            .withTexture("texture", "guybrush.png");

        auto atlasMng = _render.createAssetManager<TextureAtlas>();
        atlasMng.addLoader<GdxTextureAtlasLoader>();

        auto sprite = _scene.addChild();
        sprite->addComponent<Sprite>(atlasMng.load("guybrush.atlas").get());
	}

	void Application::unload()
	{
	}

	void Application::update(double dt)
	{
		_render.getQueue().draw();
	}

}
