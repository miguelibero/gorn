
#include <gorn/render/RenderQueue.hpp>
#include <gorn/render/VertexArray.hpp>
#include <gorn/render/VertexBuffer.hpp>
#include <gorn/render/MaterialManager.hpp>
#include <gorn/asset/AssetManager.hpp>

namespace gorn
{
    RenderQueue::RenderQueue(MaterialManager& materials):
    _materials(materials)
    {
    }

    void RenderQueue::setDefaultOrder(Order order)
    {
    }

    void RenderQueue::pushOrder(Order order)
    {
    }

    void RenderQueue::popOrder()
    {
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
            vao.draw(cmd.getElements().count, cmd.getDrawMode());
        }
        _commands.clear();
    }
}

