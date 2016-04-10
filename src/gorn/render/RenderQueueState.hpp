#ifndef __gorn__RenderQueueState__
#define __gorn__RenderQueueState__

#include <gorn/base/Rect.hpp>
#include <gorn/base/Frustum.hpp>
#include <glm/glm.hpp>
#include <stack>

namespace gorn
{
	class RenderCommand;
	class RenderCamera;

    class RenderQueueState
    {
        typedef RenderCommand Command;
		typedef RenderCamera Camera;
        typedef std::stack<glm::mat4> Transforms;
        typedef std::stack<size_t> Checkpoints;
		typedef std::vector<int> Layers;
		typedef std::stack<Layers> LayersStack;

        size_t _boundingEnds;
        Transforms _transforms;
		const Camera& _camera;
        Frustum _frustum;
        Checkpoints _checkpoints;
		LayersStack _layers;

    public:
        RenderQueueState(const Camera& cam);
        void updateTransform(const Command& cmd);
		void updateLayers(const Command& cmd);
        bool checkBounding(const Command& cmd);
        const glm::mat4& getTransform() const;
		const Layers& getLayers() const;
    };

}

#endif
