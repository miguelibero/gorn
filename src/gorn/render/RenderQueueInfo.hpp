#ifndef __gorn__RenderQueueInfo__
#define __gorn__RenderQueueInfo__

#include <string>

namespace gorn
{
    class RenderQueueInfo
    {
	public:
        float framesPerSecond;
        size_t drawCalls;
        size_t drawCallsBatched;
        size_t drawCallsCulled;
        size_t vertexCount;

        RenderQueueInfo();
        RenderQueueInfo average(size_t amount) const;

        std::string str() const;
    };
}

#endif
