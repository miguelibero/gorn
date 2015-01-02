#include <gorn/render/RenderContext.hpp>
#include <gorn/render/Image.hpp>
#include <gorn/render/VertexArray.hpp>
#include <gorn/platform/PlatformBridge.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{
    const char* RenderContext::kDefaultTextureTag = "tex";
    const char* RenderContext::kDefaultVertexShaderTag = "vsh";
    const char* RenderContext::kDefaultFragmentShaderTag = "fsh";

    RenderContext::RenderContext():
    _bridge(nullptr)
    {
    }

    void RenderContext::setPlatformBridge(PlatformBridge& bridge)
    {
        _bridge = &bridge;
    }

    std::shared_ptr<Texture> RenderContext::loadTexture(const std::string& name)
    {
        auto itr = _textures.find(name);
        if(itr != _textures.end())
        {
            return itr->second;
        }
        if(_bridge == nullptr)
        {
            throw Exception("Platform bridge not set.");
        }
        auto img = _bridge->readImage(kDefaultTextureTag, name).get();
        auto tex = std::make_shared<Texture>(img);
        _textures.insert(itr, {name, tex});
        return tex;
    }

    std::shared_ptr<Shader> RenderContext::loadShader(const std::string& name, ShaderType type)
    {
        auto& shaders = _shaders[type];
        auto itr = shaders.find(name);
        if(itr != shaders.end())
        {
            return itr->second;
        }
        if(_bridge == nullptr)
        {
            throw Exception("Platform bridge not set.");
        }
        std::string tag;
        if(type == ShaderType::Vertex)
        {
            tag = kDefaultVertexShaderTag;
        }
        else if(type == ShaderType::Fragment)
        {
            tag = kDefaultFragmentShaderTag;
        }
        auto data = _bridge->readFile(tag, name).get();
        auto shader = std::make_shared<Shader>(data, type);
        shaders.insert(itr, {name, shader});
        return shader;
    }

    std::shared_ptr<Program> RenderContext::loadProgram(const std::string& name)
    {
        auto itr = _programs.find(name);
        if(itr != _programs.end())
        {
            return itr->second;
        }
        auto ditr = _programDefinitions.find(name);
        if(ditr == _programDefinitions.end())
        {
            throw Exception(std::string("Could not find program definition '")+name+"'.");
        }
        ProgramDefinition& def = ditr->second;
        auto vertex = loadShader(def.getVertexShader(), ShaderType::Vertex);
        auto fragment = loadShader(def.getFragmentShader(), ShaderType::Fragment);

        auto program = std::make_shared<Program>(fragment, vertex);
        _programs.insert(itr, {name, program});
        return program;
    }

    std::shared_ptr<Material> RenderContext::loadMaterial(const std::string& name)
    {
        auto itr = _materials.find(name);
        if(itr != _materials.end())
        {
            return itr->second;
        }
        auto ditr = _materialDefinitions.find(name);
        if(ditr == _materialDefinitions.end())
        {
            throw Exception(std::string("Could not find material definition '")+name+"'.");
        }
        MaterialDefinition& def = ditr->second;
        auto program = loadProgram(def.getProgram());

        std::map<std::string, std::shared_ptr<Texture>> textures;
        for(auto itr = def.getTextures().begin();
            itr != def.getTextures().end(); ++itr)
        {
            textures[itr->first] = loadTexture(itr->second);
        }

        auto material = std::make_shared<Material>(program, textures);
        _materials.insert(itr, {name, material});
        return material;
    }

    ProgramDefinition& RenderContext::defineProgram(const std::string& name)
    {
        auto itr = _programDefinitions.find(name);
        if(itr == _programDefinitions.end())
        {
            itr = _programDefinitions.insert(itr, {name, ProgramDefinition()});
            itr->second.withShader(name);
        }
        return itr->second;
    }

    MaterialDefinition& RenderContext::defineMaterial(const std::string& name)
    {
        auto itr = _materialDefinitions.find(name);
        if(itr == _materialDefinitions.end())
        {
            itr = _materialDefinitions.insert(itr, {name, MaterialDefinition()});
        }
        return itr->second;
    }

    void RenderContext::drawArrays(const VertexArray& vao, GLsizei size, GLint offset)
	{
		vao.bind();
		glDrawArrays(GL_TRIANGLES, offset, size);
	}

    void RenderContext::drawElements(const VertexArray& vao, GLsizei size, GLenum type, GLint offset)
    {
		vao.bind();
		glDrawElements(GL_TRIANGLES, size, type,
            reinterpret_cast<const GLvoid*>(offset));
    }

}