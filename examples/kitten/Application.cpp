
#include <gorn/gorn.hpp>
#include <glm/gtx/transform.hpp>

namespace gorn
{
	RenderContext _render;
    VertexArray _vao;
    float time;

	Application::Application()
	{
	}

	void Application::load()
	{

#ifdef GORN_PLATFORM_LINUX
		_render.getFileManager()
            ->addLoader<LocalFileLoader>("fsh", "../%s.fsh");
		_render.getFileManager()
            ->addLoader<LocalFileLoader>("vsh", "../%s.vsh");
		_render.getFileManager()
            ->addLoader<LocalFileLoader>("tex", "../%s.png");
		_render.getImageManager()
            ->addLoader<PngImageLoader>();
#elif GORN_PLATFORM_ANDROID
		_render.getFileManager()
            ->addLoader<BundleFileLoader>("fsh", "%s.fsh");
		_render.getFileManager()
            ->addLoader<BundleFileLoader>("vsh", "%s.vsh");
		_render.getFileManager()
            ->addLoader<BundleFileLoader>("tex", "%s.png");
		_render.getImageManager()
            ->addLoader<GraphicsImageLoader>();
#endif

	    _render.defineProgram("shader")
            .withUniforms({"transform"});
        _render.defineMaterial("kitten")
            .withProgram("shader")
            .withTexture("texture", "kitten");

        _vao.bindMaterial(_render.loadMaterial("kitten"));

        auto vbo = std::make_shared<VertexBuffer>(Data{
         //  Position     Color             texCoords
            -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Top-left
             0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Top-right
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // Bottom-right
            -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f  // Bottom-left
        }, VertexBuffer::Usage::StaticDraw);

        VertexDefinition vdef;
        vdef.defineAttribute("position")
            .withType(GL_FLOAT)
            .withSize(2)
            .withStride(7*sizeof(GLfloat));
        vdef.defineAttribute("color")
            .withType(GL_FLOAT)
            .withSize(3)
            .withStride(7*sizeof(GLfloat))
            .withOffset(2*sizeof(GLfloat));
        vdef.defineAttribute("texCoords")
            .withType(GL_FLOAT)
            .withSize(2)
            .withStride(7*sizeof(GLfloat))
            .withOffset(5*sizeof(GLfloat));

        _vao.bindData(vdef, vbo);

        vbo =  std::make_shared<VertexBuffer>(Data{
            0, 1, 2,
            2, 3, 0
        }, VertexBuffer::Usage::StaticDraw,
        VertexBuffer::Target::ElementArrayBuffer);

        _vao.bindData(vbo);
	}

	void Application::unload()
	{
	}

	void Application::update(double dt)
	{
        time += dt;
        auto transform = glm::rotate(glm::mat4(), time, glm::vec3(0,0,1));
        _vao.getProgram()->setUniform("transform", transform);
		_render.drawElements(_vao, 6, GL_UNSIGNED_INT);
	}

}
