#ifndef GLDUSERINFOUTILS_H
#define GLDUSERINFOUTILS_H

#include <windows.h>
#include <QString>

namespace GLDSysInfo
{
    namespace GLDCpuInfo
    {
        typedef struct CpuCoreCount
        {
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

        QString getCpuBrand();

        ulong getCpuSpeed();

        int getCpuCount();

        CoreCount getCpuCoreCount();

        CpuInfo getCpuInfo();

        int getCpuUsage();
    }



    namespace GLDDiskInfo
    {
        typedef struct DiskSpaceInfo
        {
            double m_totalSpace;
            double m_availSpace;
            double m_usedSpace;
        } DiskSpaceInfo;

        typedef struct PartitionInfo
        {
            char                    chDrive;
            PARTITION_INFORMATION   info;
        } PartitionInfo, *LPPartitionInfo;


        typedef struct DiskInfo
        {
            int                        iPartitionSize;
            PPARTITION_INFORMATION     pPartitions;
        } DiskInfo, *LPDiskInfo;


        QString getDiskSerialNo();

        int getAllDiskPartitionInfo(LPDiskInfo* lpDisks);

        DiskSpaceInfo getDiskFreeSpace(QString driver);
    }
}



#endif // GLDUSERINFOUTILS_H
