
/**********************************************************************
 *
 *  ������ �깤�ߵ�Ԫ
 *
 *  ��ƣ�Zhangsk 2012.04.17
 *  ��ע��
 *  ��ˣ�
 *  ע�⣺
 *
 *  Copyright (c) 2012-2013 GlodonSoft Corporation
 *
 **********************************************************************/

#ifndef GLDMACROUTILS_H
#define GLDMACROUTILS_H



//�ַ�����������
#define makechar(x) #@x

//�Ѻ������Ϊһ���ַ�����
#define makestring(x) #x

//�������Ӳ����������궨��Ķ���βγ�һ��ʵ�ʲ�������
#define token_pasting(n) num##n

//#define IID_PPV_ARGS


extern "C++"
{
    template<typename T> void** IID_PPV_ARGS_Helper(T** pp) 
    {
        // make sure everyone derives from IUnknown
        static_cast<IUnknown*>(*pp);

        return reinterpret_cast<void**>(pp);
    }
}

#define IID_PPV_ARGS(ppType) __uuidof(**(ppType)), IID_PPV_ARGS_Helper(ppType)

#define IID_PPV_ARGS_Base(Type, Expr) IID_##Type, \
        reinterpret_cast<void**>(static_cast<Type **>(Expr))

//todo: ���������֧��#pragma once�ı�����
//#if defined (_MSC_VER) && (_MSC_VER >= 1020) && !defined(__midl)
//#pragma once
//#endif

#endif  //GLDMACROUTILS_H
