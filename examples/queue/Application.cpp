
#include <gorn/gorn.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/constants.hpp>

namespace gorn
{
	RenderContext _render;

	Application::Application()
	{
	}

	void Application::load()
	{
        _render.basicSetup();

	    _render.getPrograms().define("shader")
            .withShaderFile(ShaderType::Vertex, "shader.vsh")
            .withShaderFile(ShaderType::Fragment, "shader.fsh");
        _render.getMaterials().define("kitten")
            .withProgram("shader")
            .withTexture("texture", "kitten.png");
        _render.getMaterials().define("puppy")
            .withProgram("shader")
            .withTexture("texture", "puppy.png");

        _render.getVertexDefinitions().preload("vdef")
            .withAttribute(AttributeDefinition()
                .withName("position")
                .withType(GL_FLOAT)
                .withSize(2)
                .withStride(4*sizeof(GLfloat)))
            .withAttribute(AttributeDefinition()
                .withName("texCoords")
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

        _render.getQueue().addCommand("vdef", "kitten")
            .withVertexData({
                //  Position  texCoords
                -0.75f,  0.75f, 0.0f, 1.0f, // Top-left
                 0.25f,  0.75f, 1.0f, 1.0f, // Top-right
                 0.25f, -0.25f, 1.0f, 0.0f, // Bottom-right
                -0.75f, -0.25f, 0.0f, 0.0f  // Bottom-left
            })
            .withElementData({
                0, 1, 2,
                2, 3, 0
            }, GL_UNSIGNED_INT)
            .withElementCount(6);

        _render.getQueue().addCommand("vdef", "puppy")
            .withVertexData({
                //  Position  texCoords
                -0.25f,  0.25f, 0.0f, 1.0f, // Top-left
                 0.75f,  0.25f, 1.0f, 1.0f, // Top-right
                 0.75f, -0.75f, 1.0f, 0.0f, // Bottom-right
                -0.25f, -0.75f, 0.0f, 0.0f  // Bottom-left
            })
            .withElementData({
                0, 1, 2,
                2, 3, 0
            }, GL_UNSIGNED_INT)
            .withElementCount(6);

		_render.getQueue().draw();
	}

}
