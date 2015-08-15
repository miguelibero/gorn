#include <gorn/gl/FeatureState.hpp>
#include <algorithm>

namespace gorn
{
    FeatureState::FeatureState()
    {
    }

    FeatureState& FeatureState::withEnable(FeatureType type)
    {
        auto itr = std::find(_enables.begin(),
            _enables.end(), type);
        if(itr == _enables.end())
        {
            _enables.insert(itr, type);
        }
        return *this;
    }

    FeatureState& FeatureState::withDisable(FeatureType type)
    {
        auto itr = std::find(_disables.begin(),
            _disables.end(), type);
        if(itr == _disables.end())
        {
            _disables.insert(itr, type);
        }
        return *this;
    }

    bool FeatureState::operator==(const FeatureState& other) const
    {
        return true
            && std::is_permutation(_enables.begin(),
                _enables.end(), other._enables.begin())
            && std::is_permutation(_disables.begin(),
                _disables.end(), other._disables.begin());
    }

    bool FeatureState::operator!=(const FeatureState& other) const
    {
        return !(*this == other);
    }

    FeatureState FeatureState::current()
    {
        FeatureState state;
        return state;
    }

    void FeatureState::apply()
    {
        for(auto& f : _enables)
        {            
            auto glf = getGlFeature(f);
            if(glf != 0)
            {
                glEnable(glf);
            }
        }
        for(auto& f : _disables)
        {
            auto glf = getGlFeature(f);
            if(glf != 0)
            {
                glDisable(glf);
            }
        }
    }

    FeatureStateGuard::FeatureStateGuard(const FeatureState& state) :
    _old(FeatureState::current()),
    _new(state)
    {
        _new.apply();
    }

    FeatureStateGuard::~FeatureStateGuard()
    {
        _old.apply();
    }

}
