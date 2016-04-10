
#include <gorn/render/RenderQueueInfo.hpp>
#include <sstream>

namespace gorn
{    
    RenderQueueInfo::RenderQueueInfo():
    framesPerSecond(0.0), drawCalls(0),
    drawCallsBatched(0), drawCallsCulled(0),
    vertexCount(0)
    {
    }

    RenderQueueInfo RenderQueueInfo::average(size_t amount) const
    {
        if(amount == 0)
        {
            return RenderQueueInfo();
        }
        RenderQueueInfo result(*this);
        result.framesPerSecond *= amount;
        result.drawCalls /= amount;
        result.drawCallsBatched /= amount;
        result.vertexCount /= amount;
        return result;
    }

    std::string RenderQueueInfo::str() const
    {
        std::stringstream ss;
        ss << "fps: " << framesPerSecond << std::endl;
        ss << "draws: " << drawCalls << "/";
        ss << drawCallsBatched << "/";
        ss << drawCallsCulled << std::endl;
        ss << "verts: " << vertexCount;
        return ss.str();
    }
}
