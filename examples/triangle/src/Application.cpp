#include <gorn/gorn.hpp>
#include <cmath>

namespace gorn
{
	Context _ctx;
    VertexArray _vao;
    float time;

	Application::Application()
	{
	}

	void Application::load()
	{
#ifdef GORN_PLATFORM_LINUX
		_ctx.getFiles()
            .addDefaultLoader<LocalFileLoader>("../assets/%s");
#elif GORN_PLATFORM_ANDROID
		_ctx.getFiles()
            .addDefaultLoader<AssetFileLoader>("%s");

#endif

        _vao.setProgram(_ctx.getPrograms().load("shader"));

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
        _vao.getProgram()->setUniformValue("timeSin", sinf(time));
		_vao.draw(3);
	}

}
