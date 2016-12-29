#ifndef __gorn__FunctionFileLoader__
#define __gorn__FunctionFileLoader__

#include <functional>
#include <gorn/asset/FileLoader.hpp>
#include <buffer.hpp>

namespace gorn
{

    class FunctionFileLoader : public FileLoader
    {
    public:
        typedef std::function<buffer()> LoadFunction;
        typedef std::function<buffer(const std::string&)> StringLoadFunction;
        typedef std::function<bool()> ValidateFunction;
        typedef std::function<bool(const std::string&)> StringValidateFunction;
    private:
        StringLoadFunction _strLoad;
        LoadFunction _load;
        StringValidateFunction _strValidate;
        ValidateFunction _validate;
    public:
        FunctionFileLoader(const LoadFunction& load, const ValidateFunction& validate = nullptr);
        FunctionFileLoader(const StringLoadFunction& load, const ValidateFunction& validate = nullptr);
        FunctionFileLoader(const LoadFunction& load, const StringValidateFunction& validate = nullptr);
        FunctionFileLoader(const StringLoadFunction& load, const StringValidateFunction& validate = nullptr);
        bool validate(const std::string& name) const NOEXCEPT;     
        buffer load(const std::string& name) const;
    };
}

#endif
