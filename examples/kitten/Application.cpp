#include <gorn/base/Application.hpp>
#include <gorn/platform/PlatformBridge.hpp>
#include <gorn/render/RenderContext.hpp>
#include <gorn/render/MaterialDefinition.hpp>
#include <gorn/render/VertexBuffer.hpp>
#include <gorn/render/VertexArray.hpp>
#include <gorn/render/VertexDefinition.hpp>
#include <glm/gtx/transform.hpp>

#ifdef GORN_PLATFORM_LINUX
#include <gorn/platform/linux/LocalFileLoader.hpp>
#include <gorn/platform/linux/PngImageLoader.hpp>
#elif GORN_PLATFORM_ANDROID
#include <gorn/platform/android/BundleFileLoader.hpp>
#include <gorn/platform/android/GraphicsImageLoader.hpp>
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
#elif GORN_PLATFORM_ANDROID
		_bridge.addFileLoader("fsh", std::unique_ptr<FileLoader>(
            new BundleFileLoader("%s.fsh")));
		_bridge.addFileLoader("vsh", std::unique_ptr<FileLoader>(
            new BundleFileLoader("%s.vsh")));
		_bridge.addFileLoader("tex", std::unique_ptr<FileLoader>(
            new BundleFileLoader("%s.png")));
		_bridge.addImageLoader(std::unique_ptr<ImageLoader>(
            new GraphicsImageLoader()));
#endif

		_render.setPlatformBridge(_bridge);
	    _render.defineProgram("shader")
            .withUniforms({"timeSin"});
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
