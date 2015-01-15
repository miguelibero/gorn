#ifndef __gorn__RenderQueue__
#define __gorn__RenderQueue__

#include <gorn/render/RenderCommand.hpp>
#include <glm/glm.hpp>

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
        MaterialManager& _materials;
        std::vector<Command> _commands;
        glm::mat4 _baseTransform;
    public:
        RenderQueue(MaterialManager& materials);
        void setDefaultOrder(Order order);
        void setBaseTransform(const glm::mat4& trans);
        void addCommand(RenderCommand&& cmd);
        RenderCommand& addCommand();
        RenderCommand& addCommand(const std::string& material);
        void draw();
    };
}

#endif
