#ifndef __gorn__RenderQueue__
#define __gorn__RenderQueue__

#include <gorn/render/RenderCommand.hpp>
#include <gorn/render/RenderEnums.hpp>
#include <gorn/base/Frustum.hpp>
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

    class RenderQueueState
    {
        typedef RenderCommand Command;
        typedef std::stack<glm::mat4> Transforms;
        typedef std::stack<size_t> Checkpoints;
        typedef RenderCommandBoundingMode BoundingMode;
        typedef RenderCommandTransformMode TransformMode;

        size_t _boundingEnds;
        static Rect _screenRect;
        Transforms _transforms;
        Frustum _frustum;
        Frustum _baseFrustum;
        Checkpoints _checkpoints;

    public:
        RenderQueueState(const Frustum& frustum,
            const glm::mat4& trans=glm::mat4());
        void updateTransform(const Command& cmd);
        bool checkBounding(const Command& cmd);
        const glm::mat4& getTransform() const;
    };

    class RenderQueue;

    class RenderQueueBlock
    {
    public:    
        typedef RenderQueueInfo Info;
        typedef RenderCommand::Elements Elements;
    private:
        std::shared_ptr<Material> _material;
        VertexDefinition _definition;
        buffer _vertices;
        Elements _elements;
        DrawMode _mode;
        glm::mat4 _transform;
        Stencil _stencil;
        ClearAction _clearAction;
        FeatureState _featureState;

    public:
        RenderQueueBlock();
        RenderQueueBlock(const RenderCommand& cmd);
        bool supports(const RenderCommand& cmd) const;
        void draw(const RenderQueue& queue, Info& info);
        void addDefinition(const RenderCommand& cmd);
        void addData(const RenderCommand& cmd, const glm::mat4& trans);
    };

    class RenderQueue
    {
    public:
        typedef RenderCommand Command;
        typedef RenderQueueInfo Info;
        typedef RenderQueueBlock Block;
        typedef RenderQueueState State;
        typedef std::map<std::string, UniformValue> UniformValueMap;
    private:
        MaterialManager& _materials;
        std::vector<Command> _commands;
        std::mutex _commandsMutex;
        UniformValueMap _uniforms;
        Info _info;
        Info _tempInfo;
        double _infoUpdateInterval;
        size_t _infoUpdatesPerSecond;
        size_t _tempInfoAmount;
        glm::mat4 _viewTrans;
        glm::mat4 _projTrans;
        glm::mat4 _modelTrans;
        Frustum _frustum;

    public:
        RenderQueue(MaterialManager& materials);

        void setViewTransform(const glm::mat4& view);
        void setProjectionTransform(const glm::mat4& proj);
        void setModelTransform(const glm::mat4& model);
        const Frustum& getFrustum() const;

        void setUniformValue(const std::string& name, const UniformValue& value);
        bool removeUniformValue(const std::string& name);
        const UniformValueMap& getUniformValues() const;

        RenderCommand& addCommand(RenderCommand&& cmd);
        RenderCommand& addCommand();
        RenderCommand& addCommand(const std::string& material);

        void update(double dt);
        void draw();

        const Info& getInfo() const;
        void setInfoUpdatesPerSecond(size_t ups);

    };
}

#endif
