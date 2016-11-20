#ifndef __gorn__ProgramAttributeDefinition__
#define __gorn__ProgramAttributeDefinition__

#include <string>
#include <buffer.hpp>
#include <gorn/gl/Enums.hpp>
#include <gorn/gl/AttributeTransformation.hpp>
#include <gorn/gl/AttributeKind.hpp>

namespace gorn
{
    class ProgramAttributeDefinition
    {
	public:
		typedef AttributeTransformation::Function Transformation;
		typedef AttributeKind Kind;
	private:
		Kind _kind;
		Transformation _transformation;
		buffer _defaultValue;
		size_t _count;
		BasicType _type;

	public:
        ProgramAttributeDefinition(const Kind& kind = Kind());

		ProgramAttributeDefinition& withDefaultValue(const buffer& data);
        ProgramAttributeDefinition& withTransformation(const Transformation& trans);
		ProgramAttributeDefinition& withBasicType(const BasicType& type);
		ProgramAttributeDefinition& withCount(const size_t& count);

		const Kind& getKind() const;
		const Transformation& getTransformation() const;
		const buffer& getDefaultValue() const;
		BasicType getBasicType() const;
		size_t getCount() const;
    };
}

#endif
