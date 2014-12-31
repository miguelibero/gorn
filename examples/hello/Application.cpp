#include <gorn/base/Application.hpp>
#include <gorn/base/Log.hpp>
#include <gorn/platform/PlatformBridge.hpp>
#include <gorn/render/Renderer.hpp>
#include <gorn/render/ProgramDefinition.hpp>
#include <gorn/render/MaterialDefinition.hpp>

#ifdef GORN_PLATFORM_LINUX
#include <gorn/platform/linux/PngImageLoader.hpp>
#include <gorn/platform/linux/LocalFileLoader.hpp>
#endif

namespace gorn
{
	PlatformBridge _bridge;
	Renderer _renderer;

	Application::Application()
	{
	}

	void Application::load()
	{
#ifdef GORN_PLATFORM_LINUX
		_bridge.addImageLoader(std::unique_ptr<ImageLoader>(
            new PngImageLoader()));
		_bridge.addFileLoader("texture", std::unique_ptr<FileLoader>(
            new LocalFileLoader("../examples/assets/textures/%s.png")));
#endif

		_renderer.setPlatformBridge(_bridge);
	    _renderer.defineProgram("sprite",
	        ProgramDefinition("shaders/sprite.vsh", "shaders/sprite.fsh")
	        .withUniforms({"projView"})
	        .withAttributes({"position", "texCoord", "color"}));
	    _renderer.defineMaterial("sprite",
	        MaterialDefinition("sprite")
	        .withTextures({"texture:img_test"}));

        _renderer.loadTexture("texture:img_test");
	}

	void Application::unload()
	{   
	}

	void Application::update(double dt)
	{
		_renderer.draw();
	}

}
