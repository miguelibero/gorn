
#include <gorn/render/RenderQueueBlock.hpp>
#include <gorn/render/RenderQueueInfo.hpp>
#include <gorn/render/RenderQueueState.hpp>
#include <gorn/render/RenderQueue.hpp>
#include <gorn/gl/VertexBuffer.hpp>
#include <gorn/gl/VertexArray.hpp>
#include <gorn/render/RenderKinds.hpp>

namespace gorn
{
    RenderQueueBlock::RenderQueueBlock()
    {
    }

    RenderQueueBlock::RenderQueueBlock(const RenderCommand& cmd, const RenderCamera& cam, const RenderQueueState& state, const UniformValueMap& uniforms):
    _material(cmd.getMaterial()),
    _uniforms(uniforms),
    _mode(cmd.getDrawMode()),
    _stencil(cmd.getStencil()),
    _clearAction(cmd.getClearAction()),
    _stateChange(cmd.getStateChange()),
	_transform(state.getTransform()),
	_inverse(glm::inverse(_transform)),
    _blendMode(state.getBlendMode())
    {
		if(cmd.getBlendStackAction() == RenderStackAction::Push)
		{
			_blendMode = cmd.getBlendMode();
		}
		_uniforms += cam.getUniformValues();
    }

    void RenderQueueBlock::addDefinition(const RenderCommand& cmd)
    {
        if(_material != nullptr && _material->getProgram() != nullptr)
        {
			_definition += _material->getProgram()->getVertexDefinition();
        }
    }

    void RenderQueueBlock::addData(const RenderCommand& cmd,
        const glm::mat4& trans)
    {
		_uniforms += cmd.getUniformValues();
		auto rtrans = _inverse * trans;
        cmd.getVertexData(_vertices, _elements, _definition, rtrans);
    }

	bool RenderQueueBlock::supports(const RenderQueueState& state) const
	{
		return true
			&& state.getBlendMode() == _blendMode;
	}

    bool RenderQueueBlock::supports(const RenderCommand& cmd) const
    {
		return true
			&& cmd.getClearAction().empty()
			&& (cmd.getMaterial() == _material || cmd.getMaterial() == nullptr)
			&& cmd.getDrawMode() == _mode
			&& cmd.getStencil() == _stencil
			&& cmd.getStateChange() == _stateChange;
    }

    void RenderQueueBlock::draw(Info& info)
    {
        _stateChange.apply();
		_stencil.apply();
		_clearAction.apply();

        if(_vertices.empty() || _material == nullptr
            || _material->getProgram() == nullptr)
        {
            return;
        }

		_blendMode.apply();

        VertexArray vao;
        auto usage = VertexBuffer::Usage::StaticDraw;
        auto elmsCount = _elements.size();
        auto vertsCount = _vertices.size()/_definition.getElementSize();
        vao.setMaterial(_material);
        vao.addVertexData(std::make_shared<VertexBuffer>(
            buffer(std::move(_vertices)), usage,
            VertexBuffer::Target::ArrayBuffer),
            _definition);
        vao.setElementData(std::make_shared<VertexBuffer>(
            buffer(std::move(_elements)), usage,
            VertexBuffer::Target::ElementArrayBuffer));

        vao.setUniformValues(_uniforms);
        vao.setUniformValue(UniformKind::Model, _transform);
		if(_material->getProgram()->hasUniform(UniformKind::NormalMatrix))
		{
			auto normal = glm::transpose(glm::inverse(glm::mat3(_transform)));
			vao.setUniformValue(UniformKind::NormalMatrix, normal);
		}

        vao.draw(elmsCount, _mode);
        info.vertexCount += vertsCount;
        info.drawCalls++;
    }

}
