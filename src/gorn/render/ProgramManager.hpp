#ifndef __gorn__ProgramManager__
#define __gorn__ProgramManager__

#include <map>
#include <memory>
#include <gorn/base/DefinitionManager.hpp>
#include <gorn/render/ProgramDefinition.hpp>

namespace gorn
{
    class VertexArray;
    class Shader;
    class Program;
    class FileManager;

    class ProgramManager
    {
    public:
        typedef ProgramDefinition Definition;
        typedef DefinitionManager<Definition> Definitions;
    private:
        static const char* kDefaultVertexShaderExtension;
        static const char* kDefaultFragmentShaderExtension;

        std::map<ShaderType, std::map<std::string, std::shared_ptr<Shader>>> _shaders;
        std::map<std::string, std::shared_ptr<Program>> _programs;     
        FileManager& _files;
        Definitions _definitions;

        std::shared_ptr<Shader> loadShader(
            const Definition& def, ShaderType type);

    public:
        ProgramManager(FileManager& files);

        const Definitions& getDefinitions() const;
        Definitions& getDefinitions();

        std::shared_ptr<Shader> loadShader(
            const std::string& name, ShaderType type);
        std::shared_ptr<Program> load(const std::string& name);

    };
}

#endif
