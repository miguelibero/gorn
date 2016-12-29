#ifndef __gorn__DefinitionManager__
#define __gorn__DefinitionManager__

#include <unordered_map>
#include <memory>
#include <functional>
#include <gorn/base/String.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{
    template<typename D>
    class DefinitionManager
    {
    public:
        typedef D Definition;
        typedef std::function<Definition(const std::string&)> StringBuilder;
        typedef std::function<Definition()> Builder;
    private:
        std::unordered_map<std::string, Definition> _definitions;
        std::unordered_map<std::string, StringBuilder> _stringBuilders;
        std::unordered_map<std::string, Builder> _builders;

    public:
        DefinitionManager();

        Definition& get(const std::string& name);
        Definition get(const std::string& name) const;
        bool has(const std::string& name) const;
        void set(const std::string& name, const Definition& def);
        void set(const StringBuilder& builder);
        void set(const std::string& tag, const StringBuilder& builder);
        void set(const std::string& name, const Builder& builder);
        void set(const std::string& name, const std::string& alias);
    };

    template<typename D>
    DefinitionManager<D>::DefinitionManager()
    {
    }

    template<typename D>
    void DefinitionManager<D>::set(const std::string& name,
        const Definition& def)
    {
        _definitions[name] = def;
    }

    template<typename D>
    typename DefinitionManager<D>::Definition& DefinitionManager<D>::get(
        const std::string& name)
    {
        auto itr = _definitions.find(name);
        if(itr == _definitions.end())
        {
            auto parts = String::splitTag(name);
            auto bitr = _stringBuilders.find(parts.first);
            if(bitr == _stringBuilders.end())
            {
                bitr = _stringBuilders.find(String::kDefaultTag);
            }
            if(bitr != _stringBuilders.end())
            {
                auto def = bitr->second(name);
                itr = _definitions.insert(itr, { name, def });
            }
            else
            {
                itr = _definitions.insert(itr, { name, Definition() });
            }
        }
        return itr->second;
    }

    template<typename D>
    typename DefinitionManager<D>::Definition DefinitionManager<D>::get(
        const std::string& name) const
    {
        {
            auto itr = _definitions.find(name);
            if(itr != _definitions.end())
            {
                return itr->second;
            }
        }
        {
            auto itr = _builders.find(name);
            if(itr != _builders.end())
            {
                return itr->second();
            }
        }
        {
            auto parts = String::splitTag(name);
            auto itr = _stringBuilders.find(parts.first);
            if(itr == _stringBuilders.end())
            {
                itr = _stringBuilders.find(String::kDefaultTag);
            }
            if(itr != _stringBuilders.end())
            {
                return itr->second(name);
            }
        }
        throw new Exception("Could not find definition");
    }

    template<typename D>
    bool DefinitionManager<D>::has(const std::string& name) const
    {
        {
            auto itr = _definitions.find(name);
            if(itr != _definitions.end())
            {
                return true;
            }
        }
        {
            auto itr = _builders.find(name);
            if(itr != _builders.end())
            {
                return true;
            }
        }
        {
            auto parts = String::splitTag(name);
            auto itr = _stringBuilders.find(parts.first);
            if(itr == _stringBuilders.end())
            {
                itr = _stringBuilders.find(String::kDefaultTag);
            }
            if(itr != _stringBuilders.end())
            {
                return true;
            }
        }
        return false;
    }

    template<typename D>
    void DefinitionManager<D>::set(const StringBuilder& builder)
    {
        set(String::kDefaultTag, builder);
    }

    template<typename D>
    void DefinitionManager<D>::set(const std::string& prefix,
        const StringBuilder& builder)
    {
        _stringBuilders[prefix] = builder;
    }

    template<typename D>
    void DefinitionManager<D>::set(const std::string& name, const Builder& builder)
    {
        _builders[name] = builder;
    }

    template<typename D>
    void DefinitionManager<D>::set(const std::string& name, const std::string& alias)
    {
        set(name, [this]() {
            return load(alias);
        });
    }


}

#endif
