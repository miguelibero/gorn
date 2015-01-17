
#include <gorn/sprite/FntSpriteAtlasLoader.hpp>
#include <gorn/sprite/SpriteAtlas.hpp>
#include <gorn/sprite/SpriteAtlasRegion.hpp>
#include <gorn/base/Data.hpp>
#include <gorn/base/String.hpp>

namespace gorn {

    const char* FntSignature = "info ";
    const char FntAttrSepToken = ' ';
    const char FntAttrValSepToken = '=';
    const char FntAttrGroupToken = '"';

    FntSpriteAtlasLoader::FntSpriteAtlasLoader()
    {
    }

    bool FntSpriteAtlasLoader::validate(const Data& data) const
    {
        DataInputStream in(data);
        std::string line;
        in.read(line);
        return line.find(FntSignature) == 0;
    }

    std::map<std::string, std::string> parseData(const std::string& str)
    {
        std::size_t p = str.find(FntAttrSepToken);
        std::map<std::string, std::string> map;
        map[""] = str.substr(0, p);
        while(true)
        {
			if(p>=str.size())
			{
				break;
			}
            if(str[p] == FntAttrSepToken)
            {
                p++;
                continue;
            }
            std::size_t n = str.find(FntAttrSepToken, p);
            if(n == std::string::npos)
            {
                n = str.size()-1;
            }
            std::size_t s = str.find(FntAttrValSepToken, p);
            if(s == std::string::npos)
            {
                break;
            }            
            std::string name = str.substr(p, s-p);
            s++;
            if(str[s] == FntAttrGroupToken)
            {
                s++;
                n = str.find(FntAttrGroupToken, s);
                if(n == std::string::npos)
                {
                    break;
                }
            }
            std::string value = str.substr(s, n-s);
            map[name] = value;
            p = n;
        }
        return map;
    }

    SpriteAtlas FntSpriteAtlasLoader::load(Data&& data) const
    {
        SpriteAtlas atlas;
        DataInputStream in(data);
        std::vector<std::string> pages;
        while(!in.reachedEnd())
        {
            std::string line;
            in.read(line);
            auto map = parseData(line);
            auto name = map[""];
            map.erase("");
            if(name == "info" || name == "common")
            {
                for(auto itr = map.begin(); itr != map.end(); ++itr)
                {
                    atlas.setProperty(itr->first, itr->second);
                }
            }            
            else if(name == "page")
            {
                auto i = String::convertTo<size_t>(map["id"]);
                atlas.setMaterial(map["file"], i);
            }
            else if(name == "char")
            {
                SpriteAtlasRegion region;
                region.setOrigin(SpriteAtlasRegion::Origin::TopLeft);
                region.setPosition(
                    String::convertTo<SpriteAtlasRegion::value_type>(map["x"]),
                    String::convertTo<SpriteAtlasRegion::value_type>(map["y"])
                );
                region.setSize(
                    String::convertTo<SpriteAtlasRegion::value_type>(map["width"]),
                    String::convertTo<SpriteAtlasRegion::value_type>(map["height"])
                );
                /*
                region.setOffset(
                    String::convertTo<SpriteAtlasRegion::value_type>(map["xoffset"]),
                    String::convertTo<SpriteAtlasRegion::value_type>(map["yoffset"])
                );
                */
                // TODO: what is xadvance?
                std::string name = map["letter"];
                if(name == "space")
                {
                    name = " ";
                }
                region.setPage(String::convertTo<size_t>(map["page"]));
                atlas.setRegion(name, region);
            }
        }
        
        return atlas;
    }


}
