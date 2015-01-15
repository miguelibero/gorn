
#include <gorn/render/RenderQueue.hpp>
#include <gorn/render/VertexArray.hpp>
#include <gorn/render/VertexBuffer.hpp>
#include <gorn/render/MaterialManager.hpp>
#include <gorn/render/Kinds.hpp>
#include <gorn/asset/AssetManager.hpp>
#include <stack>

namespace gorn
{
    RenderQueue::RenderQueue(MaterialManager& materials):
    _materials(materials)
    {
    }

    void RenderQueue::setDefaultOrder(Order order)
    {
    }

    void RenderQueue::setBaseTransform(const glm::mat4& trans)
    {
        _baseTransform = trans;
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
        transforms.push(_baseTransform);
        for(auto& cmd : _commands)
        {
            VertexArray vao;
            vao.setMaterial(cmd.getMaterial());
            auto vdef = cmd.generateVertexDefinition();
            Data vdata = cmd.generateVertexData(vdef);
            vao.addVertexData(std::make_shared<VertexBuffer>(
                std::move(vdata),
                VertexBuffer::Usage::DynamicDraw,
                VertexBuffer::Target::ArrayBuffer),
                vdef);
            if(cmd.getElements().type)
            {
                vao.setElementData(std::make_shared<VertexBuffer>(
                    std::move(cmd.getElements().data),
                    VertexBuffer::Usage::DynamicDraw,
                    VertexBuffer::Target::ElementArrayBuffer),
                    cmd.getElements().type);
            }
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
                    transforms.emplace();
                    break;
                default:
                    break;
            }
            vao.setUniformValue(UniformKind::Transform, transforms.top());
            vao.draw(cmd.getElements().count, cmd.getDrawMode());
        }
        _commands.clear();
    }
}

