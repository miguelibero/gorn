#ifndef __gorn__Stencil__
#define __gorn__Stencil__

#include <gorn/gl/Enums.hpp>
#include <cstdint>

namespace gorn
{
    class Stencil
    {
    public:
        typedef StencilFunction Function;
        typedef StencilAction Action;
    private:
        Function _function;
        Action _failAction;
        Action _passAction;
        uint8_t _mask;
        int _refValue;
    public:
        Stencil();

        Stencil& withFunction(Function f);
        Stencil& withFailAction(Action a);
        Stencil& withPassAction(Action a);
        Stencil& withMask(uint8_t mask);
        Stencil& withReferenceValue(int val);

        bool operator==(const Stencil& other) const;
        bool operator!=(const Stencil& other) const;

        void apply();

        static Stencil current();
        
    };

    class StencilGuard
    {
    public:
        Stencil _old;
        Stencil _new;
    public:
        StencilGuard(const Stencil& stencil);
        ~StencilGuard();
    };
}

#endif
