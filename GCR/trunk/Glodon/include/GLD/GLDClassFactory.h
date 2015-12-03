#ifndef GLDCLASSFACTORY_H
#define GLDCLASSFACTORY_H

#include "GLDObject.h"

/// �����೧�Ļ���
template < class T >
class GLDCOMMONSHARED_EXPORT GClassFactory: public GObject, public IClassFactory
{
public:
    DECLARE_IUNKNOWN

    STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void **ppv)
    {
        if (riid == IID_IClassFactory)
        {
            GetGInterface((IClassFactory*) this, ppv);
            return NOERROR;
        }
        else
        {
            return GObject::NonDelegatingQueryInterface( riid , ppv );
        }

    }

    STDMETHODIMP CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppvObject)
    {
        T* p = new T;
        return GetGInterface((LPUNKNOWN) (PGNDUNKNOWN) p, ppvObject);
    }

    STDMETHODIMP LockServer( BOOL /*fLock*/)
    {
        return S_OK;
    }
};

#endif // GLDCLASSFACTORY_H
