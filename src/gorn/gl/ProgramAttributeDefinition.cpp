#include <gorn/gl/ProgramAttributeDefinition.hpp>
#include <gorn/gl/AttributeTransformation.hpp>

namespace gorn
{
    ProgramAttributeDefinition::ProgramAttributeDefinition(
		const Kind& kind):
        _kind(kind), _transformation(AttributeTransformation::create(kind.getType())),
		_count(0), _type(BasicType::None)
    {
    }

	ProgramAttributeDefinition&
		ProgramAttributeDefinition::withDefaultValue(const buffer& data)
	{
		_defaultValue = data;
		return *this;
	}

    ProgramAttributeDefinition&
        ProgramAttributeDefinition::withTransformation(const Transformation& trans)
    {
        _transformation = trans;
        return *this;
    }

	ProgramAttributeDefinition&
		ProgramAttributeDefinition::withBasicType(const BasicType& type)
	{
		_type = type;
		return *this;
	}

	ProgramAttributeDefinition&
		ProgramAttributeDefinition::withCount(const size_t& count)
	{
		_count = count;
		return *this;
	}

	const ProgramAttributeDefinition::Kind& ProgramAttributeDefinition::getKind() const
	{
		return _kind;
	}

	const ProgramAttributeDefinition::Transformation& ProgramAttributeDefinition::getTransformation() const
	{
		return _transformation;
	}

	const buffer& ProgramAttributeDefinition::getDefaultValue() const
	{
		return _defaultValue;
	}

	BasicType ProgramAttributeDefinition::getBasicType() const
	{
		return _type;
	}

	size_t ProgramAttributeDefinition::getCount() const
	{
		return _count;
	}
}

