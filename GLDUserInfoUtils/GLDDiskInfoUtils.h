#ifndef GLDDISKINFOUTILS_H
#define GLDDISKINFOUTILS_H

#include <qt_windows.h>
#include <bitset>
#include <iostream>
#include <algorithm>
#include <utility>
#include <Winioctl.h>
#include <string>
#include <map>
#include <QVector>
#include <QString>
#include <QHash>

using namespace std;

namespace GLDDISKINFO
{
    enum FS
    {
        OTHER_FORMAT = 0,
        FAT32        = 1,
        NTFS         = 2
    };

    typedef struct SDiskInfomation
    {
        SDiskInfomation()
        {
            m_dwFreeMBytes = 0;
            m_dwTotalMBytes = 0;
        }

        QString m_strDiskName;   // ������(�̷�)
        QString m_strTypeName;   // ��������
        QString m_strFileSystem; // ������ʽ
        ulong   m_dwTotalMBytes; // �ܿռ�
        ulong   m_dwFreeMBytes;  // ���ÿռ�

    }DiskInfomation;

    class GLDDiskInfo
    {
    public:
        /**
         * @brief ��ȡӲ�����к�
         * @return
         */
        QString getDiskSerialNo();

        /**
         * @brief ��ȡ��������
         * @return
         */
        ulong getDriverNum();

        /**
         * @brief ��ȡ���з�����Ϣ
         * @return
         */
        QVector<DiskInfomation> getAllDriversInfo();

        /**
         * @brief ��ȡ������ʽ
         * @param dir  ������
         * @return
         */
        FS getFileSystemType(const QString& dir);

        /**
         * @brief ��ȡ��������
         * @param dir   ������
         * @return
         */
        QString getDriverTypeItem(const QString& dir);

        bool getLastVolumeInfo(DiskInfomation &diskInfo);
        bool getDiskSize(quint64 &llOfSectors, ulong dwDiskNum = 0);
        bool getDiskSize2(quint64 &llOfSectors, ulong dwDiskNum = 0);
        bool getVolumeSize(quint64 &llOfSectors, string volName);
        bool getFreeSpace(const QString& dir, qint64& ri64FreeBytesToCaller, qint64& ri64TotalBytes);

    private:
        bool getAllDriverName(ulong dwDrvNum, QVector<QString> & driveNameVct);
        void toLittleEndian(PUSHORT pWords, int nFirstIndex, int nLastIndex, LPTSTR pBuf);
        void trimStart(LPTSTR pBuf);
    };
}

#endif // GLDDISKINFOUTILS_H
