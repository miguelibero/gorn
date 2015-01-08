#include <gorn/render/ProgramManager.hpp>

namespace gorn
{
    const char* ProgramManager::kDefaultVertexShaderTag = "vsh";
    const char* ProgramManager::kDefaultFragmentShaderTag = "fsh";

    ProgramManager::ProgramManager(FileManager& files):
    _files(files)
    {
    }

    std::shared_ptr<Shader> ProgramManager::loadShader(
        const ProgramDefinition& def, ShaderType type)
    {
        if(def.hasShaderData(type))
        {
            return std::make_shared<Shader>(def.getShaderData(type), type);
        }
        else if(def.hasShaderFile(type))
        {
            return loadShader(def.getShaderFile(type), type);
        }
        else
        {
            return nullptr;
        }
    }

    std::shared_ptr<Shader> ProgramManager::loadShader(
        const std::string& name, ShaderType type)
    {
        auto& shaders = _shaders[type];
        auto itr = shaders.find(name);
        if(itr != shaders.end())
        {
            return itr->second;
        }
        std::string tname(name);
        if(type == ShaderType::Vertex)
        {
            FileManager::prefix(tname, kDefaultVertexShaderTag);
        }
        else if(type == ShaderType::Fragment)
        {
            FileManager::prefix(tname, kDefaultFragmentShaderTag);
        }
        auto data = _files.load(tname, false).get();
        auto shader = std::make_shared<Shader>(data, type);
        shaders.insert(itr, {name, shader});
        return shader;
    }

    std::shared_ptr<Program> ProgramManager::load(const std::string& name)
    {
        auto itr = _programs.find(name);
        if(itr != _programs.end())
        {
            return itr->second;
        }
        auto& def = define(name);
        auto vertex = loadShader(def, ShaderType::Vertex);
        auto fragment = loadShader(def, ShaderType::Fragment);

        auto program = std::make_shared<Program>(fragment, vertex);
        for(auto itr = def.getAttributes().begin();
            itr != def.getAttributes().end(); ++itr)
        {
            program->loadAttribute(itr->second, itr->first);
        }
        for(auto itr = def.getUniforms().begin();
            itr != def.getUniforms().end(); ++itr)
        {
            program->loadUniform(itr->second, itr->first);
        }
        _programs.insert(itr, {name, program});
        return program;
    }

    ProgramDefinition& ProgramManager::define(const std::string& name)
    {
        auto itr = _definitions.find(name);
        if(itr == _definitions.end())
        {
            itr = _definitions.insert(itr, {name, ProgramDefinition()});
            itr->second.withShaderFile(ShaderType::Vertex, name);
            itr->second.withShaderFile(ShaderType::Fragment, name);
        }
        return itr->second;
    }

}
