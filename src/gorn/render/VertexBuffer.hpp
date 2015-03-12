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
        static std::map<GLenum, GLuint> s_currentIds;
		mutable GLuint _id;
        Target _target;
        size_t _size;
	public:

		VertexBuffer(const buffer& data,
            Usage usage=Usage::DynamicDraw,
            Target target=Target::ArrayBuffer);
        VertexBuffer(Target target=Target::ArrayBuffer);
		~VertexBuffer();
		GLuint getId() const;

        void bind() const;
        void setData(const buffer& data, Usage usage);
        void setSubData(const buffer& data, size_t offset);
        size_t getSize() const;
	};
}

#endif
