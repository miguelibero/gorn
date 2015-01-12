

#ifndef __gorn__SpriteAtlas__
#define __gorn__SpriteAtlas__

#include <map>
#include <vector>
#include <string>
#include <gorn/sprite/SpriteAtlasRegion.hpp>
#include <gorn/base/String.hpp>

namespace gorn
{
    class SpriteAtlas
    {
    public:
        typedef SpriteAtlasRegion Region;
    private:
        std::vector<std::string> _materials;
        std::map<std::string, std::vector<Region>> _regions;
        std::map<std::string, std::string> _properties;
    public:
        SpriteAtlas();

        const std::string& getMaterial(size_t page=0) const;
        void setMaterial(const std::string& value, size_t page=0);
        size_t getMaterialCount() const;

        void setProperty(const std::string& name, const std::string& value);
        const std::string& getProperty(const std::string& name) const;
        bool hasProperty(const std::string& name) const;
        const std::map<std::string, std::string>& getProperties() const;
        template<typename T>
        const T& getProperty(const std::string& name);

        void addRegion(const std::string& name, const Region& region);
        void setRegion(const std::string& name, const Region& region);
        void setRegion(const std::string& name, const Region& region, size_t index);
        const std::map<std::string, std::vector<Region>>& getRegions() const;
        const Region& getRegion(const std::string& name, size_t index=0) const;
        const std::vector<Region>& getRegions(const std::string& name) const;
        bool hasRegion(const std::string& name) const;
    };

    template<typename T>
    const T& SpriteAtlas::getProperty(const std::string& name)
    {
        return String::convertTo<T>(getProperty(name));
    }
}

#endif
