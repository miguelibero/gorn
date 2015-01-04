
#include <gorn/gorn.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

namespace gorn
{
	RenderContext _render;
    VertexDefinition _vdef;

	Application::Application()
	{
	}

	void Application::load()
	{

#ifdef GORN_PLATFORM_LINUX
		_render.getFileManager()
            .addDefaultLoader<LocalFileLoader>("../%s");
		_render.getImageManager()
            .addLoader<PngImageLoader>();
#elif GORN_PLATFORM_ANDROID
		_render.getFileManager()
            .addDefaultLoader<BundleFileLoader>("%s");
		_render.getImageManager()
            .addLoader<GraphicsImageLoader>();
#endif

	    _render.getPrograms().define("shader")
            .withVertexShader("shader.vsh")
            .withFragmentShader("shader.fsh");
        _render.getMaterials().define("kitten")
            .withProgram("shader")
            .withTexture("texture", "kitten.png");
        _render.getMaterials().define("puppy")
            .withProgram("shader")
            .withTexture("texture", "puppy.png");

        _vdef = VertexDefinition()
            .withAttribute(AttributeDefinition("position")
                .withType(GL_FLOAT)
                .withSize(2)
                .withStride(4*sizeof(GLfloat)))
            .withAttribute(AttributeDefinition("texCoords")
                .withType(GL_FLOAT)
                .withSize(2)
                .withStride(4*sizeof(GLfloat))
                .withOffset(2*sizeof(GLfloat)));
	}

	void Application::unload()
	{
	}

	void Application::update(double dt)
	{

        _render.getQueue().addCommand()
            .withVertexData({
                //  Position  texCoords
                -0.75f,  0.75f, 0.0f, 1.0f, // Top-left
                 0.25f,  0.75f, 1.0f, 1.0f, // Top-right
                 0.25f, -0.25f, 1.0f, 0.0f, // Bottom-right
                -0.75f, -0.25f, 0.0f, 0.0f  // Bottom-left
            }, _vdef)
            .withElementData({
                0, 1, 2,
                2, 3, 0
            }, GL_UNSIGNED_INT)
            .withElementCount(6)
            .withMaterial(_render.getMaterials().load("kitten"));

        _render.getQueue().addCommand()
            .withVertexData({
                //  Position  texCoords
                -0.25f,  0.25f, 0.0f, 1.0f, // Top-left
                 0.75f,  0.25f, 1.0f, 1.0f, // Top-right
                 0.75f, -0.75f, 1.0f, 0.0f, // Bottom-right
                -0.25f, -0.75f, 0.0f, 0.0f  // Bottom-left
            }, _vdef)
            .withElementData({
                0, 1, 2,
                2, 3, 0
            }, GL_UNSIGNED_INT)
            .withElementCount(6)
            .withMaterial(_render.getMaterials().load("puppy"));

		_render.getQueue().draw();
	}

}
