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

    class MaterialManager;
    
    template<typename A>
    class AssetManager;

    class RenderQueue
    {
    public:
        typedef RenderCommand Command;
        typedef RenderQueueOrder Order;
    private:
        AssetManager<VertexDefinition>& _vdefs;
        MaterialManager& _materials;
        std::vector<Command> _commands;

    public:
        RenderQueue(AssetManager<VertexDefinition>& vdefs, MaterialManager& materials);
        void setDefaultOrder(Order order);
        void pushOrder(Order order);
        void popOrder();
        void addCommand(RenderCommand&& cmd);
        RenderCommand& addCommand(
            const std::string& vdef);
        RenderCommand& addCommand(
            const std::string& vdef,
            const std::string& material);
        void draw();
    };
}

#endif
