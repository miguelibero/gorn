#ifndef __gorn__ProgramManager__
#define __gorn__ProgramManager__

#include <map>
#include <string>
#include <memory>
#include <gorn/render/Gl.hpp>
#include <gorn/render/ProgramDefinition.hpp>
#include <gorn/render/Shader.hpp>
#include <gorn/render/Program.hpp>
#include <gorn/asset/FileManager.hpp>

namespace gorn
{
    class VertexArray;

    class ProgramManager
    {
    private:
        std::map<ShaderType, std::map<std::string, std::shared_ptr<Shader>>> _shaders;
        std::map<std::string, std::shared_ptr<Program>> _programs;
        std::map<std::string, ProgramDefinition> _definitions;
       
        FileManager& _files;

        std::shared_ptr<Shader> loadShader(
            const ProgramDefinition& def, ShaderType type);

    public:

        static const char* kDefaultVertexShaderTag;
        static const char* kDefaultFragmentShaderTag;

        ProgramManager(FileManager& files);

        ProgramDefinition& define(const std::string& name);
        std::shared_ptr<Shader> loadShader(
            const std::string& name, ShaderType type);
        std::shared_ptr<Program> load(const std::string& name);

    };
}

#endif
