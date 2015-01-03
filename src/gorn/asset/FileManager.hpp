#ifndef __gorn__FileManager__
#define __gorn__FileManager__

#include <memory>
#include <string>
#include <future>
#include <vector>
#include <map>
#include <gorn/asset/FileLoader.hpp>

namespace gorn
{
    class Data;

	class FileManager
	{
    public:
        typedef FileLoader Loader;
	private:
        static const char* kDefaultTag;
        static const char* kTagSeparator;

		std::map<std::string, std::vector<std::shared_ptr<Loader>>> _loaders;
        std::future<Data> load(const std::shared_ptr<Loader>& loader, const std::string& name);

	public:
	    std::future<Data> load(const std::string& tag, const std::string& name);
	    std::future<Data> load(const std::string& name);

	    void addLoader(const std::string& tag, std::unique_ptr<Loader>&& loader);
        void addLoader(std::unique_ptr<Loader>&& loader);

        template<typename L, typename... Args>
        void addLoader(const std::string& tag, Args&&... args);
        template<typename L, typename... Args>
        void addDefaultLoader(Args&&... args);
	};

    template<typename L, typename... Args>
    void FileManager::addLoader(const std::string& tag, Args&&... args)
    {
        addLoader(tag, std::unique_ptr<Loader>(new L(std::forward<Args>(args)...)));
    }

    template<typename L, typename... Args>
    void FileManager::addDefaultLoader(Args&&... args)
    {
        addLoader(std::unique_ptr<Loader>(new L(std::forward<Args>(args)...)));
    }
}

#endif
