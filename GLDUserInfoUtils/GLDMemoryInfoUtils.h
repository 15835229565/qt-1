#ifndef GLDMEMORYINFOUTILS_H
#define GLDMEMORYINFOUTILS_H

#include <windows.h>

namespace GLDMemoryInfo
{
    typedef struct PhysicalMemoryInfo
    {
        __int64     m_totalPhys;     // ���ڴ���,��λM
        __int64     m_availPhys;     // �����ڴ���,��λM
        int         m_usedPhys;      // �����ڴ�ٷֱ�,��Χ:0-100
    } PhysMemInfo;

    typedef struct VirtualMemoryInfo
    {
        __int64     m_totalVirtual;  // �������ڴ���,��λM
        __int64     m_availVirtual;  // ���������ڴ���,��λM
    } VirMemInfo;

    PhysMemInfo getPhysMemInfo();

    VirMemInfo getVirMemInfo();
}

#endif // GLDMEMORYINFOUTILS_H
