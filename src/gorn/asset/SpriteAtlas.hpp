

#ifndef __gorn__SpriteAtlas__
#define __gorn__SpriteAtlas__

#include <map>
#include <vector>
#include <string>
#include <gorn/asset/SpriteRegion.hpp>
#include <gorn/render/Material.hpp>

namespace gorn
{
    class SpriteAtlas
    {
    public:
        typedef SpriteRegion Region;
    private:
        std::shared_ptr<Material> _material;
        std::map<std::string, std::vector<Region>> _regions;
    public:
        SpriteAtlas(const std::shared_ptr<Material>& = nullptr);

        const std::shared_ptr<Material>& getMaterial() const;
        void setMaterial(const std::shared_ptr<Material>& value);

        void addRegion(const std::string& name, const Region& region);
        void setRegion(const std::string& name, const Region& region);
        void setRegion(const std::string& name, const Region& region, size_t index);
        const std::map<std::string, std::vector<Region>>& getRegions() const;
        const Region& getRegion(const std::string& name, size_t index=0) const;
        const std::vector<Region>& getRegions(const std::string& name) const;
        bool hasRegion(const std::string& name) const;
    };
}

#endif
