/**********************************************************************
 *
 *  ������ COM�������ӿڶ���
 *
 *  ��ƣ�Zhangsk 2012.05.25
 *  ��ע��
 *  ��ˣ�
 *  ע�⣺
 *
 *  Copyright (c) 2012-2013 GlodonSoft Corporation
 *
 **********************************************************************/

#ifndef GLDCOMLOADERINTF_H
#define GLDCOMLOADERINTF_H

#include "GLDUnknwn.h"
//#include "GLDObject.h"

DEFINE_IID(IComLoader, "{A4CD87EA-E1DE-4588-A2E0-277C3AE2B536}");
DECLARE_INTERFACE_(IComLoader, IUnknown)
{
    /*! ��װһ��Ӧ�õ��೧
        \param pszName        ��������ƣ����鷽ʽ��com.grand.gsp
        \param pszVersion   ����İ汾
        \param pFactory     �೧����
        \return S_OK S_FALSE
    */
    STDMETHOD(InstallApplication)( wchar_t *pszName , wchar_t *pszVersion, IUnknown* pFactory ) PURE;
};

#endif // GLDCOMLOADERINTF_H
