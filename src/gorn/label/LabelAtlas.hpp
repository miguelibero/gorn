

#ifndef __gorn__LabelAtlas__
#define __gorn__LabelAtlas__

#include <map>
#include <vector>
#include <string>
#include <gorn/label/LabelAtlasRegion.hpp>
#include <gorn/base/String.hpp>

namespace gorn
{
    class LabelAtlas
    {
    public:
        typedef LabelAtlasRegion Region;
    private:
        std::vector<std::string> _materials;
        std::map<std::string, Region> _regions;
        std::map<std::string, std::string> _properties;
    public:
        LabelAtlas();

        const std::string& getMaterial(size_t page=0) const;
        void setMaterial(const std::string& value, size_t page=0);
        size_t getMaterialCount() const;

        void setRegion(const std::string& name, const Region& region);
        const std::map<std::string, Region>& getRegions() const;
        const Region& getRegion(const std::string& name) const;
        bool hasRegion(const std::string& name) const;
    };

}

#endif
