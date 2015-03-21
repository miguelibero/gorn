
#include <gorn/gorn.hpp>

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
#ifdef GORN_PLATFORM_LINUX
	_ctx.getFiles()
        .makeLoader<LocalFileLoader>("sprite", "../assets/%s.png");
	_ctx.getFiles()
        .makeLoader<LocalFileLoader>("vsh", "../assets/%s.vsh");
	_ctx.getFiles()
        .makeLoader<LocalFileLoader>("fsh", "../assets/%s.fsh");
	_ctx.getImages()
        .makeDataLoader<PngImageLoader>("sprite");
#elif GORN_PLATFORM_WINDOWS
	_ctx.getFiles()
		.makeLoader<LocalFileLoader>("sprite", "../assets/%s.png");
	_ctx.getFiles()
		.makeLoader<LocalFileLoader>("vsh", "../assets/%s.vsh");
	_ctx.getFiles()
		.makeLoader<LocalFileLoader>("fsh", "../assets/%s.fsh");
	_ctx.getImages()
		.makeDataLoader<SOILImageLoader>("sprite");
#elif GORN_PLATFORM_ANDROID
	_ctx.getFiles()
        .makeLoader<AssetFileLoader>("sprite", "%s.png");
	_ctx.getFiles()
        .makeLoader<AssetFileLoader>("vsh", "%s.vsh");
	_ctx.getFiles()
        .makeLoader<AssetFileLoader>("fsh", "%s.fsh");
	_ctx.getImages()
        .makeDataLoader<GraphicsImageLoader>("sprite");
#endif

    _ctx.getMaterials().getDefinitions()
        .set("sprite", [](const std::string& name){
            return MaterialDefinition()
                .withProgram("sprite")
                .withTexture(UniformKind::Texture0, name);
        });

    _ctx.getPrograms().getDefinitions().get("sprite")
        .withUniform("texture", UniformKind::Texture0)
        .withShaderFile(ShaderType::Vertex, "vsh:shader")
        .withShaderFile(ShaderType::Fragment, "fsh:shader");
}

void QueueApplication::draw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    _ctx.getQueue().addCommand("sprite:kitten")
        .withAttribute(AttributeKind::Position, {
            -0.75f,  0.75f,
             0.25f,  0.75f,
             0.25f, -0.25f,
            -0.75f, -0.25f,
             0.66f
        }, 2, BasicType::Float)
        .withAttribute(AttributeKind::TexCoords, {
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f
        }, 2, BasicType::Float)
        .withElements({
            0, 1, 2,
            2, 3, 0
        }, BasicType::UnsignedInteger);

    _ctx.getQueue().addCommand("sprite:puppy")
        .withAttribute(AttributeKind::Position, {
            -0.25f,  0.25f,
             0.75f,  0.25f,
             0.75f, -0.75f,
            -0.25f, -0.75f
        }, 2, BasicType::Float)
        .withAttribute(AttributeKind::TexCoords, {
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f
        }, 2, BasicType::Float)
        .withElements({
            0, 1, 2,
            2, 3, 0
        }, BasicType::UnsignedInteger);

	_ctx.getQueue().draw();
}
