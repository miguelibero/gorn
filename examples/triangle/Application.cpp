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
		_render.getFileManager()
            ->addLoader<LocalFileLoader>("fsh", "../%s.fsh");
		_render.getFileManager()
            ->addLoader<LocalFileLoader>("vsh", "../%s.vsh");
#elif GORN_PLATFORM_ANDROID
		_render.getFileManager()
            ->addLoader<BundleFileLoader>("fsh", "%s.fsh");
		_render.getFileManager()
            ->addLoader<BundleFileLoader>("vsh", "%s.vsh");
#endif

        _vao.bindProgram(_render.loadProgram("shader"));

        auto vbo = std::make_shared<VertexBuffer>(Data{
         //  Position     Color 
             0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
        }, VertexBuffer::Usage::StaticDraw);

        
        _vao.bindAttribute(vbo)
            .withAttribute("position")
            .withType(GL_FLOAT)
            .withSize(2)
            .withStride(5*sizeof(GLfloat))
            .finish();
        _vao.bindAttribute(vbo)
            .withAttribute("color")
            .withType(GL_FLOAT)
            .withSize(3)
            .withStride(5*sizeof(GLfloat))
            .withOffset(2*sizeof(GLfloat))
            .finish();
	}

	void Application::unload()
	{   
	}

	void Application::update(double dt)
	{
        time += dt;
        _vao.getProgram()->setUniform("timeSin", sinf(time));
		_render.drawArrays(_vao, 3);
	}

}
