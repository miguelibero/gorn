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
        float framesPerSecond;
        size_t drawCalls;
        size_t drawCallsBatched;
        size_t vertexCount;

        RenderQueueDebugInfo();
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

    class RenderQueue;

    struct RenderQueueDrawBlock
    {
        typedef RenderQueueDebugInfo DebugInfo;
        typedef RenderQueueDrawState DrawState;

        std::shared_ptr<Material> material;
        VertexDefinition definition;
        buffer vertices;
        std::vector<unsigned> elements;
        DrawMode mode;
        glm::mat4 transform;

        RenderQueueDrawBlock(
            const std::shared_ptr<Material>& material=nullptr,
            DrawMode mode=DrawMode::Triangles);

        void draw(const RenderQueue& queue, DebugInfo& debug);
    };

    class RenderQueue
    {
    public:
        typedef RenderCommand Command;
        typedef RenderQueueDebugInfo DebugInfo;
        typedef RenderQueueDrawBlock DrawBlock;
        typedef RenderQueueDrawState DrawState;
        typedef std::map<std::string, UniformValue> UniformValueMap;
    private:
        MaterialManager& _materials;
        std::vector<Command> _commands;
        DrawState _state;
        double _updateInterval;
        DebugInfo _debugInfo;
        UniformValueMap _uniforms;

        void draw(DrawBlock& block, DebugInfo& debug, const DrawState& state);
    public:
        RenderQueue(MaterialManager& materials);

        void setUniformValue(const std::string& name, const UniformValue& value);
        bool removeUniformValue(const std::string& name);
        const UniformValueMap& getUniformValues() const;

        void addCommand(RenderCommand&& cmd);
        RenderCommand& addCommand();
        RenderCommand& addCommand(const std::string& material);

        void update(double dt);
        void draw();

        const DebugInfo& getDebugInfo() const;
    };
}

#endif
