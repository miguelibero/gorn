
#include <gorn/gl/ProgramUniformDefinition.hpp>

namespace gorn
{
    ProgramUniformDefinition::ProgramUniformDefinition(
        const char* name):
    name(name)
    {
    }

    ProgramUniformDefinition::ProgramUniformDefinition(
        const std::string& name, const Value& value):
    name(name), value(value)
    {
    }

    ProgramUniformDefinition& ProgramUniformDefinition::withValue(
        const Value& v)
    {
        value = v;
        return *this;
    }
}

