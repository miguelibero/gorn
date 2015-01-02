#include <gorn/base/Application.hpp>
#include <gorn/platform/PlatformBridge.hpp>
#include <gorn/render/RenderContext.hpp>
#include <gorn/render/MaterialDefinition.hpp>
#include <gorn/render/VertexBuffer.hpp>
#include <gorn/render/VertexArray.hpp>
#include <gorn/render/VertexDefinition.hpp>
#include <cmath>

#ifdef GORN_PLATFORM_LINUX
#include <gorn/platform/linux/LocalFileLoader.hpp>
#include <gorn/platform/linux/PngImageLoader.hpp>
#endif

namespace gorn
{
	PlatformBridge _bridge;
	RenderContext _render;
    VertexArray _vao;
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
		_bridge.addFileLoader("tex", std::unique_ptr<FileLoader>(
            new LocalFileLoader("../%s.png")));
		_bridge.addImageLoader(std::unique_ptr<ImageLoader>(
            new PngImageLoader()));
#endif

		_render.setPlatformBridge(_bridge);
	    _render.defineProgram("shader")
            .withUniforms({"timeSin"});
        _render.defineMaterial("kitten")
            .withProgram("shader")
            .withTexture("texture", "kitten");

        _vao.bindMaterial(_render.loadMaterial("kitten"));

        auto vbo = std::make_shared<VertexBuffer>(Data{
         //  Position     Color             Texcoords
            -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
             0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Top-right
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
            -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
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
        _vao.getProgram()->setUniform("timeSin", sinf(time));
		_render.drawElements(_vao, 6, GL_UNSIGNED_INT);
	}

}
