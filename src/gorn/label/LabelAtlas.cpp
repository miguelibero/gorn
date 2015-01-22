
#include <gorn/label/LabelAtlas.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn {

    LabelAtlas::LabelAtlas()
    {
    }

    const std::string& LabelAtlas::getMaterial(size_t page) const
    {
        return _materials.at(page);
    }

    void LabelAtlas::setMaterial(const std::string& value, size_t page)
    {
        if(_materials.size() <= page)
        {
            _materials.resize(page+1);
        }
        _materials[page] = value;
    }

    size_t LabelAtlas::getMaterialCount() const
    {
        return _materials.size();
    }

    void LabelAtlas::setRegion(const std::string& name, const Region& region)
    {
        _regions[name] = region;
    }

    const std::map<std::string, LabelAtlas::Region>& LabelAtlas::getRegions() const
    {
        return _regions;
    }

    const LabelAtlas::Region& LabelAtlas::getRegion(const std::string& name) const
    {
        auto itr = _regions.find(name);
        if(itr != _regions.end())
        {
            return itr->second;
        }
        throw Exception("Could not find region.");
    }

    bool LabelAtlas::hasRegion(const std::string& name) const
    {
        return _regions.find(name) != _regions.end();
    }
}
