#ifndef __gorn__FileLoader__
#define __gorn__FileLoader__

#include <string>
#include <gorn/base/Config.hpp>

class buffer;

namespace gorn
{
    class FileLoader
    {
    public:
        virtual ~FileLoader();

        /**
         * @return true if the file can be loaded
         */
        virtual bool validate(const std::string& name) const NOEXCEPT;

        /**
         * @return the new file data
         */
        virtual buffer load(const std::string& name) const = 0;
    };

}

#endif
