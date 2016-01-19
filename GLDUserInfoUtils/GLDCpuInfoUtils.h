#ifndef GLDCPUINFOUTILS_H
#define GLDCPUINFOUTILS_H

#include "CBBNameSpace.h"

#include <windows.h>
#include <QString>

CBB_GLODON_BEGIN_NAMESPACE

    typedef struct CpuCoreCount
    {
        CpuCoreCount()
            : m_cpuLogicalCoreCount(-1)
            , m_cpuCoreCount(-1)
        {

        }

        int m_cpuLogicalCoreCount;   // CPU������
        int m_cpuCoreCount;          // �߼�CPU��
    } CoreCount;

    struct CpuInfo
    {
        QString   m_cpuBrand;              // CPU�̱�
        int       m_processorPackageCount; // ����cpu����
        CoreCount m_coreCount;             // ����
        ulong     m_processSpeed;          // cpu����ٶ�(��λMHZ)
    };

    /**
     * @brief ��ȡCPU�̱�
     * @return
     */
    QString getCpuBrand();

    /**
     * @brief ��ȡCPU�ٶ�,��Ƶ��
     * @return
     */
    ulong getCpuSpeed();

    /**
     * @brief ��ȡCPU�������
     * @return
     */
    ulong getCpuCount();

    /**
     * @brief ��ȡCPU����,��������������߼�����
     * @return
     */
    CoreCount getCpuCoreCount();

    /**
     * @brief ��ȡCPU��Ϣ
     * @return
     */
    CpuInfo getCpuInfo();

CBB_GLODON_END_NAMESPACE
#endif // GLDCPUINFOUTILS_H
