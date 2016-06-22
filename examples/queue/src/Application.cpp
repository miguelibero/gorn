
#include <gorn/gorn.hpp>
#include <glm/gtx/transform.hpp>

using namespace gorn;

class QueueApplication : public gorn::Application
{
    gorn::Context _ctx;

public:

    QueueApplication();

    void load() override;
    void draw() override;
};

namespace gorn
{
    std::unique_ptr<Application> main()
    {
        return std::unique_ptr<Application>(new QueueApplication());
    }
}

QueueApplication::QueueApplication()
{
}

void QueueApplication::load()
{
#if GORN_PLATFORM_LINUX || GORN_PLATFORM_WINDOWS
    _ctx.getFiles()
        .makeLoader<LocalFileLoader>("sprite", "../assets/%s.png");
    _ctx.getFiles()
        .makeLoader<LocalFileLoader>("vsh", "../assets/%s.vsh");
    _ctx.getFiles()
        .makeLoader<LocalFileLoader>("fsh", "../assets/%s.fsh");
#elif GORN_PLATFORM_ANDROID
    _ctx.getFiles()
        .makeLoader<AssetFileLoader>("sprite", "%s.png");
    _ctx.getFiles()
        .makeLoader<AssetFileLoader>("vsh", "%s.vsh");
    _ctx.getFiles()
        .makeLoader<AssetFileLoader>("fsh", "%s.fsh");
#elif GORN_PLATFORM_IOS
    _ctx.getFiles()
        .makeLoader<BundleFileLoader>("sprite", "%s.png");
    _ctx.getFiles()
        .makeLoader<BundleFileLoader>("vsh", "%s.vsh");
    _ctx.getFiles()
        .makeLoader<BundleFileLoader>("fsh", "%s.fsh");
#endif

	_ctx.getQueue().addCamera();

    _ctx.getImages()
        .makeDataLoader<StbImageLoader>("sprite");

    _ctx.getMaterials().getDefinitions()
        .set("sprite", [](const std::string& name){
            return MaterialDefinition()
                .withProgram("sprite")
                .withTexture(UniformKind::Texture0, name);
        });

    _ctx.getPrograms().getDefinitions().get("sprite")
        .withUniform("texture", UniformKind::Texture0)
        .withShaderFile(ShaderType::Vertex, "vsh:shader")
        .withShaderFile(ShaderType::Fragment, "fsh:shader")
		.withAttribute(AttributeKind::Position,
			ProgramAttributeDefinition()
				.withCount(2)
			.withType(BasicType::Float))
		.withAttribute(AttributeKind::TexCoords,
			ProgramAttributeDefinition()
			.withCount(2)
			.withType(BasicType::Float));
}

void QueueApplication::draw()
{
    _ctx.getQueue().addCommand()
        .withClearAction(ClearAction()
            .withColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f))
            .withType(ClearType::Color));

    _ctx.getQueue().addCommand("sprite:kitten")
        .withAttribute(AttributeKind::Position, buffer{
            -0.75f,  0.75f,
             0.25f,  0.75f,
             0.25f, -0.25f,
            -0.75f, -0.25f
        })
        .withAttribute(AttributeKind::TexCoords, buffer{
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f
        })
        .withElements({
            0, 1, 2,
            2, 3, 0
        });

    _ctx.getQueue().addCommand("sprite:kitten")
        .withAttribute(AttributeKind::Position, buffer{
             0.25f,  0.75f,
             0.75f,  0.75f,
             0.75f, -0.25f,
             0.25f, -0.25f
        })
        .withAttribute(AttributeKind::TexCoords, buffer{
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f
        })
        .withElements({
            0, 1, 2,
            2, 3, 0
        });

    _ctx.getQueue().addCommand("sprite:puppy")
        .withAttribute(AttributeKind::Position, buffer{
            -0.25f,  0.25f,
             0.75f,  0.25f,
             0.75f, -0.75f,
            -0.25f, -0.75f
        })
        .withAttribute(AttributeKind::TexCoords, buffer{
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f
        })
        .withElements({
            0, 1, 2,
            2, 3, 0
        });

    _ctx.getQueue().draw();
}
