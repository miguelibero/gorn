#ifndef __gorn__ProgramAttributeDefinition__
#define __gorn__ProgramAttributeDefinition__

#include <string>

namespace gorn
{
    struct ProgramAttributeDefinition
    {
        std::string name;
        bool transformable;

        ProgramAttributeDefinition(const char* name);
        ProgramAttributeDefinition(const std::string& name="",
            bool transformable=false);
        ProgramAttributeDefinition& withTransformable(bool enabled);
    };
}

#endif
