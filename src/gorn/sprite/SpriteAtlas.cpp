
#include <gorn/sprite/SpriteAtlas.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn {

    SpriteAtlas::SpriteAtlas()
    {
    }

    const std::string& SpriteAtlas::getMaterial(size_t page) const
    {
        return _materials.at(page);
    }

    void SpriteAtlas::setMaterial(const std::string& value, size_t page)
    {
        if(_materials.size() <= page)
        {
            _materials.resize(page+1);
        }
        _materials[page] = value;
    }

    size_t SpriteAtlas::getMaterialCount() const
    {
        return _materials.size();
    }

    void SpriteAtlas::setProperty(const std::string& name, const std::string& value)
    {
        _properties[name] = value;
    }

    const std::string& SpriteAtlas::getProperty(const std::string& name) const
    {
        return _properties.at(name);
    }

    bool SpriteAtlas::hasProperty(const std::string& name) const
    {
        return _properties.find(name) != _properties.end();
    }

    const std::map<std::string, std::string>& SpriteAtlas::getProperties() const
    {
        return _properties;
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
