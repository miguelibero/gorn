#include <gorn/render/RenderContext.hpp>
#include <gorn/render/Image.hpp>
#include <gorn/render/VertexArray.hpp>
#include <gorn/platform/PlatformBridge.hpp>
#include <gorn/base/Log.hpp>
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
        LogDebug("loaded texture '%s' into %d", name.c_str(), tex->getId());
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
        LogDebug("loaded shader '%s' into %d", name.c_str(), shader->getId());
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
        LogDebug("loaded program '%s' into %d", name.c_str(), program->getId());
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

        std::vector<std::shared_ptr<Texture>> textures;

        auto material = std::make_shared<Material>(program, textures);
        _materials.insert(itr, {name, material});
        LogDebug("loaded material '%s'", name.c_str());
        return material;
    }

    void RenderContext::defineProgram(const std::string& name, const ProgramDefinition& def)
    {
        auto itr = _programDefinitions.find(name);
        if(itr != _programDefinitions.end())
        {
            throw Exception(std::string("Program '")+name+"' already defined.");
        }
        _programDefinitions.insert(itr, {name, def});
    }

    void RenderContext::defineProgram(const std::string& name)
    {
        defineProgram(name, ProgramDefinition(name));
    }

    void RenderContext::defineMaterial(const std::string& name, const MaterialDefinition& def)
    {
        auto itr = _materialDefinitions.find(name);
        if(itr != _materialDefinitions.end())
        {
            throw Exception(std::string("Material '")+name+"' already defined.");
        }
        _materialDefinitions.insert(itr, {name, def});
    }

    void RenderContext::drawArrays(const VertexArray& vao, GLsizei size, GLint offset)
	{
		glBindVertexArray(vao.getId());
		glDrawArrays(GL_TRIANGLES, offset, size);
	}

}
