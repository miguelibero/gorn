

#ifndef __gorn__TextureAtlas__
#define __gorn__TextureAtlas__

#include <glm/glm.hpp>
#include <map>
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
    private:
        std::map<std::string, TextureRegion> _regions;
        std::string _texture;
    public:
        TextureAtlas();

        void setTexture(const std::string& name);
        const std::string& getTexture() const;

        void setRegion(const std::string& name, const TextureRegion& region);
        const std::map<std::string, TextureRegion>& getRegions() const;
        const TextureRegion& getRegion(const std::string& name) const;
        bool hasRegion(const std::string& name) const;
    };
}

#endif
