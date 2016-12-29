
#include <gorn/asset/FunctionFileLoader.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{
    FunctionFileLoader::FunctionFileLoader(const LoadFunction& load, const ValidateFunction& validate):
    _load(load), _validate(validate)
    {
    }

    FunctionFileLoader::FunctionFileLoader(const StringLoadFunction& load, const ValidateFunction& validate):
    _strLoad(load), _validate(validate)
    {
    }

    FunctionFileLoader::FunctionFileLoader(const LoadFunction& load, const StringValidateFunction& validate):
    _load(load), _strValidate(validate)
    {
    }

    FunctionFileLoader::FunctionFileLoader(const StringLoadFunction& load, const StringValidateFunction& validate):
    _strLoad(load), _strValidate(validate)
    {
    }

    bool FunctionFileLoader::validate(const std::string& name) const NOEXCEPT
    {
        if(_validate != nullptr)
        {
            return _validate();
        }
        if(_strValidate != nullptr)
        {
            return _strValidate(name);
        }
        return true;
    }

    buffer FunctionFileLoader::load(const std::string& name) const
    {
        if(_load != nullptr)
        {
            return _load();
        }
        if(_strLoad != nullptr)
        {
            return _strLoad(name);
        }
        throw new Exception("No load function specified.");
    }

}
