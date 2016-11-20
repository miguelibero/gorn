
#include <gorn/gorn.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

using namespace gorn;

class StencilApplication : public gorn::Application
{
    gorn::Context _ctx;
    gorn::VertexArray _vao;
    double _time;

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

#if GORN_PLATFORM_LINUX || GORN_PLATFORM_WINDOWS
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
		.withUniform(UniformKind("texture", UniformType::DiffuseTexture))
		.withUniform(ProgramUniformDefinition(
			UniformKind("proj", UniformType::ProjectionTransform), proj))
		.withUniform(ProgramUniformDefinition(
			UniformKind("view", UniformType::ViewTransform), view))
		.withUniform(ProgramUniformDefinition(
			UniformKind("model", UniformType::ModelTransform), view))
		.withUniform(ProgramUniformDefinition(
			UniformKind("overrideColor", UniformType::Color), glm::vec3(1.0f, 1.0f, 1.0f)))
		.withAttribute(ProgramAttributeDefinition(
			AttributeKind("position", AttributeType::Position))
			.withCount(3)
			.withBasicType(BasicType::Float));

    _ctx.getMaterials().getDefinitions().get("kitten")
        .withProgram("shader")
        .withTexture(UniformType::DiffuseTexture, "kitten.png");            

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
        .withBasicType(BasicType::Float)
        .withCount(3)
        .withStride(8, BasicType::Float);
    vdef.setAttribute("color")
        .withBasicType(BasicType::Float)
        .withCount(3)
        .withStride(8, BasicType::Float)
        .withOffset(3, BasicType::Float);
    vdef.setAttribute("texCoords")
        .withBasicType(BasicType::Float)
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
    ClearAction()
        .withColor(glm::vec4(1.0f))
        .withType(ClearType::Color)
        .withType(ClearType::Depth)
        .withType(ClearType::Stencil)
        .apply();

    _vao.getMaterial()->setUniformValue(
        UniformType::Color, glm::vec3(1.0f, 1.0f, 1.0f));

    auto model = getTransform((float)_time);

    _vao.getMaterial()->setUniformValue(
        UniformType::ModelTransform, model);
    _vao.draw(36);

    Capabilities()
        .with(CapabilityType::StencilTest, true)
        .with(CapabilityType::DepthTest, false)
        .apply();

    Stencil()
        .withFunction(StencilFunction::Always)
        .withReferenceValue(1)
        .withFailAction(StencilAction::Keep)
        .withPassAction(StencilAction::Replace)
        .withMask(0xFF)
        .apply();

    ClearAction()
        .withType(ClearType::Stencil)
        .apply();

    _vao.draw(6, 36);

    Stencil()
        .withFunction(StencilFunction::Equal)
        .withReferenceValue(1)
        .withMask(0x00)
        .apply();

	Capabilities()
        .with(CapabilityType::DepthTest, true)
        .apply();

    _vao.getMaterial()->setUniformValue(
        UniformType::Color, glm::vec3(0.3f, 0.3f, 0.3f));

    model = glm::scale(glm::translate(model,
        glm::vec3(0.0f, 0.0f, -1.0f)),
        glm::vec3(1.0f, 1.0f, -1.0f));
    _vao.getMaterial()->setUniformValue(
        UniformType::ModelTransform, model);

    _vao.draw(36);

	Capabilities()
        .with(CapabilityType::StencilTest, false)
        .apply();
}

