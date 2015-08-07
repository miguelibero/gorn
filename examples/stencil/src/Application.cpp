
#include <gorn/gorn.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

using namespace gorn;

class StencilApplication : public gorn::Application
{
	gorn::Context _ctx;
    gorn::VertexArray _vao;
    float _time;

    glm::mat4 getTransform(float angle);

public:

    StencilApplication();

    void load() override;
    void update(double dt) override;
    void draw() override;
};


namespace gorn
{
    std::unique_ptr<Application> main()
    {
        return std::unique_ptr<Application>(new StencilApplication());
    }
}

StencilApplication::StencilApplication()
{
}

glm::mat4 StencilApplication::getTransform(float angle)
{
    return glm::rotate(glm::mat4(),
        angle * glm::radians(180.0f),
        glm::vec3(0.0f, 0.0f , 1.0f));
}

void StencilApplication::load()
{

    glEnable(GL_DEPTH_TEST);

#ifdef GORN_PLATFORM_LINUX
	_ctx.getFiles()
        .makeDefaultLoader<LocalFileLoader>("../assets/%s");
#elif GORN_PLATFORM_ANDROID
	_ctx.getFiles()
        .makeDefaultLoader<AssetFileLoader>("%s");
#endif
	_ctx.getImages()
        .makeDefaultDataLoader<StbImageLoader>();

    auto view = glm::lookAt(
        glm::vec3(2.5f, 2.5f, 2.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );

    auto proj = glm::perspective(
            glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);

    _ctx.getPrograms().getDefinitions().get("shader")
        .withUniform(UniformKind::Texture0, "texture")
        .withUniform(UniformKind::Projection, ProgramUniformDefinition(
            "proj", proj))
        .withUniform(UniformKind::View, ProgramUniformDefinition(
            "view", view))
        .withUniform(UniformKind::Model, ProgramUniformDefinition(
            "model", view))
        .withUniform(UniformKind::Color, ProgramUniformDefinition(
            "overrideColor", glm::vec3(1.0f, 1.0f, 1.0f)));

    _ctx.getMaterials().getDefinitions().get("kitten")
        .withProgram("shader")
        .withTexture(UniformKind::Texture0, "kitten.png");            

    _vao.setMaterial(_ctx.getMaterials().load("kitten"));


    auto vbo = std::make_shared<VertexBuffer>(buffer{
     // Position            Color             texCoords
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,

        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        -1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
         1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
    }, VertexBuffer::Usage::StaticDraw);

    VertexDefinition vdef;
    vdef.setAttribute("position")
        .withType(BasicType::Float)
        .withCount(3)
        .withStride(8, BasicType::Float);
    vdef.setAttribute("color")
        .withType(BasicType::Float)
        .withCount(3)
        .withStride(8, BasicType::Float)
        .withOffset(3, BasicType::Float);
    vdef.setAttribute("texCoords")
        .withType(BasicType::Float)
        .withCount(2)
        .withStride(8, BasicType::Float)
        .withOffset(6, BasicType::Float);

    _vao.addVertexData(vbo, vdef);

    glClearStencil(0);
}

void StencilApplication::update(double dt)
{
    _time += dt;
}

void StencilApplication::draw()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    _vao.getMaterial()->setUniformValue(
        UniformKind::Color, glm::vec3(1.0f, 1.0f, 1.0f));

    auto model = getTransform(_time);

    _vao.getMaterial()->setUniformValue(
        UniformKind::Model, model);
	_vao.draw(36);

    glEnable(GL_STENCIL_TEST);

    auto stencil = Stencil()
        .withFunction(StencilFunction::Always)
        .withReferenceValue(1)
        .withFailAction(StencilAction::Keep)
        .withPassAction(StencilAction::Replace)
        .withMask(0xFF);

    stencil.apply();
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glDepthMask(GL_FALSE);

	_vao.draw(6, 36);

    stencil
        .withFunction(StencilFunction::Equal)
        .withMask(0x00);

    stencil.apply();
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);

    _vao.getMaterial()->setUniformValue(
        UniformKind::Color, glm::vec3(0.3f, 0.3f, 0.3f));

    model = glm::scale(glm::translate(model,
        glm::vec3(0.0f, 0.0f, -1.0f)),
        glm::vec3(1.0f, 1.0f, -1.0f));
    _vao.getMaterial()->setUniformValue(
        UniformKind::Model, model);

	_vao.draw(36);

    glDisable(GL_STENCIL_TEST);
}

