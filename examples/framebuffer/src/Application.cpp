
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
    float _time;

public:

    FramebufferApplication();

    void load() override;
    void update(double dt) override;
    void draw() override;
};


namespace gorn
{
    std::unique_ptr<Application> main()
    {
        return std::unique_ptr<Application>(new FramebufferApplication());
    }
}

FramebufferApplication::FramebufferApplication():
_time(0.0f)
{
}


void FramebufferApplication::load()
{

#if GORN_PLATFORM_LINUX || GORN_PLATFORM_WINDOWS
    _ctx.getFiles()
        .makeDefaultLoader<LocalFileLoader>("../assets/%s");
#elif GORN_PLATFORM_ANDROID
    _ctx.getFiles()
        .makeDefaultLoader<AssetFileLoader>("%s");
#endif
    _ctx.getImages()
        .makeDefaultDataLoader<StbImageLoader>();

    _ctx.getMaterials().getDefinitions().get("kitten")
        .withProgram("sprite")
        .withTexture(UniformKind::Texture0, "kitten.png");

    _ctx.getMaterials().getDefinitions().set("glass",
        MaterialDefinition().withProgram("glass"));

    _ctx.getPrograms().getDefinitions().get("glass")
        .withShaderFile(gorn::ShaderType::Vertex, "sprite.vsh")
        .withShaderFile(gorn::ShaderType::Fragment, "glass.fsh");

    _vao1.setMaterial(_ctx.getMaterials().load("kitten"));
    _vao2.setMaterial(_ctx.getMaterials().load("glass"));

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
        -0.5f,  0.5f, 0.0f, 1.0f, // Top-left
         0.5f,  0.5f, 1.0f, 1.0f, // Top-right
         0.5f, -0.5f, 1.0f, 0.0f, // Bottom-right
        -0.5f, -0.5f, 0.0f, 0.0f  // Bottom-left
    }, VertexBuffer::Usage::StaticDraw);
    _vao1.addVertexData(vbo, vdef);

    vbo = std::make_shared<VertexBuffer>(buffer{
     //  Position     texCoords
        -1.0f,  1.0f, 0.0f, 1.0f, // Top-left
         1.0f,  1.0f, 1.0f, 1.0f, // Top-right
         1.0f, -1.0f, 1.0f, 0.0f, // Bottom-right
        -1.0f, -1.0f, 0.0f, 0.0f  // Bottom-left
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
    fbtex->setImage(Image(getSize()));
    _fbo.attach(fbtex);
    _vao2.getMaterial()->setTexture(UniformKind::Texture0, fbtex);
}

void FramebufferApplication::update(double dt)
{
    _time += dt;
}

void FramebufferApplication::draw()
{
    _fbo.activate();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    _vao1.draw(6);
    _fbo.unbind();

    _vao2.getProgram()->setUniformValue("time", _time);
    _vao2.draw(6);
}

