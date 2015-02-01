
#include <gorn/gorn.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

namespace gorn
{
	Context _ctx;
    VertexArray _vao;
    float time;

	Application::Application()
	{
	}

    glm::mat4 getTransform(float angle)
    {
        return glm::rotate(glm::mat4(),
            glm::pi<float>()*angle,
            glm::vec3(0,0,1));
    }

	void Application::load()
	{

#ifdef GORN_PLATFORM_LINUX
		_ctx.getFiles()
            .addLoader<LocalFileLoader>("fsh", "../assets/%s.fsh");
		_ctx.getFiles()
            .addLoader<LocalFileLoader>("vsh", "../assets/%s.vsh");
		_ctx.getFiles()
            .addLoader<LocalFileLoader>("tex", "../assets/%s.png");
		_ctx.getImages()
            .addDefaultDataLoader<PngImageLoader>();
#elif GORN_PLATFORM_ANDROID
		_ctx.getFiles()
            .addLoader<AssetFileLoader>("fsh", "%s.fsh");
		_ctx.getFiles()
            .addLoader<AssetFileLoader>("vsh", "%s.vsh");
		_ctx.getFiles()
            .addLoader<AssetFileLoader>("tex", "%s.png");
		_ctx.getImages()
            .addDefaultDataLoader<GraphicsImageLoader>();
#endif

	    _ctx.getPrograms().getDefinitions().get("shader")
            .withShaderFile(ShaderType::Vertex, "vsh:shader")
            .withShaderFile(ShaderType::Fragment, "fsh:shader")
            .withUniform("transform", UniformKind::Transform)
            .withUniform("texture", UniformKind::Texture0)
            .withUniformValue(UniformKind::Transform, getTransform(0.25f));

        _ctx.getMaterials().getDefinitions().get("kitten")
            .withProgram("shader")
            .withTexture(UniformKind::Texture0, "tex:kitten");            

        _vao.setMaterial(_ctx.getMaterials().load("kitten"));

        auto vbo = std::make_shared<VertexBuffer>(Data{
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
            .withStride(7*getSize(BasicType::Float));
        vdef.setAttribute("color")
            .withType(BasicType::Float)
            .withCount(3)
            .withStride(7*getSize(BasicType::Float))
            .withOffset(2*getSize(BasicType::Float));
        vdef.setAttribute("texCoords")
            .withType(BasicType::Float)
            .withCount(2)
            .withStride(7*getSize(BasicType::Float))
            .withOffset(5*getSize(BasicType::Float));

        _vao.addVertexData(vbo, vdef);

        vbo =  std::make_shared<VertexBuffer>(Data{
            0, 1, 2,
            2, 3, 0
        }, VertexBuffer::Usage::StaticDraw,
        VertexBuffer::Target::ElementArrayBuffer);

        _vao.setElementData(vbo);
	}

	void Application::background()
	{
	}

    void Application::foreground()
    {
    }

	void Application::unload()
	{
	}

	void Application::update(double dt)
	{
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        time += dt;
        _vao.getMaterial()->setUniformValue(
            UniformKind::Transform, getTransform(time));
		_vao.draw(6);
	}

}
