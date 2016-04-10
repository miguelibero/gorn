#include <gorn/gl/ProgramAttributeDefinition.hpp>
#include <gorn/gl/AttributeTransformation.hpp>

namespace gorn
{
    ProgramAttributeDefinition::ProgramAttributeDefinition(
        const char* name):
        _name(name), _transformation(AttributeTransformation::create(name))
    {
    }

    ProgramAttributeDefinition::ProgramAttributeDefinition(
        const std::string& name, const Transformation& trans):
		_name(name), _transformation(trans)
    {
    }

    ProgramAttributeDefinition&
        ProgramAttributeDefinition::withTransformation(const Transformation& trans)
    {
        _transformation = trans;
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
}

