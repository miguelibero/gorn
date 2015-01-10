
#include <gorn/sprite/SpriteAtlas.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn {

    SpriteAtlas::SpriteAtlas()
    {
    }

    const std::string& SpriteAtlas::getMaterial() const
    {
        return _material;
    }

    void SpriteAtlas::setMaterial(const std::string& value)
    {
        _material = value;
    }

    void SpriteAtlas::addRegion(const std::string& name, const Region& region)
    {
        _regions[name].push_back(region);
    }

    void SpriteAtlas::setRegion(const std::string& name, const Region& region)
    {
        _regions[name] = {region};
    }

    void SpriteAtlas::setRegion(const std::string& name,
        const Region& region, size_t index)
    {
        auto& regions = _regions[name];
        if(regions.size() <= index)
        {
            regions.resize(index+1);
        }
        regions[index] = region;
    }

    const std::map<std::string, std::vector<SpriteAtlasRegion>>& SpriteAtlas::getRegions() const
    {
        return _regions;
    }


    const std::vector<SpriteAtlasRegion>& SpriteAtlas::getRegions(const std::string& name) const
    {
        auto itr = _regions.find(name);
        if(itr != _regions.end())
        {
            return itr->second;
        }
        throw Exception("Could not find regions.");
    }

    const SpriteAtlasRegion& SpriteAtlas::getRegion(const std::string& name, size_t index) const
    {
        auto itr = _regions.find(name);
        if(itr != _regions.end() && itr->second.size() > index)
        {
            return itr->second.at(index);
        }
        throw Exception("Could not find region.");
    }

    bool SpriteAtlas::hasRegion(const std::string& name) const
    {
        return _regions.find(name) != _regions.end();
    }
}
