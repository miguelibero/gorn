
#include <gorn/gl/Stencil.hpp>

namespace gorn
{

    Stencil::Stencil():
    _function(Function::Always),
    _failAction(Action::Keep),
    _passAction(Action::Keep),
    _mask(0xFF),
    _refValue(1)
    {
    }

    Stencil& Stencil::withFunction(Function f)
    {
        _function = f;
        return *this;
    }

    Stencil& Stencil::withFailAction(Action a)
    {
        _failAction = a;
        return *this;
    }

    Stencil& Stencil::withPassAction(Action a)
    {
        _passAction = a;
        return *this;
    }

    Stencil& Stencil::withMask(uint8_t mask)
    {
        _mask = mask;
        return *this;
    }

    Stencil& Stencil::withReferenceValue(int val)
    {
        _refValue = val;
        return *this;
    }

    bool Stencil::operator==(const Stencil& other) const
    {
        return _function == other._function
            && _failAction == other._failAction
            && _passAction == other._passAction
            && _mask == other._mask
            && _refValue == other._refValue;
    }

    bool Stencil::operator!=(const Stencil& other) const
    {
        return !(*this == other);
    }

    Stencil Stencil::current()
    {
        Stencil stencil;
        GLint val;
        glGetIntegerv(GL_STENCIL_FUNC, &val);
        stencil.withFunction(getStencilFunctionFromGl(val));
        glGetIntegerv(GL_STENCIL_WRITEMASK, &val);
        stencil.withMask(val);
        glGetIntegerv(GL_STENCIL_REF, &val);
        stencil.withReferenceValue(val);
        glGetIntegerv(GL_STENCIL_FAIL, &val);
        stencil.withFailAction(getStencilActionFromGl(val));
        glGetIntegerv(GL_STENCIL_PASS_DEPTH_PASS, &val);
        stencil.withPassAction(getStencilActionFromGl(val));
        return stencil;
    }

    void Stencil::apply()
    {
        glStencilFunc(getGlStencilFunction(_function), _refValue, 0xFF);
        checkGlError("setting stencil function");
        glStencilOp(getGlStencilAction(_failAction),
            getGlStencilAction(_failAction), getGlStencilAction(_passAction));
        checkGlError("setting stencil operation");
        glStencilMask(_mask);
        checkGlError("setting stencil mask");
    }

    StencilGuard::StencilGuard(const Stencil& stencil) :
    _old(Stencil::current()),
    _new(stencil)
    {
        _new.apply();
    }

    StencilGuard::~StencilGuard()
    {
        _old.apply();
    }
}
