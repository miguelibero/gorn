#include <gorn/render/ProgramManager.hpp>

namespace gorn
{
    const char* ProgramManager::kDefaultVertexShaderTag = "vsh";
    const char* ProgramManager::kDefaultFragmentShaderTag = "fsh";

    ProgramManager::ProgramManager(FileManager& files):
    _files(files)
    {
    }

    std::shared_ptr<Shader> ProgramManager::loadShader(const std::string& name, ShaderType type)
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
        auto vertex = loadShader(def.getVertexShader(), ShaderType::Vertex);
        auto fragment = loadShader(def.getFragmentShader(), ShaderType::Fragment);

        auto program = std::make_shared<Program>(fragment, vertex);
        for(auto& name : def.getAttributes())
        {
            program->getAttribute(name);
        }
        for(auto& name : def.getUniforms())
        {
            program->getUniform(name);
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
            itr->second.withShader(name);
        }
        return itr->second;
    }
}
