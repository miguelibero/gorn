#ifndef __gorn__MaterialManager__
#define __gorn__MaterialManager__

#include <map>
#include <memory>
#include <gorn/render/MaterialDefinition.hpp>
#include <gorn/base/DefinitionManager.hpp>

namespace gorn
{
    class ProgramManager;
    class TextureManager;
    class Material;

    class MaterialManager
    {
    public:
        typedef MaterialDefinition Definition;
        typedef DefinitionManager<MaterialDefinition> Definitions;
    private:
        std::map<std::string, std::shared_ptr<Material>> _materials;
        ProgramManager& _programs;
        TextureManager& _textures;
        Definitions _definitions;

    public:

        MaterialManager(ProgramManager& programs, TextureManager& textures);

        const Definitions& getDefinitions() const;
        Definitions& getDefinitions();

        bool validate(const std::string& name) const;
        std::shared_ptr<Material> load(const std::string& name);
    };

}

#endif
