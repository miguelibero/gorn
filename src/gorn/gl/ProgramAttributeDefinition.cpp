#include <gorn/gl/ProgramAttributeDefinition.hpp>
#include <gorn/gl/AttributeTransformation.hpp>

namespace gorn
{
    ProgramAttributeDefinition::ProgramAttributeDefinition(
        const char* name):
        _name(name), _transformation(AttributeTransformation::create(name)),
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
		ProgramAttributeDefinition::withType(const BasicType& type)
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

	const std::string& ProgramAttributeDefinition::getName() const
	{
		return _name;
	}

	const ProgramAttributeDefinition::Transformation& ProgramAttributeDefinition::getTransformation() const
	{
		return _transformation;
	}

	const buffer& ProgramAttributeDefinition::getDefaultValue() const
	{
		return _defaultValue;
	}

	BasicType ProgramAttributeDefinition::getType() const
	{
		return _type;
	}

	size_t ProgramAttributeDefinition::getCount() const
	{
		return _count;
	}
}

