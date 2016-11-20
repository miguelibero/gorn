#ifndef __gorn__ProgramUniformDefinition__
#define __gorn__ProgramUniformDefinition__

#include <string>
#include <gorn/gl/UniformKind.hpp>
#include <gorn/gl/UniformValue.hpp>

namespace gorn
{
    struct ProgramUniformDefinition
    {
	public:
		typedef UniformKind Kind;
        typedef UniformValue Value;
	private:
		Kind _kind;
        Value _value;

	public:
		ProgramUniformDefinition(const Kind& kind = Kind());
        ProgramUniformDefinition(const Kind& kind, const Value& value);

        ProgramUniformDefinition& withDefaultValue(const Value& value);

		const Kind& getKind() const;
		const Value& getDefaultValue() const;
    };
}

#endif
