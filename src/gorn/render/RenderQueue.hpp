#ifndef __gorn__RenderQueue__
#define __gorn__RenderQueue__

#include <gorn/render/RenderCommand.hpp>
#include <gorn/render/Enums.hpp>
#include <glm/glm.hpp>
#include <stack>

class buffer;

namespace gorn
{

    class MaterialManager;
    class VertexDefinition;
    
    template<typename A>
    class AssetManager;

    struct RenderQueueDebugInfo
    {
        double framesPerSecond;
        double drawCalls;
        double drawCallsBatched;

        RenderQueueDebugInfo();
    };

    struct RenderQueueDrawBlock
    {
        std::shared_ptr<Material> material;
        VertexDefinition definition;
        buffer vertices;
        std::vector<unsigned> elements;
        glm::mat4 transform;
        DrawMode mode;

        RenderQueueDrawBlock(
            const std::shared_ptr<Material>& material=nullptr,
            DrawMode mode=DrawMode::Triangles);
    };

    class RenderQueueDrawState
    {
        typedef RenderCommand Command;
        typedef std::stack<glm::mat4> Transforms;
        typedef std::stack<size_t> Checkpoints;
        Transforms _transforms;
        Checkpoints _checkpoints;
    public:
        RenderQueueDrawState();
        void update(const Command& cmd);
        const glm::mat4& getTransform() const;
    };

    class RenderQueue
    {
    public:
        typedef RenderCommand Command;
        typedef RenderQueueDebugInfo DebugInfo;
        typedef RenderQueueDrawBlock DrawBlock;
        typedef RenderQueueDrawState DrawState;
    private:

        MaterialManager& _materials;
        std::vector<Command> _commands;
        std::map<std::string, UniformValue> _uniformValues;
        double _updateInterval;
        DebugInfo _debugInfo;

        bool draw(DrawBlock&& block) const;
    public:
        RenderQueue(MaterialManager& materials);

        void setUniformValue(const std::string& name, const UniformValue& value);
        bool removeUniformValue(const std::string& name);

        void addCommand(RenderCommand&& cmd);
        RenderCommand& addCommand();
        RenderCommand& addCommand(const std::string& material);

        void update(double dt);
        void draw();

        const DebugInfo& getDebugInfo() const;
    };
}

#endif
