
#include <gorn/render/RenderQueue.hpp>
#include <gorn/render/VertexArray.hpp>
#include <gorn/render/VertexBuffer.hpp>
#include <gorn/render/MaterialManager.hpp>
#include <gorn/render/Kinds.hpp>
#include <gorn/asset/AssetManager.hpp>
#include <algorithm>
#include <cmath>
#include <glm/gtc/matrix_inverse.hpp>

namespace gorn
{
    RenderQueue::RenderQueue(MaterialManager& materials):
    _materials(materials), _infoUpdateInterval(0.0),
    _infoUpdatesPerSecond(10), _tempInfoAmount(0)
    {
    }

    void RenderQueue::setInfoUpdatesPerSecond(size_t ups)
    {
        _infoUpdatesPerSecond = ups;
    }

    void RenderQueue::setUniformValue(const std::string& name,
        const UniformValue& value)
    {
        _uniforms[name] = value;
    }

    bool RenderQueue::removeUniformValue(const std::string& name)
    {
        auto itr = _uniforms.find(name);
        if(itr != _uniforms.end())
        {
            _uniforms.erase(itr);
            return true;
        }
        return false;
    }

    const RenderQueue::UniformValueMap& RenderQueue::getUniformValues() const
    {
        return _uniforms;
    }

    void RenderQueue::addCommand(RenderCommand&& cmd)
    {
        _commands.push_back(std::move(cmd));
    }

    RenderCommand& RenderQueue::addCommand()
    {
        _commands.push_back(RenderCommand());
        return _commands.back();
    }

    RenderCommand& RenderQueue::addCommand(const std::string& material)
    {
        auto& cmd = addCommand();
        cmd.withMaterial(_materials.load(material));
        return cmd;
    }

    void RenderQueue::update(double dt)
    {
        _infoUpdateInterval += dt;
    }

    const RenderQueue::Info& RenderQueue::getInfo() const
    {
        return _info;
    }

    void RenderQueue::draw()
    {
        auto infoDuration = 1.0/_infoUpdatesPerSecond;
        if(_infoUpdateInterval > infoDuration)
        {
            _tempInfo.framesPerSecond = 1.0 / _infoUpdateInterval;
            _info = _tempInfo.average(_tempInfoAmount);
            _tempInfoAmount = 0;
            _tempInfo = Info();
            while(_infoUpdateInterval > infoDuration)
            {
                _infoUpdateInterval -= infoDuration;
            }
        }
        _tempInfoAmount++;

        DrawState state;
        DrawBlock block;

        for(auto& cmd : _commands)
        {
            state.update(cmd);
            auto cmdMaterial = cmd.getMaterial();
            if(!cmdMaterial)
            {
                continue;
            }
            auto cmdMode = cmd.getDrawMode();
            if(cmdMaterial != block.material || cmdMode != block.mode)
            {
                block.draw(*this, _tempInfo);
                block = DrawBlock(cmdMaterial, cmdMode);
            }
            else
            {
                _tempInfo.drawCallsBatched++;
            }
             
            auto& transform = state.getTransform();
            // TODO: load def first
            block.definition += cmd.getVertexDefinition(
                *block.material->getProgram());

            cmd.getVertexData(block.vertices, block.elements,
                block.definition, transform);
        }
        block.draw(*this, _tempInfo);

        _commands.erase(std::remove_if(_commands.begin(), _commands.end(),
            [](const Command& cmd){
                return cmd.getLifetime() == RenderCommandLifetime::Frame;
            }), _commands.end());
    }

    RenderQueueDrawBlock::RenderQueueDrawBlock(
        const std::shared_ptr<Material>& material,
        DrawMode mode):
        material(material), mode(mode)
    {
    }

    void RenderQueueDrawBlock::draw(const RenderQueue& queue,
        Info& info)
    {
        if(vertices.empty() || material == nullptr
            || material->getProgram() == nullptr)
        {
            return;
        }

        VertexArray vao;
        auto usage = VertexBuffer::Usage::StaticDraw;
        auto elmsCount = elements.size();
        auto vertsCount = vertices.size()/definition.getElementSize();
        vao.setMaterial(material);
        vao.addVertexData(std::make_shared<VertexBuffer>(
            std::move(vertices), usage,
            VertexBuffer::Target::ArrayBuffer),
            definition);
        vao.setElementData(std::make_shared<VertexBuffer>(
            std::move(elements), usage,
            VertexBuffer::Target::ElementArrayBuffer));
        
        vao.setUniformValues(queue.getUniformValues());
        vao.setUniformValue(UniformKind::Model, transform);
    
        vao.draw(elmsCount, mode);
        info.vertexCount += vertsCount;
        info.drawCalls++;
    }

    RenderQueueInfo::RenderQueueInfo():
    framesPerSecond(0.0), drawCalls(0),
    drawCallsBatched(0), vertexCount(0)
    {
    }

    RenderQueueInfo RenderQueueInfo::average(size_t amount) const
    {
        RenderQueueInfo result(*this);
        result.framesPerSecond *= amount;
        result.drawCalls /= amount;
        result.drawCallsBatched /= amount;
        result.vertexCount /= amount;
        return result;
    }

    RenderQueueDrawState::RenderQueueDrawState()
    {
        _transforms.push(glm::mat4());
    }

    void RenderQueueDrawState::update(const Command& cmd)
    {
        switch(cmd.getTransformMode())
        {
            case RenderCommand::TransformMode::PushLocal:
                _transforms.push(_transforms.top()*cmd.getTransform());
                break;
            case RenderCommand::TransformMode::PopLocal:
                _transforms.pop();
                break;
            case RenderCommand::TransformMode::SetGlobal:
                _transforms.push(cmd.getTransform());
                break;
                break;
            case RenderCommand::TransformMode::PushCheckpoint:
                _checkpoints.push(_transforms.size());
                break;
            case RenderCommand::TransformMode::PopCheckpoint:
            {
                size_t size = _checkpoints.top();
                _checkpoints.pop();
                while(_transforms.size() > size)
                {
                    _transforms.pop();
                }
                break;
            }
            default:
                break;
        }
    }

    const glm::mat4& RenderQueueDrawState::getTransform() const
    {
        return _transforms.top();
    }
}

