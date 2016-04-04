#ifndef __gorn__ProgramAttributeDefinition__
#define __gorn__ProgramAttributeDefinition__

#include <string>
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

	public:
        ProgramAttributeDefinition(const char* name);
        ProgramAttributeDefinition(const std::string& name = "",
            const Transformation& trans=nullptr);
        ProgramAttributeDefinition& withTransformation(const Transformation& trans);

		const std::string& getName() const;
		const Transformation& getTransformation() const;
    };
}

#endif
