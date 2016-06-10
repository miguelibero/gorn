#ifndef __gorn__RenderQueueState__
#define __gorn__RenderQueueState__

#include <gorn/base/Rect.hpp>
#include <gorn/base/Frustum.hpp>
#include <gorn/gl/BlendMode.hpp>
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
        typedef std::stack<glm::mat4> TransformStack;
        typedef std::stack<size_t> CheckpointStack;
		typedef std::vector<int> Layers;
		typedef std::stack<Layers> LayersStack;
		typedef std::stack<BlendMode> BlendStack;

        size_t _boundingEnds;
        TransformStack _transforms;
		const Camera& _camera;
        Frustum _frustum;
        CheckpointStack _checkpoints;
		LayersStack _layers;
		BlendStack _blendModes;

    public:
        RenderQueueState(const Camera& cam);
        void updateTransform(const Command& cmd);
		void updateLayers(const Command& cmd);
		void updateBlendMode(const Command& cmd);
        bool checkBounding(const Command& cmd);
        const glm::mat4& getTransform() const;
		const Layers& getLayers() const;
		const BlendMode& getBlendMode() const;
    };

}

#endif
