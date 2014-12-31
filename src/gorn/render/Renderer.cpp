#include <gorn/render/Renderer.hpp>
#include <gorn/render/Image.hpp>
#include <gorn/platform/PlatformBridge.hpp>
#include <gorn/base/Log.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{
    Renderer::Renderer():
    _bridge(nullptr)
    {
    }

    void Renderer::draw()
    {
    }

    void Renderer::setPlatformBridge(PlatformBridge& bridge)
    {
        _bridge = &bridge;
    }

    std::shared_ptr<Texture> Renderer::loadTexture(const std::string& name)
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
        auto img = _bridge->readImage(name).get();
        auto tex = std::make_shared<Texture>(img);
        _textures.insert(itr, {name, tex});
        LogDebug("loaded texture '%s' into %d", name.c_str(), tex->getId());
        return tex;
    }

    std::shared_ptr<Shader> Renderer::loadShader(const std::string& name, GLenum type)
    {
        auto itr = _shaders.find(name);
        if(itr != _shaders.end())
        {
            return itr->second;
        }
        if(_bridge == nullptr)
        {
            throw Exception("Platform bridge not set.");
        }
        auto data = _bridge->readFile(name).get();
        auto shader = std::make_shared<Shader>(data, type);
        _shaders.insert(itr, {name, shader});
        LogDebug("loaded shader '%s' into %d", name.c_str(),shader->getId());
        return shader;
    }

    std::shared_ptr<Program> Renderer::loadProgram(const std::string& name)
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
        auto vertex = loadShader(def.getVertexShader(), GL_VERTEX_SHADER);
        auto fragment = loadShader(def.getFragmentShader(), GL_FRAGMENT_SHADER);

        auto program = std::make_shared<Program>(fragment, vertex);
        _programs.insert(itr, {name, program});
        LogDebug("loaded program '%s' into %d", name.c_str(), program->getId());
        return program;
    }

    std::shared_ptr<Material> Renderer::loadMaterial(const std::string& name)
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

    void Renderer::defineProgram(const std::string& name, const ProgramDefinition& def)
    {
        auto itr = _programDefinitions.find(name);
        if(itr != _programDefinitions.end())
        {
            throw Exception(std::string("Program '")+name+"' already defined.");
        }
        _programDefinitions.insert(itr, {name, def});
    }

    void Renderer::defineMaterial(const std::string& name, const MaterialDefinition& def)
    {
        auto itr = _materialDefinitions.find(name);
        if(itr != _materialDefinitions.end())
        {
            throw Exception(std::string("Material '")+name+"' already defined.");
        }
        _materialDefinitions.insert(itr, {name, def});
    }

}
