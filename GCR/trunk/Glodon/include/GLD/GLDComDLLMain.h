
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the GDLLEX_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// GDLLEX_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

#ifndef WIN32
//TODO: Linux, Mac OS
#else    //WIN32


#ifdef GWP_BCB    //Glodon Work Platform �������ƽ̨
#include <vcl.h>
#include <windows.h> //GWP_BCB c++builder
#pragma hdrstop
#pragma argsused


//Project��Ҫ��������� _DEFINE_INTERFACE_
//Project��ҪDependencis COMExt���Project
//�ӿڶ��嶼��xapp.h�н��У�COMExt��Ŀ��
#ifdef GDLLEX_EXPORTS
#define GDLLEX_API __declspec(dllexport)
#else
#define GDLLEX_API __declspec(dllimport)
#endif

extern "C" GDLLEX_API int __cdecl LoadGCOMExtension( void* );


#else    //GWP_BCB

#ifdef GDLLEX_EXPORTS
#   define GDLLEX_API __declspec(dllexport)
#else
#   define GDLLEX_API __declspec(dllimport)
#endif

extern "C" GDLLEX_API int __cdecl _LoadGCOMExtension( void* );

#endif    //GWP_BCB
#endif    //WIN32
