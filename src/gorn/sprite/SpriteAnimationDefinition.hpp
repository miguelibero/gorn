

#ifndef __gorn__SpriteAnimationDefinition__
#define __gorn__SpriteAnimationDefinition__

#include <string>
#include <vector>

namespace gorn {


    class SpriteAnimationDefinition
    {
    private:
        std::vector<std::string> _frames;
        std::string _atlas;
        double _frameDuration;
    public:
        SpriteAnimationDefinition();

        SpriteAnimationDefinition& withAtlas(const std::string& atlas);
        SpriteAnimationDefinition& withFrames(const std::string& frame);
        SpriteAnimationDefinition& withFrameDuration(double duration);

        const std::string& getAtlas() const;
        const std::vector<std::string>& getFrames() const;
        double getFrameDuration() const;
    };

}

#endif
