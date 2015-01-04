
#include <gorn/asset/CocosTextureAtlasLoader.hpp>
#include <gorn/asset/TextureAtlas.hpp>
#include <gorn/base/String.hpp>
#include <gorn/base/Data.hpp>
#include <rapidxml/rapidxml.hpp>

using namespace rapidxml;

namespace gorn {

    void loadXmlDocument(rapidxml::xml_document<>& doc, const Data& data)
    {
        Data buffer(data);
        DataOutputStream output(buffer);
        output.write("\0");
        doc.parse<0>(reinterpret_cast<char*>(buffer.ptr()));
    }

    void loadXmlDocument(rapidxml::xml_document<>& doc, Data&& data)
    {
        DataOutputStream output(data);
        output.write("\0");
        doc.parse<0>(reinterpret_cast<char*>(data.ptr()));
    }

    std::vector<int> loadIntegerParts(const std::string& value)
    {
        std::vector<std::string> strparts = String::split(value, ",");
        std::vector<int> parts;
        for(std::string& strpart : strparts)
        {
            String::trim(strpart, "{}");
            parts.push_back(String::convertTo<int>(strpart));
        }
        return parts;
    }

    void loadFrame(xml_node<>* dict, TextureRegion& region)
    {
        auto key = dict->first_node("key");
        while(key != nullptr)
        {
            std::string name = key->value();
            if(name == "frame")
            {
                std::string value = key->next_sibling()->value();
                std::vector<int> parts = loadIntegerParts(value);
                if(parts.size() != 4)
                {
                    throw std::runtime_error("Invalid frame value.");
                }
                region.origin.x = parts[0];
                region.origin.y = parts[1];
                region.size.x = parts[2];
                region.size.y = parts[3];

            }
            else if(name == "offset")
            {
                std::string value = key->next_sibling()->value();
                std::vector<int> parts = loadIntegerParts(value);
                if(parts.size() != 2)
                {
                    throw std::runtime_error("Invalid offset value.");
                }
                region.offset.x = parts[0];
                region.offset.y = parts[1];                    
            }
            else if(name == "rotated")
            {                
                std::string value = key->next_sibling()->name();
                if(value == "true")
                {
                    region.rotate();
                }
            }
            else if(name == "sourceSize")                
            {
                std::string value = key->next_sibling()->value();
                std::vector<int> parts = loadIntegerParts(value);
                if(parts.size() != 2)
                {
                    throw std::runtime_error("Invalid sourceSize value.");
                }
                region.original.x = parts[0];
                region.original.y = parts[1];  
            }
            key = key->next_sibling("key");
        }
        // in cocos2d offset origin is the center
        region.offset.x += (region.original.x-region.size.x)/2.0f;
        region.offset.y += (region.original.y-region.size.y)/2.0f;
    }

    void loadFrames(xml_node<>* dict, TextureAtlas& atlas)
    {
        auto key = dict->first_node("key");
        while(key != nullptr)
        {
            TextureRegion region;
            loadFrame(key->next_sibling("dict"), region);
            atlas.addRegion(key->value(), region);
            key = key->next_sibling("key");
        }
    }

    void loadMetadata(xml_node<>* dict, TextureAtlas& atlas)
    {
        auto key = dict->first_node("key");
        while(key != nullptr)
        {
            std::string name = key->value();
            if(name == "textureFileName")
            {
                auto value = key->next_sibling();
                atlas.setTexture(value->value());
            }
            key = key->next_sibling("key");
        }
    }

    CocosTextureAtlasLoader::CocosTextureAtlasLoader()
    {
    }
    
    bool CocosTextureAtlasLoader::validate(const Data& data) const
    {
        xml_document<> doc;
        loadXmlDocument(doc, data);
        return std::string(doc.first_node()->name()) == "plist";
    }

    TextureAtlas CocosTextureAtlasLoader::load(Data&& data) const
    {
        xml_document<> doc;
        loadXmlDocument(doc, data);
        
        TextureAtlas atlas;
        auto root = doc.first_node("plist");
        auto dict = root->first_node("dict");
        while (dict != nullptr)
        {
            auto key = dict->first_node("key");
            while(key != nullptr)
            {
                std::string name = key->value();
                if(name == "frames")
                {
                    loadFrames(key->next_sibling("dict"), atlas);
                }
                if(name == "metadata")
                {
                    loadMetadata(key->next_sibling("dict"), atlas);
                }
                key = key->next_sibling("key");
            }
            dict = dict->next_sibling("dict");
        }
        return atlas;
    }

}
