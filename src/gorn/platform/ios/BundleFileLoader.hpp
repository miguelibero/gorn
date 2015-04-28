#ifndef __gorn__BundleFileLoader__
#define __gorn__BundleFileLoader__

#include <gorn/asset/FileLoader.hpp>

namespace gorn {
    
    class BundleFileLoader : public FileLoader
    {
    private:
        static const char* kPlaceholder;
        
        std::string _nameTemplate;
        std::string getName(const std::string& name) const NOEXCEPT;
    public:
        BundleFileLoader(const std::string& nameTemplate=kPlaceholder) NOEXCEPT;
        virtual bool validate(const std::string& name) const NOEXCEPT override;
        virtual buffer load(const std::string& name) const override;
    };
}


#endif
