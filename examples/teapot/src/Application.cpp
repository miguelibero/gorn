
#include <gorn/gorn.hpp>
#include <glm/gtx/transform.hpp>


using namespace gorn;

class TeapotApplication : public gorn::Application
{
	gorn::Context _ctx;
    std::shared_ptr<Mesh> _mesh;

public:

    TeapotApplication();

    void load() override;
    void draw() override;
};

namespace gorn
{
    std::unique_ptr<Application> main()
    {
        return std::unique_ptr<Application>(new TeapotApplication());
    }
}

TeapotApplication::TeapotApplication()
{
}

void TeapotApplication::load()
{
#ifdef GORN_PLATFORM_LINUX
	_ctx.getFiles()
        .addDefaultLoader<LocalFileLoader>("../assets/%s");
	_ctx.getImages()
        .addDefaultDataLoader<PngImageLoader>();
#elif GORN_PLATFORM_ANDROID
	_ctx.getFiles()
        .addDefaultLoader<AssetFileLoader>("%s");
#elif GORN_PLATFORM_IOS
    _ctx.getFiles()
    .addDefaultLoader<BundleFileLoader>("%s");
#endif

    _ctx.getMaterials().getDefinitions()
        .set("metal", MaterialDefinition()
            .withTexture(gorn::UniformKind::Texture0, "default.png")
            .withProgram("diffuse"));

    AssetManager<Mesh> meshes(_ctx.getFiles());
    meshes.addDefaultDataLoader<ObjMeshLoader>();

    _ctx.getQueue().setUniformValue(UniformKind::Projection,
        glm::perspective(
            glm::pi<float>()/6.0f,
            4.0f / 3.0f,
            0.1f,
            400.0f
        ));

    _ctx.getQueue().setUniformValue(UniformKind::View,  
        glm::lookAt(
            glm::vec3(0.0f, 200.0f, 300.0f),
            glm::vec3(0.0f, 50.0f, 0.0f),
            glm::vec3(0.0f, 1.0f ,0.0f)
        ));

    _mesh = meshes.load("teapot.obj").get();
}

void TeapotApplication::draw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    auto cmd = _mesh->render();
    cmd.withMaterial(_ctx.getMaterials().load("metal"));
    _ctx.getQueue().addCommand(std::move(cmd));

	_ctx.getQueue().draw();
}

