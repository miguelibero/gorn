
#include <gorn/render/RenderQueueState.hpp>
#include <gorn/render/RenderCamera.hpp>
#include <gorn/render/RenderCommand.hpp>

namespace gorn
{
    RenderQueueState::RenderQueueState(const Camera& cam):
    _boundingEnds(0), _camera(cam), _frustum(cam.getFrustum())
    {
        _transforms.push(glm::mat4());
		_layers.push(Layers());
		_checkpoints.push(0);
    }

	void RenderQueueState::updateLayers(const Command& cmd)
	{
		switch(cmd.getLayersMode())
		{
		case RenderCommand::LayersMode::Start:
		{
			auto layers = cmd.getLayers();
			auto& oldLayers = _layers.top();
			layers.insert(layers.end(), oldLayers.begin(), oldLayers.end());
			_layers.push(std::move(layers));
			break;
		}
		case RenderCommand::LayersMode::End:
			_layers.pop();
			break;
        default:
            break;
		}
	}

    void RenderQueueState::updateTransform(const Command& cmd)
    {
        bool changed = false;
        switch(cmd.getTransformMode())
        {
			case RenderCommand::TransformMode::PushLocal:
                _transforms.push(_transforms.top()*cmd.getTransform());
                changed = true;
                break;
            case RenderCommand::TransformMode::PopLocal:
                _transforms.pop();
                changed = true;
                break;
            case RenderCommand::TransformMode::SetGlobal:
                _transforms.push(cmd.getTransform());
                changed = true;
                break;
            case RenderCommand::TransformMode::PushCheckpoint:
                _checkpoints.push(_transforms.size());
                break;
            case RenderCommand::TransformMode::PopCheckpoint:
            {
                size_t size = _checkpoints.top();
                _checkpoints.pop();
                while(_transforms.size() > size)
                {
                    _transforms.pop();
                    changed = true;
                }
                break;
            }
            default:
                break;
        }
        if(changed)
        {
            _frustum = _camera.getFrustum()*getTransform();
        }
    }

    bool RenderQueueState::checkBounding(const Command& cmd)
    {
        auto bound = cmd.getBoundingMode();
        if(bound == RenderCommand::BoundingMode::End && _boundingEnds > 0)
        {
            _boundingEnds--;
        }
        if(_boundingEnds > 0)
        {
            return false;
        }
        if(bound != RenderCommand::BoundingMode::Start &&
            bound != RenderCommand::BoundingMode::Local)
        {
            return true;
        }

        if(!_frustum.sees(cmd.getBoundingBox()))
        {
            if(bound == RenderCommand::BoundingMode::Start)
            {
                _boundingEnds++;
            }
            return false;
        }
        return true;
    }

	const RenderQueueState::Layers& RenderQueueState::getLayers() const
	{
		return _layers.top();
	}

    const glm::mat4& RenderQueueState::getTransform() const
    {
        return _transforms.top();
    }
}
