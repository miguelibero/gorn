#ifndef __gorn__RenderQueue__
#define __gorn__RenderQueue__

#include <gorn/render/RenderCommand.hpp>

namespace gorn
{
    enum class RenderQueueOrder
    {
        Fixed,
        GroupByMaterial
    };

    class RenderQueue
    {
    public:
        typedef RenderCommand Command;
        typedef RenderQueueOrder Order;
    private:
        std::vector<Command> _commands;
    public:
        RenderQueue();
        void setDefaultOrder(Order order);
        void pushOrder(Order order);
        void popOrder();
        void addCommand(RenderCommand&& cmd);
        void draw();
    };
}

#endif
