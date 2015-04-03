#include <gorn/render/ProgramAttributeDefinition.hpp>

namespace gorn
{
    ProgramAttributeDefinition::ProgramAttributeDefinition(
        const char* name):
        name(name), transformable(false)
    {
    }

    ProgramAttributeDefinition::ProgramAttributeDefinition(
        const std::string& name, bool transformable):
        name(name), transformable(transformable)
    {
    }

    ProgramAttributeDefinition&
        ProgramAttributeDefinition::withTransformable(bool enabled)
    {
        transformable = enabled;
        return *this;
    }
}

