#ifndef __gorn__RenderContext__
#define __gorn__RenderContext__

#include <map>
#include <string>
#include <memory>
#include <gorn/render/Gl.hpp>
#include <gorn/render/ProgramDefinition.hpp>
#include <gorn/render/MaterialDefinition.hpp>
#include <gorn/render/TextureDefinition.hpp>
#include <gorn/render/Texture.hpp>
#include <gorn/render/Shader.hpp>
#include <gorn/render/Program.hpp>
#include <gorn/render/Material.hpp>
#include <gorn/asset/FileManager.hpp>
#include <gorn/asset/AssetManager.hpp>

namespace gorn
{
    class VertexArray;

    class RenderContext
    {
    private:
        std::map<std::string, std::shared_ptr<Texture>> _textures;
        std::map<ShaderType, std::map<std::string, std::shared_ptr<Shader>>> _shaders;
        std::map<std::string, std::shared_ptr<Program>> _programs;
        std::map<std::string, std::shared_ptr<Material>> _materials;
        std::map<std::string, ProgramDefinition> _programDefinitions;
        std::map<std::string, MaterialDefinition> _materialDefinitions;
        std::map<std::string, TextureDefinition> _textureDefinitions;
        
        std::shared_ptr<FileManager> _files;
        std::shared_ptr<AssetManager<Image>> _images;

    public:
        static const char* kDefaultTextureTag;
        static const char* kDefaultVertexShaderTag;
        static const char* kDefaultFragmentShaderTag;

        RenderContext();

        void setFileManager(const std::shared_ptr<FileManager>& mng);
        void setImageManager(const std::shared_ptr<AssetManager<Image>>& mng);
        const std::shared_ptr<FileManager>& getFileManager() const;
        const std::shared_ptr<AssetManager<Image>>& getImageManager() const;

        ProgramDefinition& defineProgram(const std::string& name);
        MaterialDefinition& defineMaterial(const std::string& name);
        TextureDefinition& defineTexture(const std::string& name);

        std::shared_ptr<Texture> loadTexture(const std::string& name);    
        std::shared_ptr<Shader> loadShader(const std::string& name, ShaderType type);
        std::shared_ptr<Program> loadProgram(const std::string& name);
        std::shared_ptr<Material> loadMaterial(const std::string& name);

        void drawArrays(const VertexArray& vao, GLsizei size, GLint offset=0);
        void drawElements(const VertexArray& vao, GLsizei size, GLenum type, GLint offset=0);
    };
}

#endif
