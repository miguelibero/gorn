
#include <gorn/render/RenderQueue.hpp>
#include <gorn/render/VertexArray.hpp>
#include <gorn/render/VertexBuffer.hpp>
#include <gorn/render/MaterialManager.hpp>
#include <gorn/asset/AssetManager.hpp>

namespace gorn
{
    RenderQueue::RenderQueue(AssetManager<VertexDefinition>& vdefs, MaterialManager& materials):
    _vdefs(vdefs), _materials(materials)
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

    RenderCommand& RenderQueue::addCommand(
        const std::string& vdefname)
    {
        auto& vdef = *_vdefs.load(vdefname).get();
        _commands.push_back(RenderCommand(vdef));
        return _commands.back();
    }

    RenderCommand& RenderQueue::addCommand(
        const std::string& vdef,
        const std::string& material)
    {
        auto& cmd = addCommand(vdef);
        cmd.withMaterial(_materials.load(material));
        return cmd;
    }

    void RenderQueue::draw()
    {
        // TODO: join commands to reduce draw calls
        for(auto& cmd : _commands)
        {
            VertexArray vao;
            vao.setMaterial(cmd.getMaterial());
            vao.addVertexData(std::make_shared<VertexBuffer>(
                cmd.getVertexData(),
                VertexBuffer::Usage::DynamicDraw,
                VertexBuffer::Target::ArrayBuffer),
                cmd.getVertexDefinition());
            if(cmd.getElementType())
            {
                vao.setElementData(std::make_shared<VertexBuffer>(
                    cmd.getElementData(),
                    VertexBuffer::Usage::DynamicDraw,
                    VertexBuffer::Target::ElementArrayBuffer),
                    cmd.getElementType());
            }
            vao.draw(cmd.getElementCount());
        }
        _commands.clear();
    }
}

