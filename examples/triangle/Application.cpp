#include <gorn/base/Application.hpp>
#include <gorn/platform/PlatformBridge.hpp>
#include <gorn/render/Renderer.hpp>
#include <gorn/render/ProgramDefinition.hpp>
#include <gorn/render/VertexBuffer.hpp>
#include <gorn/render/VertexArray.hpp>
#include <gorn/render/AttributeBinding.hpp>

#ifdef GORN_PLATFORM_LINUX
#include <gorn/platform/linux/LocalFileLoader.hpp>
#endif

namespace gorn
{
	PlatformBridge _bridge;
	Renderer _renderer;
    VertexArray _vao;

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

		_renderer.setPlatformBridge(_bridge);
	    _renderer.defineProgram("shader");

        auto prog = _renderer.loadProgram("shader");

        VertexBuffer vbo({
             0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
            -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
        }, VertexBufferUsage::StaticDraw);

        _vao.bindAttribute(vbo, *prog)
            .setAttribute("position")
            .setType(GL_FLOAT)
            .setSize(5*sizeof(float))
            .create();
        _vao.bindAttribute(vbo, *prog)
            .setAttribute("color")
            .setType(GL_FLOAT)
            .setSize(3)
            .setStride(5*sizeof(float))
            .setOffset(2*sizeof(float))
            .create();
	}

	void Application::unload()
	{   
	}

	void Application::update(double dt)
	{
		_renderer.drawArrays(_vao, 3);
	}

}
