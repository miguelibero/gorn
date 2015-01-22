
#include <gorn/gorn.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

namespace gorn
{
	RenderContext _render;
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
		_render.getFiles()
            .addLoader<LocalFileLoader>("fsh", "../%s.fsh");
		_render.getFiles()
            .addLoader<LocalFileLoader>("vsh", "../%s.vsh");
		_render.getFiles()
            .addLoader<LocalFileLoader>("tex", "../%s.png");
		_render.getImages()
            .addDefaultLoader<PngImageLoader>();
#elif GORN_PLATFORM_ANDROID
		_render.getFiles()
            .addLoader<BundleFileLoader>("fsh", "%s.fsh");
		_render.getFiles()
            .addLoader<BundleFileLoader>("vsh", "%s.vsh");
		_render.getFiles()
            .addLoader<BundleFileLoader>("tex", "%s.png");
		_render.getImages()
            .addDefaultLoader<GraphicsImageLoader>();
#endif

	    _render.getPrograms().getDefinitions().get("shader")
            .withShaderFile(ShaderType::Vertex, "vsh:shader")
            .withShaderFile(ShaderType::Fragment, "fsh:shader")
            .withUniform("transform", UniformKind::Transform)
            .withUniform("texture", UniformKind::Texture0)
            .withUniformValue(UniformKind::Transform, getTransform(0.25f));

        _render.getMaterials().getDefinitions().get("kitten")
            .withProgram("shader")
            .withTexture(UniformKind::Texture0, "tex:kitten");            

        _vao.setMaterial(_render.getMaterials().load("kitten"));

        auto vbo = std::make_shared<VertexBuffer>(Data{
         //  Position     Color             texCoords
            -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Top-left
             0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Top-right
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // Bottom-right
            -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f  // Bottom-left
        }, VertexBuffer::Usage::StaticDraw);

        VertexDefinition vdef;
        vdef.setAttribute("position")
            .withType(GL_FLOAT)
            .withCount(2)
            .withStride(7*sizeof(GLfloat));
        vdef.setAttribute("color")
            .withType(GL_FLOAT)
            .withCount(3)
            .withStride(7*sizeof(GLfloat))
            .withOffset(2*sizeof(GLfloat));
        vdef.setAttribute("texCoords")
            .withType(GL_FLOAT)
            .withCount(2)
            .withStride(7*sizeof(GLfloat))
            .withOffset(5*sizeof(GLfloat));

        _vao.addVertexData(vbo, vdef);

        vbo =  std::make_shared<VertexBuffer>(Data{
            0, 1, 2,
            2, 3, 0
        }, VertexBuffer::Usage::StaticDraw,
        VertexBuffer::Target::ElementArrayBuffer);

        _vao.setElementData(vbo);
	}

	void Application::unload()
	{
	}

	void Application::update(double dt)
	{
        time += dt;
        _vao.getMaterial()->setUniformValue(
            UniformKind::Transform, getTransform(time));
		_vao.draw(6);
	}

}
