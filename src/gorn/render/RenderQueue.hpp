#ifndef __gorn__RenderQueue__
#define __gorn__RenderQueue__

#include <gorn/render/RenderCommand.hpp>
#include <gorn/render/RenderQueueInfo.hpp>
#include <gorn/render/RenderCamera.hpp>
#include <gorn/gl/UniformValue.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <mutex>

class buffer;

namespace gorn
{
    class MaterialManager;
	class RenderQueueState;
	class RenderQueueBlock;

    class RenderQueue
    {
    public:
        typedef RenderCommand Command;
		typedef RenderCamera Camera;
        typedef RenderQueueInfo Info;
        typedef RenderQueueBlock Block;
        typedef RenderQueueState State;
		typedef std::vector<std::shared_ptr<Camera>> Cameras;
    private:
        MaterialManager& _materials;
        std::vector<Command> _commands;
        std::mutex _commandsMutex;
		Cameras _cameras;
        Info _info;
        Info _tempInfo;
        double _infoUpdateInterval;
        size_t _infoUpdatesPerSecond;
        size_t _tempInfoAmount;
        glm::mat4 _modelTrans;
		UniformValueMap _uniformValues;
		bool _batching;

		void draw(const Camera& cam, const std::vector<Command>& cmds);
    public:
        RenderQueue(MaterialManager& materials);

		void setBatching(bool enabled);

		UniformValueMap& getUniformValues();
		const UniformValueMap& getUniformValues() const;

		Camera& addCamera(const std::shared_ptr<Camera>& cam);
		bool removeCamera(const std::shared_ptr<Camera>& cam);
		Camera& addCamera();

		Cameras& getCameras();
		const Cameras& getCameras() const;

        RenderCommand& addCommand(RenderCommand&& cmd);
        RenderCommand& addCommand();
        RenderCommand& addCommand(const std::string& material);

        void update(double dt);
        void draw();

        const Info& getInfo() const;
        void setInfoUpdatesPerSecond(size_t ups);
    };
}

#endif
