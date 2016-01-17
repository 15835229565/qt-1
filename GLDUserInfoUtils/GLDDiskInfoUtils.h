#ifndef GLDDISKINFOUTILS_H
#define GLDDISKINFOUTILS_H

#include <qt_windows.h>
#include <bitset>
#include <Winioctl.h>
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
         * @brief ��ȡϵͳ�̷�
         * @return
         */
        QString getSystemVolumeName();

        /**
         * @brief ��ȡ��ǰ�̷�
         * @return
         */
        QString getCurrentVolumeName();

        /**
         * @brief ��ȡӲ�����к�
         * @return
         */
        QString getPhysicalDriveSerialNumber();

        /**
         * @brief ��ȡ��������
         * @return
         */
        ulong getVolumeNum();

        /**
         * @brief ��ȡ���з�����Ϣ
         * @return
         */
        QVector<DiskInfomation> getAllVolumeInfo();

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
        QString getVolumeTypeItem(const QString& dir);

        /**
         * @brief ��ȡ�����ռ���Ϣ
         * @param dir                      ������
         * @param ri64FreeBytesToCaller    ���ÿռ�
         * @param ri64TotalBytes           �����ܿռ�
         * @return
         */
        bool getVolumeSpace(const QString& dir, qint64& ri64FreeBytesToCaller, qint64& ri64TotalBytes);
        bool getDiskSize(quint64 &llOfSectors, ulong dwDiskNum = 0);
        bool getVolumeSize(quint64 &llOfSectors, string volName);

    private:
        bool getAllVolumeName(ulong dwDrvNum, QVector<QString> & driveNameVct);
    };
}

#endif // GLDDISKINFOUTILS_H
