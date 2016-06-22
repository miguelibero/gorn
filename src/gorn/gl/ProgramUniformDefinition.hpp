#ifndef __gorn__ProgramUniformDefinition__
#define __gorn__ProgramUniformDefinition__

#include <string>
#include <gorn/gl/UniformValue.hpp>

namespace gorn
{
    struct ProgramUniformDefinition
    {
	public:
        typedef UniformValue Value;
	private:
        std::string _name;
        Value _value;

	public:
        ProgramUniformDefinition(const char* name);
        ProgramUniformDefinition(const std::string& name = "",
            const Value& value=Value());

        ProgramUniformDefinition& withDefaultValue(const Value& value);

		const std::string& getName() const;
		const Value& getDefaultValue() const;
    };
}

#endif
