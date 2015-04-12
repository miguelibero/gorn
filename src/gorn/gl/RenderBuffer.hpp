#ifndef __gorn__RenderBuffer__
#define __gorn__RenderBuffer__

#include <gorn/gl/GlBase.hpp>
#include <gorn/gl/GlEnums.hpp>
#include <glm/glm.hpp>

namespace gorn
{
	class RenderBuffer
	{
    public:
        typedef FrameBufferAttachType Type;
    private:
		static GLuint s_currentId;
		mutable GLuint _id;
        glm::vec2 _size;
        GLenum _format;
        Type _type;

        void cleanup();
        static void bindId(GLuint id);
        static GLenum getTypeFormat(Type type);
	public:
		RenderBuffer(const glm::vec2& size, Type type=Type::Depth);
		~RenderBuffer();

        RenderBuffer(const RenderBuffer& other) = delete;
        RenderBuffer& operator=(const RenderBuffer& other) = delete;

        RenderBuffer(RenderBuffer&& other);
        RenderBuffer& operator=(RenderBuffer&& other);

        void bind() const;
        static void unbind();
		GLuint getId() const;
        Type getType() const;

        void setParameter(GLenum param, int value);
        void attachToFrameBuffer(GLenum type);
    };
}

#endif
