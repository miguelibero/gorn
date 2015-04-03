#ifndef __gorn__RenderQueue__
#define __gorn__RenderQueue__

#include <gorn/render/RenderCommand.hpp>
#include <gorn/render/Enums.hpp>
#include <glm/glm.hpp>
#include <stack>
#include <mutex>

class buffer;

namespace gorn
{
    class MaterialManager;
    class VertexDefinition;
    
    template<typename A>
    class AssetManager;

    struct RenderQueueInfo
    {
        float framesPerSecond;
        size_t drawCalls;
        size_t drawCallsBatched;
        size_t drawCallsCulled;
        size_t vertexCount;

        RenderQueueInfo();
        RenderQueueInfo average(size_t amount) const;
    };

    class RenderQueueDrawState
    {
        typedef RenderCommand Command;
        typedef std::stack<glm::mat4> Transforms;
        typedef std::stack<size_t> Checkpoints;
        typedef RenderCommandBoundingMode BoundingMode;
        typedef RenderCommandTransformMode TransformMode;

        static Rect _screenRect;
        Transforms _transforms;
        Checkpoints _checkpoints;
        size_t _boundingEnds;

    public:
        RenderQueueDrawState();
        void updateTransform(const Command& cmd);
        bool checkBounding(const Command& cmd, const glm::mat4& viewProj);
        const glm::mat4& getTransform() const;
    };

    class RenderQueue;

    struct RenderQueueDrawBlock
    {
        typedef RenderQueueInfo Info;
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

        bool supports(const RenderCommand& cmd) const;
        void draw(const RenderQueue& queue, Info& info);
    };

    class RenderQueue
    {
    public:
        typedef RenderCommand Command;
        typedef RenderQueueInfo Info;
        typedef RenderQueueDrawBlock DrawBlock;
        typedef RenderQueueDrawState DrawState;
        typedef std::map<std::string, UniformValue> UniformValueMap;
    private:
        MaterialManager& _materials;
        std::vector<Command> _commands;
        std::mutex _commandsMutex;
        DrawState _state;
        UniformValueMap _uniforms;
        Info _info;
        Info _tempInfo;
        double _infoUpdateInterval;
        size_t _infoUpdatesPerSecond;
        size_t _tempInfoAmount;
        glm::mat4 _viewTrans;
        glm::mat4 _projTrans;
        glm::mat4 _viewProjTrans;

    public:
        RenderQueue(MaterialManager& materials);

        void setViewTransform(const glm::mat4& view);
        void setProjectionTransform(const glm::mat4& proj);

        void setUniformValue(const std::string& name, const UniformValue& value);
        bool removeUniformValue(const std::string& name);
        const UniformValueMap& getUniformValues() const;

        void addCommand(RenderCommand&& cmd);
        RenderCommand& addCommand();
        RenderCommand& addCommand(const std::string& material);

        void update(double dt);
        void draw();

        const Info& getInfo() const;
        void setInfoUpdatesPerSecond(size_t ups);

    };
}

#endif
