#ifndef GLDMEMORYINFOUTILS_H
#define GLDMEMORYINFOUTILS_H

#include "CBBNameSpace.h"

#include <windows.h>
#include <qglobal.h>

CBB_GLODON_BEGIN_NAMESPACE

    typedef struct PhysicalMemoryInfo
    {
        qint64     m_totalPhys;     // ���ڴ���,��λM
        qint64     m_availPhys;     // �����ڴ���,��λM
        int        m_usedPhys;      // �����ڴ�ٷֱ�,��Χ:0-100
    } PhysMemInfo;

    typedef struct VirtualMemoryInfo
    {
        qint64     m_totalVirtual;  // �������ڴ���,��λM
        qint64     m_availVirtual;  // ���������ڴ���,��λM
    } VirMemInfo;

    /**
     * @brief ��ȡ�����ڴ���Ϣ
     * @return
     */
    PhysMemInfo getPhysMemInfo();

    /**
     * @brief ��ȡ�����ڴ���Ϣ
     * @return
     */
    VirMemInfo getVirMemInfo();

CBB_GLODON_END_NAMESPACE

#endif // GLDMEMORYINFOUTILS_H
