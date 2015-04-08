#ifndef __gorn__RenderBuffer__
#define __gorn__RenderBuffer__

#include <gorn/render/Gl.hpp>
#include <glm/glm.hpp>

namespace gorn
{

	class RenderBuffer
	{
    private:
		static GLuint s_currentId;
		mutable GLuint _id;
        glm::vec2 _size;
        GLenum _format;

        void cleanup();
        static void bindId(GLuint id);
	public:
		RenderBuffer(const glm::vec2& size, GLenum format=GL_RGBA);
		~RenderBuffer();

        RenderBuffer(const RenderBuffer& other) = delete;
        RenderBuffer& operator=(const RenderBuffer& other) = delete;

        RenderBuffer(RenderBuffer&& other);
        RenderBuffer& operator=(RenderBuffer&& other);

        void bind() const;
        static void unbind();
		GLuint getId() const;

        void setParameter(GLenum param, int value);
        void attachToFrameBufferAsColor(int pos);
        void attachToFrameBufferAsDepth();
    };
}

#endif
