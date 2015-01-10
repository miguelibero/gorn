#ifndef __gorn__MaterialManager__
#define __gorn__MaterialManager__

#include <map>
#include <string>
#include <memory>
#include <gorn/render/Gl.hpp>
#include <gorn/render/MaterialDefinition.hpp>
#include <gorn/render/Material.hpp>

namespace gorn
{
    class ProgramManager;
    class TextureManager;

    class MaterialManager
    {
    private:
        std::map<std::string, std::shared_ptr<Material>> _materials;
        std::map<std::string, MaterialDefinition> _definitions;
        std::string _defaultProgram;
        ProgramManager& _programs;
        TextureManager& _textures;

    public:
        MaterialManager(ProgramManager& programs, TextureManager& textures);

        void setDefaultProgram(const std::string& program);

        bool hasDefined(const std::string& name) const;
        MaterialDefinition& define(const std::string& name);
        MaterialDefinition& define(const std::string& name, const MaterialDefinition& def);
        std::shared_ptr<Material> load(const std::string& name);
    };

}

#endif
