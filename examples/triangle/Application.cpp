#include <gorn/base/Application.hpp>
#include <gorn/platform/PlatformBridge.hpp>
#include <gorn/render/RenderContext.hpp>
#include <gorn/render/ProgramDefinition.hpp>
#include <gorn/render/VertexBuffer.hpp>
#include <gorn/render/VertexArray.hpp>
#include <gorn/render/AttributeBinding.hpp>
#include <cmath>

#ifdef GORN_PLATFORM_LINUX
#include <gorn/platform/linux/LocalFileLoader.hpp>
#endif

namespace gorn
{
	PlatformBridge _bridge;
	RenderContext _render;
    VertexArray _vao;
    VertexBuffer _vbo;
    std::shared_ptr<Program> _prog;
    GLuint _timeUniform;
    float time;

	Application::Application()
	{
	}

	void Application::load()
	{
#ifdef GORN_PLATFORM_LINUX
		_bridge.addFileLoader("fsh", std::unique_ptr<FileLoader>(
            new LocalFileLoader("../%s.fsh")));
		_bridge.addFileLoader("vsh", std::unique_ptr<FileLoader>(
            new LocalFileLoader("../%s.vsh")));

#endif

		_render.setPlatformBridge(_bridge);
	    _render.defineProgram("shader");

        _prog = _render.loadProgram("shader");
        _timeUniform = _prog->getUniform("timeSin");

        _vbo.setData({
         //  Position     Color 
             0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
        }, VertexBuffer::Usage::StaticDraw);

        _vao.bindAttribute(_vbo, *_prog)
            .withAttribute("position")
            .withType(GL_FLOAT)
            .withSize(2)
            .withStride(5*sizeof(GLfloat))
            .finish();
        _vao.bindAttribute(_vbo, *_prog)
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
        _prog->setUniform(_timeUniform, sinf(time));
		_render.drawArrays(_vao, 3);
	}

}
