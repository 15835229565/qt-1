#include "GLDDiskInfoUtils.h"
#include <atlstr.h>

namespace GLDDISKINFO
{

    QString GLDDiskInfo::getSystemVolumeName()
    {
        WCHAR str[MAX_PATH];
        char sysDiskName[MAX_PATH * 2 + 1];
        GetSystemDirectory(str, MAX_PATH);
        WideCharToMultiByte(CP_ACP, 0, str, -1, sysDiskName, sizeof(sysDiskName), NULL, NULL);
        return QString(sysDiskName[0]);
    }

    QString GLDDiskInfo::getCurrentVolumeName()
    {
        /* Path of Module */
        WCHAR szModulePath[MAX_PATH];
        char curDiskName[MAX_PATH * 2 + 1];
        // Get current module handle
        HMODULE module = GetModuleHandle(0);
        // Get current file path
        GetModuleFileName(module, szModulePath, sizeof(szModulePath));
        WideCharToMultiByte(CP_ACP, 0, szModulePath, -1, curDiskName, sizeof(curDiskName), NULL, NULL);
        return QString(curDiskName[0]);
    }

    QString GLDDiskInfo::getPhysicalDriveSerialNumber()
    {
        DWORD dwResult = NO_ERROR;
        UINT nDriveNumber = 0;
        CString strSerialNumber;
        strSerialNumber.Empty();

        // Format physical drive path (may be '\\.\PhysicalDrive0', '\\.\PhysicalDrive1' and so on).
        CString strDrivePath;
        strDrivePath.Format(_T("\\\\.\\PhysicalDrive%u"), nDriveNumber);

        // call CreateFile to get a handle to physical drive
        HANDLE hDevice = ::CreateFile(strDrivePath, 0, FILE_SHARE_READ | FILE_SHARE_WRITE,
            NULL, OPEN_EXISTING, 0, NULL);

        if (INVALID_HANDLE_VALUE == hDevice)
            return "";

        // set the input STORAGE_PROPERTY_QUERY data structure
        STORAGE_PROPERTY_QUERY storagePropertyQuery;
        ZeroMemory(&storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY));
        storagePropertyQuery.PropertyId = StorageDeviceProperty;
        storagePropertyQuery.QueryType = PropertyStandardQuery;

        // get the necessary output buffer size
        STORAGE_DESCRIPTOR_HEADER storageDescriptorHeader = { 0 };
        DWORD dwBytesReturned = 0;
        if (!::DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY,
            &storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
            &storageDescriptorHeader, sizeof(STORAGE_DESCRIPTOR_HEADER),
            &dwBytesReturned, NULL))
        {
            dwResult = ::GetLastError();
            ::CloseHandle(hDevice);
            return "";
        }

        // allocate the necessary memory for the output buffer
        const DWORD dwOutBufferSize = storageDescriptorHeader.Size;
        BYTE* pOutBuffer = new BYTE[dwOutBufferSize];
        ZeroMemory(pOutBuffer, dwOutBufferSize);

        // get the storage device descriptor
        if (!::DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY,
            &storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
            pOutBuffer, dwOutBufferSize,
            &dwBytesReturned, NULL))
        {
            dwResult = ::GetLastError();
            delete[]pOutBuffer;
            ::CloseHandle(hDevice);
            return "";
        }

        // Now, the output buffer points to a STORAGE_DEVICE_DESCRIPTOR structure
        // followed by additional info like vendor ID, product ID, serial number, and so on.
        STORAGE_DEVICE_DESCRIPTOR* pDeviceDescriptor = (STORAGE_DEVICE_DESCRIPTOR*)pOutBuffer;
        const DWORD dwSerialNumberOffset = pDeviceDescriptor->SerialNumberOffset;
        if (dwSerialNumberOffset != 0)
        {
            // finally, get the serial number
            strSerialNumber = CString(pOutBuffer + dwSerialNumberOffset);
        }

        // perform cleanup and return
        delete[] pOutBuffer;
        ::CloseHandle(hDevice);

        std::basic_string<TCHAR> intermediate((LPCTSTR)strSerialNumber);
        return QString::fromStdWString(intermediate).trimmed();
    }

    QVector<DiskInfomation> GLDDiskInfo::getAllVolumeInfo()
    {
        QVector<DiskInfomation> diskInfoVect;
        QVector<QString> drvNameVct;
        qulonglong dwDrvNum = getVolumeNum();

        if (getAllVolumeName(dwDrvNum, drvNameVct))
        {
            QVector<QString>::const_iterator iter = drvNameVct.begin();
            for (; iter != drvNameVct.end(); ++iter)
            {
                //deal every driver
                DiskInfomation dskinf;
                //add disk name
                dskinf.m_strDiskName = *iter;
                //add disk type
                dskinf.m_strTypeName = getVolumeTypeItem(*iter);
                //add filesystem type
                switch (getFileSystemType(*iter))
                {
                case FAT32:
                    dskinf.m_strFileSystem = "FAT32";
                    break;
                case NTFS:
                    dskinf.m_strFileSystem = "NTFS";
                    break;
                default:
                    dskinf.m_strFileSystem = "OTHER_FORMAT";
                    break;
                }
                //add space information
                if (dskinf.m_strTypeName == QStringLiteral("���̷���") && dskinf.m_strFileSystem != "OTHER_FORMAT")
                {
                    qint64 i64TotalBytes = 0;
                    qint64 i64FreeBytes = 0;

                    if (getVolumeSpace(*iter, i64FreeBytes, i64TotalBytes))
                    {
                        dskinf.m_dwFreeMBytes = DWORD(i64FreeBytes / 1024 / 1024);
                        dskinf.m_dwTotalMBytes = DWORD(i64TotalBytes / 1024 / 1024);
                    }
                    else
                    {
                        dskinf.m_dwFreeMBytes = 0;
                        dskinf.m_dwTotalMBytes = 0;
                    }
                    //make vector data
                    diskInfoVect.push_back(dskinf);
                }
            }
        }

        return diskInfoVect;
    }

    ulong GLDDiskInfo::getVolumeNum()
    {
        ulong diskCount = 0;
        DWORD DiskInfo = GetLogicalDrives();
        //����GetLogicalDrives()�������Ի�ȡϵͳ���߼����������������������ص���һ��32λ�޷����������ݡ�
        while(DiskInfo)//ͨ��ѭ�������鿴ÿһλ�����Ƿ�Ϊ1�����Ϊ1�����Ϊ��,���Ϊ0����̲����ڡ�
        {
            if(DiskInfo & 1)//ͨ��λ������߼���������ж��Ƿ�Ϊ1
            {
                ++diskCount;
            }

            DiskInfo = DiskInfo >> 1;//ͨ��λ��������Ʋ�����֤ÿѭ��һ��������λ�������ƶ�һλ��
        }

        return diskCount;
    }

    //n��driver����A��\null����ʽ��ŵĻ�����4n���ַ������飬���룬ʵ�ʻ��4n��1���ַ������飬�ɼ�ĩβ����nullnull�����ַ�����
    bool GLDDiskInfo::getAllVolumeName(ulong dwDrvNum, QVector<QString> & driveNameVct)
    {
        //ͨ��GetLogicalDriveStrings()������ȡ�����������ַ�����Ϣ���ȡ�
        DWORD dwLength = GetLogicalDriveStringsA(0,NULL);

        //�û�ȡ�ĳ����ڶ�������һ��c�����ַ�������
        char* DStr = new char[dwLength];
        dwLength = GetLogicalDriveStringsA(dwLength, (LPSTR)DStr);
        if (!dwLength)
        {
            delete [] DStr;
            return false;
        }

        DWORD dwIndex = 0;

        while (dwIndex < dwDrvNum)
        {
            QString tmp(DStr + 4 * dwIndex);
            driveNameVct.push_back(tmp);
            dwIndex++;
        }

        delete [] DStr;
        return true;
    }

    QString GLDDiskInfo::getVolumeTypeItem(const QString& dir)
    {
        UINT uiType = GetDriveTypeA(dir.toStdString().c_str());
        switch (uiType)
        {
        case DRIVE_UNKNOWN:
            return QStringLiteral("δ֪�豸");
        case DRIVE_REMOVABLE:
            return QStringLiteral("���ƶ��豸");
        case DRIVE_FIXED:
            return QStringLiteral("���̷���");
        case DRIVE_REMOTE:
            return QStringLiteral("�������");
        case DRIVE_CDROM:
            return QStringLiteral("����");
        case DRIVE_RAMDISK:
            return QStringLiteral("�������");
        default:
            return QStringLiteral("��Ч·��");
        }
    }

    FS GLDDiskInfo::getFileSystemType(const QString &dir)
    {
        //���ڹ�����Ϣ�����ų�֮
        QString temp = dir[0];
        temp += ":";
        temp += "\\";

        char Volumelabel[255];
        DWORD SerialNumber;
        DWORD MaxCLength;
        DWORD FileSysFlag;
        char FileSysName[10];
        GetVolumeInformationA(temp.toStdString().c_str(), Volumelabel, 255, &SerialNumber,
                              &MaxCLength, &FileSysFlag, FileSysName,255);

        if (strcmp(FileSysName, "NTFS") == 0 )
        {
            return NTFS;
        }
        else if (strcmp(FileSysName, "FAT32") == 0 )
        {
            return FAT32;
        }
        else
        {
            return OTHER_FORMAT;
        }
    }

    bool GLDDiskInfo::getVolumeSpace(const QString& dir, qint64& ri64FreeBytesToCaller, qint64& ri64TotalBytes)
    {
        typedef bool (WINAPI *PGETDISKFREESPACEEX)(LPCSTR,
            PULARGE_INTEGER, PULARGE_INTEGER, PULARGE_INTEGER);

        PGETDISKFREESPACEEX pGetDiskFreeSpaceEx = NULL;
        qint64 i64FreeBytes;

        bool fResult = false;

        pGetDiskFreeSpaceEx = (PGETDISKFREESPACEEX) GetProcAddress(
            GetModuleHandleA("kernel32.dll"),
            "GetDiskFreeSpaceExA");

        if (pGetDiskFreeSpaceEx)
        {
            fResult = pGetDiskFreeSpaceEx(dir.toStdString().c_str(), (PULARGE_INTEGER)&ri64FreeBytesToCaller,
                (PULARGE_INTEGER)&ri64TotalBytes, (PULARGE_INTEGER)&i64FreeBytes);

            return fResult;
        }

        return fResult;
    }

    bool GLDDiskInfo::getDiskSize(quint64 &llOfSectors, ulong dwDiskNum/* = */)
    {
        string strDiskName = "\\\\.\\PHYSICALDRIVE";
        char szindx[2] = {'\0', '\0'};
        _itoa_s(dwDiskNum, szindx, 2, 10);
        strDiskName += szindx;

        HANDLE hDisk = CreateFileA(strDiskName.c_str(), /*GENERIC_READ | GENERIC_WRITE*/0,
            FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
            OPEN_EXISTING, NULL, NULL);
        if (INVALID_HANDLE_VALUE == hDisk)
        {
            GetLastError();
            return false;
        }

        bool bIsOk;
        DWORD dwReturnBytes = 0;
        GET_LENGTH_INFORMATION gli;

        bIsOk = DeviceIoControl(hDisk, IOCTL_DISK_GET_LENGTH_INFO, NULL, 0, &gli, sizeof(gli), &dwReturnBytes, NULL);
        if (!bIsOk)
        {
            GetLastError();
            if (INVALID_HANDLE_VALUE != hDisk)
            {
                CloseHandle(hDisk);
            }
            return false;
        }

        llOfSectors = gli.Length.QuadPart / 512;

        if (INVALID_HANDLE_VALUE != hDisk)
        {
            CloseHandle(hDisk);
        }
        return true;
    }

    bool GLDDiskInfo::getVolumeSize(quint64 &llOfSectors, string volName)
    {
        char szchar[2] = {volName[0], '\0'};
        string strVolumeName = szchar;
        strVolumeName = "\\\\.\\" + strVolumeName;
        strVolumeName += ":";

        HANDLE hVolume = CreateFileA(strVolumeName.c_str(), GENERIC_READ | GENERIC_WRITE,
            FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
            OPEN_EXISTING, NULL, NULL);
        if (INVALID_HANDLE_VALUE == hVolume)
        {
            GetLastError();
            return false;
        }

        bool bIsOk;
        DWORD dwReturnBytes = 0;
        GET_LENGTH_INFORMATION gli;

        bIsOk = DeviceIoControl(hVolume, IOCTL_DISK_GET_LENGTH_INFO, NULL, 0, &gli, sizeof(gli),&dwReturnBytes, NULL);
        if (!bIsOk)
        {
            GetLastError();
            if (INVALID_HANDLE_VALUE != hVolume)
            {
                CloseHandle(hVolume);
            }
            return false;
        }

        llOfSectors = gli.Length.QuadPart / 512;

        if (INVALID_HANDLE_VALUE != hVolume)
        {
            CloseHandle(hVolume);
        }
        return true;
    }
}


