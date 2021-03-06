
#include <gorn/render/RenderQueueBlock.hpp>
#include <gorn/render/RenderQueueInfo.hpp>
#include <gorn/render/RenderQueueState.hpp>
#include <gorn/render/RenderQueue.hpp>
#include <gorn/gl/VertexBuffer.hpp>
#include <gorn/gl/VertexArray.hpp>

namespace gorn
{
    RenderQueueBlock::RenderQueueBlock()
    {
    }

    RenderQueueBlock::RenderQueueBlock(const RenderCommand& cmd, const RenderCamera& cam, const RenderQueueState& state, const UniformValueMap& uniforms):
    _material(cmd.getMaterial()),
    _uniforms(uniforms),
    _mode(cmd.getDrawMode()),
    _stencil(state.getStencil()),
    _clearAction(cmd.getClearAction()),
    _capabilities(state.getCapabilities()),
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

    void RenderQueueBlock::addData(const RenderCommand& cmd,
        const glm::mat4& trans)
    {
		_uniforms += cmd.getUniformValues();
		auto rtrans = _inverse * trans;
		if(_material == nullptr && cmd.getMaterial() != nullptr)
		{
			_material = cmd.getMaterial();
		}
        cmd.dumpVertexData(_vertices, _elements, rtrans);
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
			&& cmd.getCapabilities() == _capabilities;
    }

    void RenderQueueBlock::draw(Info& info)
    {
		_capabilities.apply();
		_stencil.apply();
		_clearAction.apply();

        if(_vertices.empty() || _material == nullptr
            || _material->getProgram() == nullptr)
        {
            return;
        }

		_blendMode.apply();

        VertexArray vao;
		auto& def = _material->getProgram()->getVertexDefinition();
        auto usage = VertexBuffer::Usage::StaticDraw;
        auto elmsCount = _elements.size();
        auto vertsCount = _vertices.size()/def.getElementSize();
        vao.setMaterial(_material);
        vao.addVertexData(std::make_shared<VertexBuffer>(
            buffer(std::move(_vertices)), usage,
            VertexBuffer::Target::ArrayBuffer),
			def);
        vao.setElementData(std::make_shared<VertexBuffer>(
            buffer(std::move(_elements)), usage,
            VertexBuffer::Target::ElementArrayBuffer));

		for(auto itr = _uniforms.begin(); itr != _uniforms.end(); ++itr)
		{
			auto uniformId = _material->getProgram()->getUniform(itr->first);
			if (uniformId >= 0)
			{
				vao.setUniformValue(uniformId, itr->second);
			}
		}
		auto uniformId = _material->getProgram()->getUniform(UniformType::ModelTransform);
		if (uniformId > 0)
		{
			vao.setUniformValue(uniformId, _transform);
		}
		uniformId = _material->getProgram()->getUniform(UniformType::NormalTransform);
		if(uniformId > 0)
		{
			auto normal = glm::transpose(glm::inverse(glm::mat3(_transform)));
			vao.setUniformValue(uniformId, normal);
		}
        vao.draw(elmsCount, _mode);
        info.vertexCount += vertsCount;
        info.drawCalls++;
    }

}
