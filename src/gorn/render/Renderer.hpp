#ifndef __gorn__Renderer__
#define __gorn__Renderer__

#include <map>
#include <string>
#include <memory>
#include <gorn/render/Gl.hpp>
#include <gorn/render/ProgramDefinition.hpp>
#include <gorn/render/MaterialDefinition.hpp>
#include <gorn/render/Texture.hpp>
#include <gorn/render/Shader.hpp>
#include <gorn/render/Program.hpp>
#include <gorn/render/Material.hpp>

namespace gorn
{
    class PlatformBridge;
    class VertexArray;

    class Renderer
    {
    private:
        typedef std::map<std::string, std::shared_ptr<Texture>> Textures;
        typedef std::map<ShaderType, std::map<std::string, std::shared_ptr<Shader>>> Shaders;
        typedef std::map<std::string, std::shared_ptr<Program>> Programs;
        typedef std::map<std::string, std::shared_ptr<Material>> Materials;
        typedef std::map<std::string, ProgramDefinition> ProgramDefinitions;
        typedef std::map<std::string, MaterialDefinition> MaterialDefinitions;

        Textures _textures;
        Shaders _shaders;
        Programs _programs;
        Materials _materials;
        ProgramDefinitions _programDefinitions;
        MaterialDefinitions _materialDefinitions;
        
        PlatformBridge* _bridge;

    public:
        static const char* kDefaultTextureTag;
        static const char* kDefaultVertexShaderTag;
        static const char* kDefaultFragmentShaderTag;

        Renderer();
        void setPlatformBridge(PlatformBridge& bridge);

        void defineProgram(const std::string& name, const ProgramDefinition& definition);
        void defineProgram(const std::string& name);
        void defineMaterial(const std::string& name, const MaterialDefinition& definition);

        std::shared_ptr<Texture> loadTexture(const std::string& name);    
        std::shared_ptr<Shader> loadShader(const std::string& name, ShaderType type);
        std::shared_ptr<Program> loadProgram(const std::string& name);
        std::shared_ptr<Material> loadMaterial(const std::string& name);

        void drawArrays(const VertexArray& vao, GLsizei size, GLint offset=0);

    };
}

#endif
