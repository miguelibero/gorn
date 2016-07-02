#ifndef __gorn__RenderQueueBlock__
#define __gorn__RenderQueueBlock__

#include <gorn/render/RenderCommand.hpp>
#include <gorn/gl/UniformValue.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <map>
#include <buffer.hpp>

namespace gorn
{
	class RenderQueueInfo;
	class RenderCamera;
	class RenderQueueState;

    class RenderQueueBlock
    {
    public:
        typedef RenderQueueInfo Info;
        typedef RenderCommand::Elements Elements;
    private:
        std::shared_ptr<Material> _material;
        buffer _vertices;
        Elements _elements;
		UniformValueMap _uniforms;
        DrawMode _mode;
        Stencil _stencil;
        ClearAction _clearAction;
        StateChange _stateChange;
		glm::mat4 _transform;
		glm::mat4 _inverse;
		BlendMode _blendMode;

    public:
        RenderQueueBlock();
        RenderQueueBlock(const RenderCommand& cmd, const RenderCamera& cam, const RenderQueueState& state, const UniformValueMap& uniforms);
        bool supports(const RenderCommand& cmd) const;
		bool supports(const RenderQueueState& cmd) const;
        void draw(Info& info);
        void addData(const RenderCommand& cmd, const glm::mat4& trans);
    };

}

#endif
