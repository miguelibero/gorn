

#include <gorn/asset/ObjMeshLoader.hpp>
#include <gorn/asset/Mesh.hpp>
#include <gorn/base/String.hpp>
#include <gorn/base/Exception.hpp>
#include <buffer.hpp>
#include <buffer_reader.hpp>
#include <algorithm>

namespace gorn
{
    const std::string kFacePrefix = "f";
    const std::string kPositionPrefix = "v";
    const std::string kNormalPrefix = "vn";
    const std::string kTexCoordPrefix = "vt";
    const std::string kComponentSeparator = " ";
    const std::string kFaceSeparator = "/";
    const char kCommentPrefix = '#';

    ObjMeshLoader::ObjMeshLoader() NOEXCEPT
    {
    }

    bool ObjMeshLoader::validate(const buffer& data) const NOEXCEPT
    {
        return !data.binary();
    }

    Mesh ObjMeshLoader::load(const buffer& data) const
    {
        buffer_reader in(data);
        std::string line;
        Mesh mesh;
        std::vector<std::vector<std::string>> faceLines;
        std::vector<std::vector<std::string>> positionLines;
        std::vector<std::vector<std::string>> normalLines;
        std::vector<std::vector<std::string>> texCoordsLines;
        while(!in.end())
        {
            in.readline(line);
            if(line.size() == 0 || line[0] == kCommentPrefix)
            {
                continue;
            }
            String::trim(line, " \t\r");
            auto parts = String::split(line, kComponentSeparator);
            parts.erase(std::remove_if(parts.begin(), parts.end(),
                [](const std::string& part){
                    return part.empty();
                }), parts.end());
            if(parts.empty())
            {
                continue;
            }
            auto prefix = parts[0];
            parts.erase(parts.begin(), parts.begin()+1);
            if(prefix == kFacePrefix)
            {
                faceLines.push_back(parts);
            }
            else if(prefix == kPositionPrefix)
            {
                positionLines.push_back(parts);
            }
            else if(prefix == kNormalPrefix)
            {
                normalLines.push_back(parts);
            }
            else if(prefix == kTexCoordPrefix)
            {
                texCoordsLines.push_back(parts);
            }
        }
        mesh.getElements().reserve(faceLines.size()*3);
        for(auto& parts : faceLines)
        {
            std::vector<Mesh::Element> face;
            face.resize(parts.size());
            size_t i=0;
            for(auto& part : parts)
            {
                auto& elm = face[i++];
                auto eparts = String::convertVector<MeshElement::idx_t>(
                    String::split(part, kFaceSeparator));
                if(eparts.size() > 0)
                {
                    elm.set(AttributeType::Position, eparts[0]-1);
                }
                if(eparts.size() > 1)
                {
                    elm.set(AttributeType::TexCoords, eparts[1]-1);
                }
                if(eparts.size() > 2)
                {
                    elm.set(AttributeType::Normal, eparts[2]-1);
                }
            }
            mesh.addFace(face);
        }
        mesh.reserveVertices<glm::vec3>(AttributeType::Position, positionLines.size());
        for(auto& parts : positionLines)
        {
            if(parts.size() < 3)
            {
                throw Exception("Position should contain 3 floats");
            }
            mesh.addVertex(AttributeType::Position, glm::vec3(
                String::convertTo<float>(parts[0]),
                String::convertTo<float>(parts[1]),
                String::convertTo<float>(parts[2])
            ));
        }
        mesh.reserveVertices<glm::vec3>(AttributeType::Normal, normalLines.size());
        for(auto& parts : normalLines)
        {
            if(parts.size() < 3)
            {
                throw Exception("Normal should contain 3 floats");
            }
            mesh.addVertex(AttributeType::Normal, glm::vec3(
                String::convertTo<float>(parts[0]),
                String::convertTo<float>(parts[1]),
                String::convertTo<float>(parts[2])
            ));
        }
        mesh.reserveVertices<glm::vec2>(AttributeType::TexCoords, texCoordsLines.size());
        for(auto& parts : texCoordsLines)
        {
            if(parts.size() < 2)
            {
                throw Exception("Texture should contain 2 floats");
            }
            mesh.addVertex(AttributeType::TexCoords, glm::vec2(
                String::convertTo<float>(parts[0]),
                String::convertTo<float>(parts[1])
            ));
        }
        return mesh;
    }
}
