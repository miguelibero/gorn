
#include <gorn/gorn.hpp>
#include <glm/gtx/transform.hpp>

using namespace gorn;

class FrustumApplication : public gorn::Application
{
	gorn::Context _ctx;
    gorn::Mesh _sphereMesh;
    gorn::Mesh _frustumMesh;
    Frustum _frustum;

public:

    FrustumApplication();

    void load() override;
    void draw() override;
};

namespace gorn
{
    std::unique_ptr<Application> main()
    {
        return std::unique_ptr<Application>(new FrustumApplication());
    }
}

FrustumApplication::FrustumApplication()
{
}

void FrustumApplication::load()
{
#ifdef GORN_PLATFORM_LINUX
	_ctx.getFiles()
        .makeDefaultLoader<LocalFileLoader>("../assets/%s");
#elif GORN_PLATFORM_WINDOWS
	_ctx.getFiles()
		.makeDefaultLoader<LocalFileLoader>("../assets/%s");
#elif GORN_PLATFORM_ANDROID
	_ctx.getFiles()
        .makeDefaultLoader<AssetFileLoader>("%s");
#elif GORN_PLATFORM_IOS
    _ctx.getFiles()
        .makeDefaultLoader<BundleFileLoader>("%s");
#endif

    _ctx.getMaterials().getDefinitions().set("in", MaterialDefinition()
        .withProgram("shader")
        .withUniformValue(UniformKind::Color, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)));

    _ctx.getMaterials().getDefinitions().set("out", MaterialDefinition()
        .withProgram("shader")
        .withUniformValue(UniformKind::Color, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)));

    _ctx.getMaterials().getDefinitions().set("frustum", MaterialDefinition()
        .withProgram("shader")
        .withUniformValue(UniformKind::Color, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)));

    _ctx.getQueue().setProjectionTransform(
        glm::perspective(
            glm::pi<float>()/6.0f,
            4.0f / 3.0f,
            0.1f,
            200.0f
        ));

    auto view = glm::lookAt(
            glm::vec3(-50.0f, 50.0f, 50.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f ,0.0f)
        );

    _ctx.getQueue().setViewTransform(view);
    _frustum = glm::frustum(-10.f, 10.f, -10.f, 10.f, 0.1f, -10.f);

    _sphereMesh = ShapeMeshFactory::create(
        SphereShape().withRings(10).withSectors(10));

    _frustumMesh = ShapeMeshFactory::create(_frustum, DrawMode::Lines);
}

void FrustumApplication::draw()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    auto cmd = _frustumMesh.render();
    cmd.withMaterial(_ctx.getMaterials().load("frustum"));
    _ctx.getQueue().addCommand(std::move(cmd));

    float amount = 10.0f;
    float sep = 4.0f;
    glm::vec3 origin;

    for(float x = -0.5f*amount; x<0.5f*amount; x++)
    {
        for(float y = -0.5f*amount; y<0.5f*amount; y++)
        {
            auto p = glm::vec3(x*sep, y*sep, 0.0f);
            auto aabb = gorn::Rect(
                glm::vec3(p)-glm::vec3(0.5f), glm::vec3(1.0f));
            bool in = _frustum.sees(aabb);

            auto cmd = _sphereMesh.render();
            cmd.withMaterial(_ctx.getMaterials().load(in?"in":"out"));
            cmd.withTransform(glm::translate(glm::mat4(), p),
                RenderCommand::TransformMode::SetGlobal);
            cmd.withBounding(aabb);
            _ctx.getQueue().addCommand(std::move(cmd));
        }
    }

	_ctx.getQueue().draw();
}
