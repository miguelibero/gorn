#ifndef __gorn__FileLoader__
#define __gorn__FileLoader__

#include <memory>
#include <future>

namespace gorn
{
    class Data;

	class FileLoader
	{
    public:
		virtual ~FileLoader(){};

        /**
         * @return true if the file can be loaded
         */
        virtual bool validate(const std::string& name) const
        {
            return true;
        }

        /**
         * @return the new file data
         */
        virtual std::future<Data> load(const std::string& name) const = 0;
	};
}

#endif
