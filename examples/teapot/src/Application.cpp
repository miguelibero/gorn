
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
#if GORN_PLATFORM_LINUX || GORN_PLATFORM_WINDOWS
    _ctx.getFiles()
        .makeDefaultLoader<LocalFileLoader>("../assets/%s");
#elif GORN_PLATFORM_ANDROID
    _ctx.getFiles()
        .makeDefaultLoader<AssetFileLoader>("%s");
#elif GORN_PLATFORM_IOS
    _ctx.getFiles()
    .makeDefaultLoader<BundleFileLoader>("%s");
#endif

    _ctx.getImages()
        .makeDefaultDataLoader<StbImageLoader>();

    _ctx.getMaterials().getDefinitions()
        .set("metal", MaterialDefinition()
            .withTexture(gorn::UniformKind::Texture0, "default.png")
            .withProgram("diffuse"));

    AssetManager<Mesh> meshes(_ctx.getFiles());
    meshes.makeDefaultDataLoader<ObjMeshLoader>();

    _ctx.getQueue().setProjectionTransform(
        glm::perspective(
            glm::pi<float>()/6.0f,
            4.0f / 3.0f,
            0.1f,
            400.0f
        ));

    _ctx.getQueue().setViewTransform(
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
