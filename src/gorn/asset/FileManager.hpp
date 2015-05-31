#ifndef __gorn__FileManager__
#define __gorn__FileManager__

#include <memory>
#include <string>
#include <future>
#include <vector>
#include <map>
#include <gorn/asset/FileLoader.hpp>
#include <gorn/base/Config.hpp>

class buffer;

namespace gorn
{
	class FileManager
	{
    public:
        typedef FileLoader Loader;
        typedef std::map<std::string, buffer> Files;
	private:
		std::shared_ptr<Files> _files;
		std::map<std::string, std::vector<std::shared_ptr<Loader>>> _loaders;
        std::future<buffer> load(const std::shared_ptr<Loader>& loader,
            const std::string& name, bool cache);

        std::vector<std::shared_ptr<Loader>>
            getLoaders(const std::pair<std::string,std::string>& parts)
            const NOEXCEPT;
	public:
        FileManager();

        bool validate(const std::string& name) const NOEXCEPT;
	    std::future<buffer> load(const std::string& name, bool cache=false) NOEXCEPT;
        void preload(const std::string& name, buffer&& data) NOEXCEPT;
        bool unload(const std::string& name) NOEXCEPT;
        void unloadAll() NOEXCEPT;

	    void addLoader(const std::string& tag,
            std::unique_ptr<Loader>&& loader) NOEXCEPT;
        void addLoader(std::unique_ptr<Loader>&& loader) NOEXCEPT;

        template<typename L, typename... Args>
        void makeLoader(const std::string& tag, Args&&... args) NOEXCEPT;
        template<typename L, typename... Args>
        void makeDefaultLoader(Args&&... args) NOEXCEPT;

	};

    template<typename L, typename... Args>
    void FileManager::makeLoader(const std::string& tag, Args&&... args) NOEXCEPT
    {
        addLoader(tag, std::unique_ptr<Loader>(new L(std::forward<Args>(args)...)));
    }

    template<typename L, typename... Args>
    void FileManager::makeDefaultLoader(Args&&... args) NOEXCEPT
    {
        addLoader(std::unique_ptr<Loader>(new L(std::forward<Args>(args)...)));
    }
}

#endif
