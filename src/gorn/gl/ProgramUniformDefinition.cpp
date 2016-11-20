
#include <gorn/gl/ProgramUniformDefinition.hpp>

namespace gorn
{
	ProgramUniformDefinition::ProgramUniformDefinition(const Kind& kind):
	_kind(kind)
	{
	}

    ProgramUniformDefinition::ProgramUniformDefinition(
        const Kind& kind, const Value& value):
	_kind(kind), _value(value)
    {
    }

    ProgramUniformDefinition& ProgramUniformDefinition::withDefaultValue(
        const Value& v)
    {
		_value = v;
        return *this;
    }

	const ProgramUniformDefinition::Kind& ProgramUniformDefinition::getKind() const
	{
		return _kind;
	}

	const ProgramUniformDefinition::Value& ProgramUniformDefinition::getDefaultValue() const
	{
		return _value;
	}
}

