
#include <gorn/gorn.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

using namespace gorn;

class KittenApplication : public gorn::Application
{
	gorn::Context _ctx;
    gorn::VertexArray _vao;
    float _time;

    glm::mat4 getTransform(float angle);

public:

    KittenApplication();

    void load() override;
    void update(double dt) override;
    void draw() override;
};


namespace gorn
{
    std::unique_ptr<Application> main()
    {
        return std::unique_ptr<Application>(new KittenApplication());
    }
}

KittenApplication::KittenApplication():
_time(0.0f)
{
}

glm::mat4 KittenApplication::getTransform(float angle)
{
    return glm::rotate(glm::mat4(),
        glm::pi<float>()*angle,
        glm::vec3(0.0f, 0.0f , 1.0f));
}

void KittenApplication::load()
{

#ifdef GORN_PLATFORM_LINUX
	_ctx.getFiles()
        .makeLoader<LocalFileLoader>("fsh", "../assets/%s.fsh");
	_ctx.getFiles()
        .makeLoader<LocalFileLoader>("vsh", "../assets/%s.vsh");
	_ctx.getFiles()
        .makeLoader<LocalFileLoader>("tex", "../assets/%s.png");
#elif GORN_PLATFORM_ANDROID
	_ctx.getFiles()
        .makeLoader<AssetFileLoader>("fsh", "%s.fsh");
	_ctx.getFiles()
        .makeLoader<AssetFileLoader>("vsh", "%s.vsh");
	_ctx.getFiles()
        .makeLoader<AssetFileLoader>("tex", "%s.png");
#endif

	_ctx.getImages()
        .makeDefaultDataLoader<StbImageLoader>();

    _ctx.getPrograms().getDefinitions().get("shader")
        .withShaderFile(ShaderType::Vertex, "vsh:shader")
        .withShaderFile(ShaderType::Fragment, "fsh:shader")
        .withUniform(UniformKind::Texture0, "texture")
        .withUniform(UniformKind::Model, ProgramUniformDefinition(
            "transform", getTransform(0.25f)));

    _ctx.getMaterials().getDefinitions().get("kitten")
        .withProgram("shader")
        .withTexture(UniformKind::Texture0, "tex:kitten");            

    _vao.setMaterial(_ctx.getMaterials().load("kitten"));

    auto vbo = std::make_shared<VertexBuffer>(buffer{
     //  Position     Color             texCoords
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Top-left
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Top-right
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // Bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f  // Bottom-left
    }, VertexBuffer::Usage::StaticDraw);

    VertexDefinition vdef;
    vdef.setAttribute("position")
        .withType(BasicType::Float)
        .withCount(2)
        .withStride(7, BasicType::Float);
    vdef.setAttribute("color")
        .withType(BasicType::Float)
        .withCount(3)
        .withStride(7, BasicType::Float)
        .withOffset(2, BasicType::Float);
    vdef.setAttribute("texCoords")
        .withType(BasicType::Float)
        .withCount(2)
        .withStride(7, BasicType::Float)
        .withOffset(5, BasicType::Float);

    _vao.addVertexData(vbo, vdef);

    vbo =  std::make_shared<VertexBuffer>(buffer{
        0, 1, 2,
        2, 3, 0
    }, VertexBuffer::Usage::StaticDraw,
    VertexBuffer::Target::ElementArrayBuffer);

    _vao.setElementData(vbo);
}

void KittenApplication::update(double dt)
{
    _time += dt;
}

void KittenApplication::draw()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    _vao.getMaterial()->setUniformValue(
        UniformKind::Model, getTransform(_time));
	_vao.draw(6);
}

