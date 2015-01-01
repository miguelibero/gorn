#ifndef __gorn__VertexBuffer__
#define __gorn__VertexBuffer__

#include <gorn/render/Gl.hpp>

namespace gorn
{
    enum class VertexBufferUsage
    {
		StreamDraw,
		StreamRead,
		StreamCopy,
		StaticDraw,
		StaticRead,
		StaticCopy,
		DynamicDraw,
		DynamicRead,
		DynamicCopy
    };

    enum class VertexBufferTarget
    {
        ArrayBuffer
    };

    class Data;

	class VertexBuffer
	{
	public:
        typedef VertexBufferUsage Usage;
        typedef VertexBufferTarget Target;
	private:
		mutable GLuint _id;
        Target _target;
	public:

		VertexBuffer(const Data& data,
            Usage usage=Usage::DynamicDraw,
            Target target=Target::ArrayBuffer);
        VertexBuffer(Target target=Target::ArrayBuffer);
		~VertexBuffer();
		GLuint getId() const;

        void bind() const;
        void setData(const Data& data, Usage usage);
        void setSubData(const Data& data, size_t offset);
        Data getSubData(size_t offset, size_t size) const;
	};
}

#endif
