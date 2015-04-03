#ifndef __gorn__ProgramUniformDefinition__
#define __gorn__ProgramUniformDefinition__

#include <string>
#include <gorn/render/UniformValue.hpp>

namespace gorn
{
    struct ProgramUniformDefinition
    {
        typedef UniformValue Value;
        std::string name;
        Value value;

        ProgramUniformDefinition(const char* name);
        ProgramUniformDefinition(const std::string& name="",
            const Value& value=Value());
        ProgramUniformDefinition& withValue(const Value& value);
    };
}

#endif
