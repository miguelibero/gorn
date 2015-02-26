
#include <gorn/render/RenderQueue.hpp>
#include <gorn/render/VertexArray.hpp>
#include <gorn/render/VertexBuffer.hpp>
#include <gorn/render/MaterialManager.hpp>
#include <gorn/render/Kinds.hpp>
#include <gorn/asset/AssetManager.hpp>
#include <stack>
#include <algorithm>

namespace gorn
{
    RenderQueue::RenderQueue(MaterialManager& materials):
    _materials(materials)
    {
    }

    void RenderQueue::setDefaultOrder(Order order)
    {
    }

    void RenderQueue::setUniformValue(const std::string& name,
        const UniformValue& value)
    {
        _uniformValues[name] = value;
    }

    bool RenderQueue::removeUniformValue(const std::string& name)
    {
        auto itr = _uniformValues.find(name);
        if(itr != _uniformValues.end())
        {
            _uniformValues.erase(itr);
            return true;
        }
        return false;
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

    void RenderQueue::draw()
    {
        std::stack<glm::mat4> transforms;
        transforms.push(glm::mat4());
        std::stack<size_t> checkpoints;
        for(auto& cmd : _commands)
        {
            switch(cmd.getTransformMode())
            {
                case RenderCommand::TransformMode::PushLocal:
                    transforms.push(transforms.top()*cmd.getTransform());
                    break;
                case RenderCommand::TransformMode::PopLocal:
                    transforms.pop();
                    break;
                case RenderCommand::TransformMode::SetGlobal:
                    transforms.push(cmd.getTransform());
                    break;
                case RenderCommand::TransformMode::SetNone:
                    transforms.push(glm::mat4());
                    break;
                case RenderCommand::TransformMode::PushCheckpoint:
                    checkpoints.push(transforms.size());
                    break;
                case RenderCommand::TransformMode::PopCheckpoint:
                {
                    size_t size = checkpoints.top();
                    checkpoints.pop();
                    while(transforms.size() > size)
                    {
                        transforms.pop();
                    }
                    break;
                }
                default:
                    break;
            }

            if(cmd.getMaterial())
            {
                VertexArray vao;
                vao.setMaterial(cmd.getMaterial());
                auto vdef = cmd.getVertexDefinition(
                    *cmd.getMaterial()->getProgram());
                Data vertData;
                Data elmData;
                auto num = cmd.getVertexData(vdef, vertData, elmData);
                auto usage = VertexBuffer::Usage::StaticDraw;

                vao.addVertexData(std::make_shared<VertexBuffer>(
                    std::move(vertData), usage,
                    VertexBuffer::Target::ArrayBuffer), vdef);
                vao.setElementData(std::make_shared<VertexBuffer>(
                    std::move(elmData), usage,
                    VertexBuffer::Target::ElementArrayBuffer));

                for(auto itr = _uniformValues.begin();
                    itr != _uniformValues.end(); ++itr)
                {
                    vao.setUniformValue(itr->first, itr->second);
                }
                vao.setUniformValue(UniformKind::Model, transforms.top());
                vao.draw(num, cmd.getDrawMode());
            }
        }
        _commands.erase(std::remove_if(_commands.begin(), _commands.end(),
            [](const Command& cmd){
                return cmd.getLifetime() == RenderCommandLifetime::Frame;
            }), _commands.end());
    }
}

