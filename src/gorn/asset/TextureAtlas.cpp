
#include <gorn/asset/TextureAtlas.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn {

    TextureAtlas::TextureAtlas()
    {
    }

    const std::string& TextureAtlas::getTexture() const
    {
        return _texture;
    }    

    void TextureAtlas::setTexture(const std::string& texture)
    {
        _texture = texture;
    }

    void TextureAtlas::addRegion(const std::string& name, const Region& region)
    {
        _regions[name].push_back(region);
    }

    void TextureAtlas::setRegion(const std::string& name, const Region& region)
    {
        _regions[name] = {region};
    }

    void TextureAtlas::setRegion(const std::string& name,
        const Region& region, size_t index)
    {
        _regions[name][index] = region;
    }

    const std::map<std::string, std::vector<TextureRegion>>& TextureAtlas::getRegions() const
    {
        return _regions;
    }


    const std::vector<TextureRegion>& TextureAtlas::getRegions(const std::string& name) const
    {
        auto itr = _regions.find(name);
        if(itr != _regions.end())
        {
            return itr->second;
        }
        throw std::runtime_error("Could not find regions.");
    }

    const TextureRegion& TextureAtlas::getRegion(const std::string& name, size_t index) const
    {
        auto itr = _regions.find(name);
        if(itr != _regions.end() && itr->second.size() > index)
        {
            return itr->second.at(index);
        }
        throw std::runtime_error("Could not find region.");
    }

    bool TextureAtlas::hasRegion(const std::string& name) const
    {
        return _regions.find(name) != _regions.end();
    }

    void TextureRegion::rotate()
    {
        // TODO
    }
}
