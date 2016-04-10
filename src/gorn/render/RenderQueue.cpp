
#include <gorn/render/RenderQueue.hpp>
#include <gorn/render/RenderCommand.hpp>
#include <gorn/render/RenderQueueState.hpp>
#include <gorn/render/RenderQueueBlock.hpp>
#include <gorn/gl/MaterialManager.hpp>
#include <algorithm>

namespace gorn
{
    RenderQueue::RenderQueue(MaterialManager& materials):
    _materials(materials), _infoUpdateInterval(0.0),
    _infoUpdatesPerSecond(10), _tempInfoAmount(0),
	_batching(true)
    {
    }

	void RenderQueue::setBatching(bool enabled)
	{
		_batching = enabled;
	}

    void RenderQueue::setInfoUpdatesPerSecond(size_t ups)
    {
        _infoUpdatesPerSecond = ups;
    }

	UniformValueMap& RenderQueue::getUniformValues()
	{
		return _uniformValues;
	}

	const UniformValueMap& RenderQueue::getUniformValues() const
	{
		return _uniformValues;
	}

	RenderQueue::Camera& RenderQueue::addCamera(const std::shared_ptr<Camera>& cam)
	{
		_cameras.push_back(cam);
		return *cam;
	}

	RenderQueue::Camera& RenderQueue::addCamera()
	{
		return addCamera(std::make_shared<Camera>());
	}

	bool RenderQueue::removeCamera(const std::shared_ptr<Camera>& cam)
	{
		auto itr = std::remove(_cameras.begin(), _cameras.end(), cam);
		if (itr == _cameras.end())
		{
			return false;
		}
		_cameras.erase(itr, _cameras.end());
		return true;
	}

	RenderQueue::Cameras& RenderQueue::getCameras()
	{
		return _cameras;
	}

	const RenderQueue::Cameras& RenderQueue::getCameras() const
	{
		return _cameras;
	}

    RenderCommand& RenderQueue::addCommand(RenderCommand&& cmd)
    {
        std::lock_guard<std::mutex> lock(_commandsMutex);
        _commands.push_back(std::move(cmd));
        return _commands.back();
    }

    RenderCommand& RenderQueue::addCommand()
    {
        std::lock_guard<std::mutex> lock(_commandsMutex);
        _commands.push_back(RenderCommand());
        return _commands.back();
    }

    RenderCommand& RenderQueue::addCommand(const std::string& material)
    {
        auto& cmd = addCommand();
        cmd.withMaterial(_materials.load(material));
        return cmd;
    }

    void RenderQueue::update(double dt)
    {
        _infoUpdateInterval += dt;
    }

    const RenderQueue::Info& RenderQueue::getInfo() const
    {
        return _info;
    }

	void RenderQueue::draw()
	{
		auto infoDuration = 1.0 / _infoUpdatesPerSecond;
		if (_infoUpdateInterval > infoDuration && _tempInfoAmount > 0)
		{
			_tempInfo.framesPerSecond = (float)(1.0 / _infoUpdateInterval);
			_info = _tempInfo.average(_tempInfoAmount);
			_tempInfoAmount = 0;
			_tempInfo = Info();
			while (_infoUpdateInterval > infoDuration)
			{
				_infoUpdateInterval -= infoDuration;
			}
		}
		_tempInfoAmount++;
		std::vector<Command> cmds;
		{
			std::lock_guard<std::mutex> lock(_commandsMutex);
			cmds = std::move(_commands);
			_commands.clear();
		}
		for(auto& cam : _cameras)
		{
			cam->update();
			draw(*cam, cmds);
		}
	}

	void RenderQueue::draw(const Camera& cam, const std::vector<Command>& cmds)
	{
        State state(cam);
		Block block;

        for(auto itr = cmds.begin(); itr != cmds.end(); ++itr)
        {
            auto& cmd = *itr;
			state.updateLayers(cmd);
			if(!cam.matchesLayers(state.getLayers()))
			{
				continue;
			}
			state.updateTransform(cmd);
            auto& transform = state.getTransform();
            if(!state.checkBounding(cmd))
            {
                _tempInfo.drawCallsCulled++;
            }
            else
            {
				if (!_batching || !block.supports(cmd))
				{
					block.draw(_tempInfo);
					block = Block(cmd, cam, transform, _uniformValues);
					auto ditr = itr;
					while (ditr != cmds.end() && block.supports(*ditr))
					{
						block.addDefinition(cmd);
						++ditr;
					}
				}
				else
				{
					_tempInfo.drawCallsBatched++;
				}
                block.addData(cmd, transform);
            }
        }
		block.draw(_tempInfo);
    }
}
