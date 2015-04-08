
#include <gorn/gorn.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

using namespace gorn;

class FramebufferApplication : public gorn::Application
{
	gorn::Context _ctx;
    gorn::VertexArray _vao1;
    gorn::FrameBuffer _fbo;
    gorn::VertexArray _vao2;

public:

    FramebufferApplication();

    void load() override;
    void draw() override;
};


namespace gorn
{
    std::unique_ptr<Application> main()
    {
        return std::unique_ptr<Application>(new FramebufferApplication());
    }
}

FramebufferApplication::FramebufferApplication()
{
}


void FramebufferApplication::load()
{

#ifdef GORN_PLATFORM_LINUX
	_ctx.getFiles()
        .makeDefaultLoader<LocalFileLoader>("../assets/%s");
	_ctx.getImages()
        .makeDefaultDataLoader<PngImageLoader>();
#elif GORN_PLATFORM_ANDROID
	_ctx.getFiles()
        .makeDefaultLoader<AssetFileLoader>("%s");
	_ctx.getImages()
        .makeDefaultDataLoader<GraphicsImageLoader>();
#endif

    _ctx.getMaterials().getDefinitions().get("kitten")
        .withProgram("sprite")
        .withTexture(UniformKind::Texture0, "kitten.png");

    _ctx.getMaterials().getDefinitions().set("sepia",
        MaterialDefinition().withProgram("sepia"));

    _ctx.getPrograms().getDefinitions().get("sepia")
        .withShaderFile(gorn::ShaderType::Vertex, "sprite.vsh")
        .withShaderFile(gorn::ShaderType::Fragment, "sepia.fsh");

    _vao1.setMaterial(_ctx.getMaterials().load("kitten"));
    _vao2.setMaterial(_ctx.getMaterials().load("sepia"));

    VertexDefinition vdef;
    vdef.setAttribute("position")
        .withType(BasicType::Float)
        .withCount(2)
        .withStride(4, BasicType::Float);
    vdef.setAttribute("texCoords")
        .withType(BasicType::Float)
        .withCount(2)
        .withStride(4, BasicType::Float)
        .withOffset(2, BasicType::Float);

    auto vbo = std::make_shared<VertexBuffer>(buffer{
     //  Position     texCoords
        -0.5f,  0.5f, 0.0f, 0.0f, // Top-left
         0.5f,  0.5f, 1.0f, 0.0f, // Top-right
         0.5f, -0.5f, 1.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f, 0.0f, 1.0f  // Bottom-left
    }, VertexBuffer::Usage::StaticDraw);
    _vao1.addVertexData(vbo, vdef);

    vbo = std::make_shared<VertexBuffer>(buffer{
     //  Position     texCoords
        -1.0f,  1.0f, 0.0f, 0.0f, // Top-left
         1.0f,  1.0f, 1.0f, 0.0f, // Top-right
         1.0f, -1.0f, 1.0f, 1.0f, // Bottom-right
        -1.0f, -1.0f, 0.0f, 1.0f  // Bottom-left
    }, VertexBuffer::Usage::StaticDraw);
    _vao2.addVertexData(vbo, vdef);

    vbo = std::make_shared<VertexBuffer>(buffer{
        0, 1, 2,
        2, 3, 0
    }, VertexBuffer::Usage::StaticDraw,
    VertexBuffer::Target::ElementArrayBuffer);

    _vao1.setElementData(vbo);
    _vao2.setElementData(vbo);

    auto fbtex = std::make_shared<Texture>();
    fbtex->setImage(Image(glm::vec2(500)));
    //_fbo.setRenderBuffer(std::make_shared<RenderBuffer>(glm::vec2(256)));
    _fbo.setTexture(fbtex);
    _vao2.getMaterial()->setTexture(UniformKind::Texture0, fbtex);
}

void FramebufferApplication::draw()
{
    _fbo.activate();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
	_vao1.draw(6);
    _fbo.unbind();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    _vao2.draw(6);
}

