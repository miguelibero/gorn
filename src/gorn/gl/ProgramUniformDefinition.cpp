
#include <gorn/gl/ProgramUniformDefinition.hpp>

namespace gorn
{
    ProgramUniformDefinition::ProgramUniformDefinition(
        const char* name):
	_name(name)
    {
    }

    ProgramUniformDefinition::ProgramUniformDefinition(
        const std::string& name, const Value& value):
	_name(name), _value(value)
    {
    }

    ProgramUniformDefinition& ProgramUniformDefinition::withDefaultValue(
        const Value& v)
    {
		_value = v;
        return *this;
    }

	const std::string& ProgramUniformDefinition::getName() const
	{
		return _name;
	}

	const ProgramUniformDefinition::Value& ProgramUniformDefinition::getDefaultValue() const
	{
		return _value;
	}
}

