#ifndef __gorn__FrameBuffer__
#define __gorn__FrameBuffer__

#include <gorn/gl/Base.hpp>
#include <gorn/gl/Texture.hpp>
#include <gorn/gl/RenderBuffer.hpp>
#include <gorn/gl/Enums.hpp>
#include <memory>

namespace gorn
{
    class FrameBuffer
    {
    public:
        typedef FrameBufferAttachType AttachType;
    private:
        typedef std::vector<std::shared_ptr<Texture>> Textures;
        typedef std::vector<std::shared_ptr<RenderBuffer>> RenderBuffers;
        static GLuint s_currentId;
        mutable GLuint _id;
        std::map<AttachType,Textures> _textures;
        std::map<AttachType,RenderBuffers> _renderBuffers;

        void cleanup();
        static void bindId(GLuint id);
        static GLenum getAttachTypeEnum(AttachType type);
    public:
        FrameBuffer();
        ~FrameBuffer();

        FrameBuffer(const FrameBuffer& other) = delete;
        FrameBuffer& operator=(const FrameBuffer& other) = delete;

        FrameBuffer(FrameBuffer&& other);
        FrameBuffer& operator=(FrameBuffer&& other);

        void attach(const std::shared_ptr<Texture>& texture,
            AttachType type=AttachType::Color);
        void attach(const std::shared_ptr<RenderBuffer>& buffer);

        void bind() const;
        static void unbind();
        void activate();
        GLuint getId() const;
    };
}

#endif
