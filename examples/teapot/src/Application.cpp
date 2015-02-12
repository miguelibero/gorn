
#include <gorn/gorn.hpp>
#include <glm/gtx/transform.hpp>

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
            .addDefaultLoader<LocalFileLoader>("../assets/%s");
#elif GORN_PLATFORM_ANDROID
		_ctx.getFiles()
            .addDefaultLoader<AssetFileLoader>("%s");
#elif GORN_PLATFORM_IOS
        _ctx.getFiles()
        .addDefaultLoader<BundleFileLoader>("%s");
#endif

        _ctx.getMaterials().getDefinitions()
            .set("metal", MaterialDefinition()
                .withProgram("diffuse"));

        AssetManager<RenderCommand> meshes(_ctx.getFiles());
        meshes.addDefaultDataLoader<ObjMeshLoader>();

        _ctx.getQueue().setUniformValue(UniformKind::Projection,
            glm::perspective(
                glm::pi<float>()/6.0f,
                4.0f / 3.0f,
                0.1f,
                100.0f
            ));

        _ctx.getQueue().setUniformValue(UniformKind::View,
            glm::lookAt(
                glm::vec3(0.0f, 1.5f, 10.0f),
                glm::vec3(0.0f, 1.5f, 0.0f),
                glm::vec3(0.0f, 1.0f ,0.0f)
            ));

        auto cmd = *meshes.load("teapot.obj").get().get();
        cmd.withMaterial(_ctx.getMaterials().load("metal"));
        cmd.withLifetime(RenderCommand::Lifetime::Forever);
        _ctx.getQueue().addCommand(std::move(cmd));

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

		_ctx.getQueue().draw();
	}

}
