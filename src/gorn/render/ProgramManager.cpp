#include <gorn/render/ProgramManager.hpp>
#include <gorn/render/Shader.hpp>
#include <gorn/render/Program.hpp>
#include <gorn/asset/FileManager.hpp>
#include <buffer.hpp>

namespace gorn
{
    const char* ProgramManager::kDefaultVertexShaderExtension = ".vsh";
    const char* ProgramManager::kDefaultFragmentShaderExtension = ".fsh";

    ProgramManager::ProgramManager(FileManager& files):
    _files(files)
    {
        getDefinitions().set([](const std::string& name){
            return Definition()
                .withShaderFile(ShaderType::Vertex,
                    name+kDefaultVertexShaderExtension)
                .withShaderFile(ShaderType::Fragment,
                    name+kDefaultFragmentShaderExtension);
        });
    }

    const ProgramManager::Definitions& ProgramManager::getDefinitions() const
    {
        return _definitions;
    }

    ProgramManager::Definitions& ProgramManager::getDefinitions()
    {
        return _definitions;
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

    bool ProgramManager::validateShader(
        const ProgramDefinition& def, ShaderType type) const
    {
        if(def.hasShaderData(type))
        {
            return true;
        }
        else if(def.hasShaderFile(type))
        {
            return validateShader(def.getShaderFile(type), type);
        }
        else
        {
            return false;
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
        auto data = _files.load(name, false).get();
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
        auto program = doLoad(name);
        _programs.insert(itr, {name, program});
        return program;
    }

    std::shared_ptr<Program> ProgramManager::doLoad(const std::string& name)
    {
        auto& def = getDefinitions().get(name);
        auto vertex = loadShader(def, ShaderType::Vertex);
        auto fragment = loadShader(def, ShaderType::Fragment);

        auto program = std::make_shared<Program>(vertex, fragment);
        program->loadDefinition(def);
        return program;
    }

    void ProgramManager::reload()
    {
        _shaders.clear();
        for(auto itr = _programs.begin(); itr != _programs.end(); ++itr)
        {
            *itr->second = std::move(*doLoad(itr->first));
        }
    }

    bool ProgramManager::validate(const std::string& name) const
    {
        auto itr = _programs.find(name);
        if(itr != _programs.end())
        {
            return true;
        }
        if(!getDefinitions().has(name))
        {
            return false;
        }
        auto def = getDefinitions().get(name);
        if(!validateShader(def, ShaderType::Vertex))
        {
            return false;
        }
        if(!validateShader(def, ShaderType::Fragment))
        {
            return false;
        }
        return true;
    }

    bool ProgramManager::validateShader(
        const std::string& name, ShaderType type) const
    {
        auto sitr = _shaders.find(type);
        if(sitr != _shaders.end())
        {
            auto itr = sitr->second.find(name);
            if(itr != sitr->second.end())
            {
                return true;
            }    
        }
        return _files.validate(name);
    }
}
