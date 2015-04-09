#ifndef __gorn__VertexBuffer__
#define __gorn__VertexBuffer__

#include <gorn/render/Gl.hpp>
#include <map>

class buffer;

namespace gorn
{
    enum class VertexBufferUsage
    {
		StreamDraw,
		StaticDraw,
		DynamicDraw,
    };

    enum class VertexBufferTarget
    {
        ElementArrayBuffer,
        ArrayBuffer
    };

	class VertexBuffer
	{
	public:
        typedef VertexBufferUsage Usage;
        typedef VertexBufferTarget Target;
	private:
		mutable GLuint _id;
        Target _target;
        size_t _size;

        void cleanup();
        static void bindId(GLuint id, GLenum target);
	public:
		VertexBuffer(const buffer& data,
            Usage usage=Usage::DynamicDraw,
            Target target=Target::ArrayBuffer);
        VertexBuffer(Target target=Target::ArrayBuffer);
		~VertexBuffer();

        VertexBuffer(const VertexBuffer& other) = delete;
        VertexBuffer& operator=(const VertexBuffer& other) = delete;

        VertexBuffer(VertexBuffer&& other);
        VertexBuffer& operator=(VertexBuffer&& other);

		GLuint getId() const;
        void bind() const;
        void unbind() const;
        void setData(const buffer& data, Usage usage);
        void setSubData(const buffer& data, size_t offset);
        size_t getSize() const;
	};
}

#endif
