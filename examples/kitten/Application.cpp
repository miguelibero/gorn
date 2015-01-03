
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
		_render.getFileManager()
            .addLoader<LocalFileLoader>("fsh", "../%s.fsh");
		_render.getFileManager()
            .addLoader<LocalFileLoader>("vsh", "../%s.vsh");
		_render.getFileManager()
            .addLoader<LocalFileLoader>("tex", "../%s.png");
		_render.getImageManager()
            .addLoader<PngImageLoader>();
#elif GORN_PLATFORM_ANDROID
		_render.getFileManager()
            .addLoader<BundleFileLoader>("fsh", "%s.fsh");
		_render.getFileManager()
            .addLoader<BundleFileLoader>("vsh", "%s.vsh");
		_render.getFileManager()
            .addLoader<BundleFileLoader>("tex", "%s.png");
		_render.getImageManager()
            .addLoader<GraphicsImageLoader>();
#endif

	    _render.getPrograms().define("shader")
            .withUniforms({"transform"});

        _render.getMaterials().define("kitten")
            .withProgram("shader")
            .withTexture("texture", "kitten")
            .withUniformValue("transform", getTransform(0.25f));

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
            .withSize(2)
            .withStride(7*sizeof(GLfloat));
        vdef.setAttribute("color")
            .withType(GL_FLOAT)
            .withSize(3)
            .withStride(7*sizeof(GLfloat))
            .withOffset(2*sizeof(GLfloat));
        vdef.setAttribute("texCoords")
            .withType(GL_FLOAT)
            .withSize(2)
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
        _vao.getMaterial()->setUniformValue("transform", getTransform(time));
		_vao.draw(6);
	}

}
