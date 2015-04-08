#ifndef __gorn__FrameBuffer__
#define __gorn__FrameBuffer__

#include <gorn/render/Gl.hpp>
#include <gorn/render/Texture.hpp>
#include <gorn/render/RenderBuffer.hpp>
#include <memory>

namespace gorn
{

	class FrameBuffer
	{
    private:
		static GLuint s_currentId;
		mutable GLuint _id;
        std::shared_ptr<Texture> _texture;
        std::shared_ptr<RenderBuffer> _render;

        void cleanup();
        static void bindId(GLuint id);
	public:
		FrameBuffer();
		~FrameBuffer();

        FrameBuffer(const FrameBuffer& other) = delete;
        FrameBuffer& operator=(const FrameBuffer& other) = delete;

        FrameBuffer(FrameBuffer&& other);
        FrameBuffer& operator=(FrameBuffer&& other);

        void setTexture(const std::shared_ptr<Texture>& texture);
        void setRenderBuffer(const std::shared_ptr<RenderBuffer>& buffer);

        void bind() const;
        static void unbind();
        void activate();
		GLuint getId() const;
    };
}

#endif
