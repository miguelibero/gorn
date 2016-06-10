
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
		_blendModes.push(BlendMode());
    }

	void RenderQueueState::updateLayers(const Command& cmd)
	{
		switch(cmd.getLayersStackAction())
		{
		case RenderStackAction::Push:
		{
			auto layers = cmd.getLayers();
			auto& oldLayers = _layers.top();
			layers.insert(layers.end(), oldLayers.begin(), oldLayers.end());
			_layers.push(std::move(layers));
			break;
		}
		case RenderStackAction::Pop:
			_layers.pop();
			break;
        default:
            break;
		}
	}

	void RenderQueueState::updateBlendMode(const Command& cmd)
	{
		switch (cmd.getBlendStackAction())
		{
		case RenderStackAction::Push:
		{
			_blendModes.push(cmd.getBlendMode());
			break;
		}
		case RenderStackAction::Pop:
			_blendModes.pop();
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
			case RenderTransformStackAction::PushLocal:
                _transforms.push(_transforms.top()*cmd.getTransform());
                changed = true;
                break;
            case RenderTransformStackAction::PopLocal:
                _transforms.pop();
                changed = true;
                break;
            case RenderTransformStackAction::SetGlobal:
                _transforms.push(cmd.getTransform());
                changed = true;
                break;
            case RenderTransformStackAction::PushCheckpoint:
                _checkpoints.push(_transforms.size());
                break;
            case RenderTransformStackAction::PopCheckpoint:
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
        auto bound = cmd.getBoundingStackAction();
        if(bound == RenderStackAction::Pop && _boundingEnds > 0)
        {
            _boundingEnds--;
        }
        if(_boundingEnds > 0)
        {
            return false;
        }
        if(bound != RenderStackAction::Push)
        {
            return true;
        }

        if(!_frustum.sees(cmd.getBoundingBox()))
        {
            if(bound == RenderStackAction::Push)
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

	const BlendMode& RenderQueueState::getBlendMode() const
	{
		return _blendModes.top();
	}
}
