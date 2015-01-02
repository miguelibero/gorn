#ifndef __gorn__VertexBuffer__
#define __gorn__VertexBuffer__

#include <gorn/render/Gl.hpp>
#include <map>

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
        ElementArrayBuffer,
        ArrayBuffer
    };

    class Data;

	class VertexBuffer
	{
	public:
        typedef VertexBufferUsage Usage;
        typedef VertexBufferTarget Target;
	private:
        static std::map<GLenum, GLuint> s_currentIds;
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
