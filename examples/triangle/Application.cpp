#include <gorn/gorn.hpp>
#include <cmath>

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
		_render.getFiles()
            .addLoader<LocalFileLoader>("fsh", "../%s.fsh");
		_render.getFiles()
            .addLoader<LocalFileLoader>("vsh", "../%s.vsh");
#elif GORN_PLATFORM_ANDROID
		_render.getFiles()
            .addLoader<BundleFileLoader>("fsh", "%s.fsh");
		_render.getFiles()
            .addLoader<BundleFileLoader>("vsh", "%s.vsh");
#endif

        _vao.setProgram(_render.getPrograms().load("shader"));

        auto vbo = std::make_shared<VertexBuffer>(Data{
         //  Position     Color 
             0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
        }, VertexBuffer::Usage::StaticDraw);

        _vao.setAttribute(vbo, AttributeDefinition("position")
            .withType(GL_FLOAT)
            .withCount(2)
            .withStride(5*sizeof(GLfloat)));
            
        _vao.setAttribute(vbo, AttributeDefinition("color")
            .withType(GL_FLOAT)
            .withCount(3)
            .withStride(5*sizeof(GLfloat))
            .withOffset(2*sizeof(GLfloat)));
	}

	void Application::unload()
	{   
	}

	void Application::update(double dt)
	{
        time += dt;
        _vao.getProgram()->setUniformValue("timeSin", sinf(time));
		_vao.draw(3);
	}

}
