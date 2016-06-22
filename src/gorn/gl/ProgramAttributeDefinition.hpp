#ifndef __gorn__ProgramAttributeDefinition__
#define __gorn__ProgramAttributeDefinition__

#include <string>
#include <buffer.hpp>
#include <gorn/gl/Enums.hpp>
#include <gorn/gl/AttributeTransformation.hpp>

namespace gorn
{
    class ProgramAttributeDefinition
    {
	public:
		typedef AttributeTransformation::Function Transformation;
	private:
        std::string _name;
		Transformation _transformation;
		buffer _defaultValue;
		size_t _count;
		BasicType _type;

	public:
        ProgramAttributeDefinition(const char* name="");

		ProgramAttributeDefinition& withDefaultValue(const buffer& data);
        ProgramAttributeDefinition& withTransformation(const Transformation& trans);
		ProgramAttributeDefinition& withType(const BasicType& type);
		ProgramAttributeDefinition& withCount(const size_t& count);

		const std::string& getName() const;
		const Transformation& getTransformation() const;
		const buffer& getDefaultValue() const;
		BasicType getType() const;
		size_t getCount() const;
    };
}

#endif
