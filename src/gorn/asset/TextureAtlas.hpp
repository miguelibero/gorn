

#ifndef __gorn__TextureAtlas__
#define __gorn__TextureAtlas__

#include <glm/glm.hpp>
#include <map>
#include <vector>
#include <string>

namespace gorn
{
    struct TextureRegion
    {
        glm::vec2 origin;
        glm::vec2 size;
        glm::vec2 original;
        glm::vec2 offset;

        void rotate();
    };

    class TextureAtlas
    {
    public:
        typedef TextureRegion Region;
    private:
        std::map<std::string, std::vector<Region>> _regions;
        std::string _texture;
    public:
        TextureAtlas();

        void setTexture(const std::string& name);
        const std::string& getTexture() const;

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
