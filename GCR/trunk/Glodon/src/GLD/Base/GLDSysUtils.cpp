#include "GLDSysUtils.h"

#include <QStandardPaths>

#include "GLDGlobal.h"
#include "GLDVector.h"
#include "GLDStrUtils.h"
#include "GLDSettings.h"
#include "GLDDir.h"

#ifdef WIN32
#   include <windows.h>
#   include <nb30.h>
#   include <ShlObj.h>
#   ifdef _MSC_VER
#       pragma comment(lib, "NETAPI32.LIB")
#   endif
#else
#   include <unistd.h>
//#   include <sys/sysconf.h>
#   include <sys/ioctl.h>
#   include <sys/socket.h>
#   include <netinet/in.h>
#   include <net/if.h>
#   include <stdio.h>
#endif

#if defined(__GNUC__)    // GCC
#include <cpuid.h>
#endif

#if _MSC_VER >=1400    // VC2005��֧��intrin.h
#include <intrin.h>    // ����Intrinsics����
#endif

#ifdef WIN32
const GChar c_GLDPathDelim = 0x5c; // '\\'
const GChar c_GLDPathDelim_Linux = '/'; // '\\'
const GChar c_GLDDriveDelim = 0x3a; // ':'
#else
const GChar c_GLDPathDelim = 0x2f; // '/'
const GChar c_GLDPathDelim_Linux = '/'; // '\\'
const GChar c_GLDDriveDelim = 0x00; // ''
#endif

GChar pathDelim()
{
    return c_GLDPathDelim;
}

GChar driveDelim()
{
    return c_GLDDriveDelim;
}

GChar backSlashDelim()
{
    return 0x2f; // '/'
}

bool isPathDelimiter(const GString &s, int index)
{
    return (index > 0) && (index < s.length()) && ((s.at(index) == c_GLDPathDelim) || (s.at(index) == c_GLDPathDelim_Linux));
}

GString includeTrailingBackslash(const GString &s)
{
    return includeTrailingPathDelimiter(s);
}

GString includeTrailingPathDelimiter(const GString &s)
{
    GString result = s;
    if (!isPathDelimiter(s, s.length() - 1))
    {
        result += c_GLDPathDelim;
    }
    return result;
}

GString excludeTrailingBackslash(const GString &s)
{
    return excludeTrailingPathDelimiter(s);
}

GString excludeTrailingPathDelimiter(const GString &s)
{
    GString result = s;
    if (isPathDelimiter(s, s.length() - 1))
        result.chop(1);
    return result;
}

double fileDateToDateTime(int fileDate)
{
    int nYear(0);
    int nMonth(0);
    int nDay(0);
    int nHour(0);
    int nMin(0);
    int nSec(0);
    int nHi(0);
    int nLow(0);
    nHi = (fileDate & 0xffff0000) >> 16;
    nYear = (nHi >> 9) + 1980;
    nMonth = (nHi >> 5) & 15;
    nDay = (nHi & 31);
    nLow = fileDate & 0x0000ffff;
    nHour = nLow >> 11;
    nMin = (nLow >> 5) & 63;
    nSec = (nLow & 31) << 1;
    return dateTimeToDouble(GDateTime(GDate(nYear, nMonth, nDay), GTime(nHour, nMin, nSec)));
}

int DateTimeToFileDate(double value)
{
    int nResult = 0;
    int nYear(0);
    int nMonth(0);
    int nDay(0);
    int nHour(0);
    int nMin(0);
    int nSec(0);
    GDateTime dateTime = doubleToDateTime(value);
    GDate date = dateTime.date();
    GTime time = dateTime.time();
    if ((yearOf(value) < 1980) || (yearOf(value) > 2107))
        nResult = 0;
    else
    {
        nYear = date.year();
        nMonth = date.month();
        nDay = date.day();
        nHour = time.hour();
        nMin = time.minute();
        nSec = time.second();
        nResult |= ((nSec >> 1) | (nMin << 5) | (nHour << 11)) & 0x0000ffff;
        nResult |= ((nDay | (nMonth << 5) | (nYear - 1980) << 9)) << 16;
    }
    return nResult;
}

GString getUserNameDef()
{
#ifdef _MSC_VER
    char *pBuff;
    size_t nLen;

    if (0 == _dupenv_s(&pBuff, &nLen, "USERNAME"))
    {
        GString sName(pBuff);
        free(pBuff);

        return sName;
    }

    free(pBuff);
    return GString("");
#else
    return GString(getenv("USER"));
#endif
}

GString getHostName()
{
    char szAddr[255] = { '\0' };

#ifdef Q_OS_WIN
    unsigned long uSize = 255;
    GetComputerNameA(szAddr, &uSize);
#else
    gethostname(szAddr, sizeof(szAddr));
#endif

    return GString(szAddr);
}

unsigned getCoreCount()
{
    unsigned uCount = 1; // ����һ��

#ifdef Q_OS_WIN
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    uCount = si.dwNumberOfProcessors;
#else
    uCount = sysconf(_SC_NPROCESSORS_CONF);
#endif

    return uCount;
}

/****************************************************************************************************
  ���ߣ� ruanlz 2015-07-14
  �������ƣ�getCPUIdString
  ���أ� GString
  ���ܣ� ��ȡcpuID
  ��ע�� ʹ��__cpuid������ȡcpuid,���ڲ�֧��__cpuid������win32�µı�����ʹ�����������ʵ��__cpuid����
        ��windows��ʹ��wmic����������֤����windowsƽ̨��ubuntu 12.04.01��maxos 10.9��������֤����Ϊ
        ��������������У�Ӳ����Ϣ������֤,����׼ȷ�Բ��ܶ��ۡ�
  ע�⣺ cpu���кŲ�Ψһ����ͬ�ͺŵ�cpu��cpu���кſ�����ͬ
  ��������Intel 486���Ϻ�AMD am486���ϵ�X86�ܹ��Ĵ���������֧�ֳ�X86����ܹ��Ĵ�����
****************************************************************************************************/

#if defined(_WIN64)
// 64λ�²�֧���������. Ӧʹ��__cpuid��__cpuidex��Intrinsics������
#elif defined(WIN32)
#if _MSC_VER < 1600    // VS2010. ��˵VC2008 SP1֮���֧��__cpuidex
void __cpuidex(INT32 CPUInfo[4], INT32 InfoType, INT32 ECXValue)
{
    if (NULL==CPUInfo)    return;
    _asm{
        // load. ��ȡ�������Ĵ���
        mov edi, CPUInfo;    // ׼����ediѰַCPUInfo
        mov eax, InfoType;
        mov ecx, ECXValue;
        // CPUID
        cpuid;
        // save. ���Ĵ������浽CPUInfo
        mov    [edi], eax;
        mov    [edi+4], ebx;
        mov    [edi+8], ecx;
        mov    [edi+12], edx;
    }
}
#endif    // #if _MSC_VER < 1600    // VS2010. ��˵VC2008 SP1֮���֧��__cpuidex

#if _MSC_VER < 1400    // VC2005��֧��__cpuid
void __cpuid(INT32 CPUInfo[4], INT32 InfoType)
{
    __cpuidex(CPUInfo, InfoType, 0);
}
#endif    // #if _MSC_VER < 1400    // VC2005��֧��__cpuid

#endif    // #if defined(_WIN64)

GString getCPUIdString()
{
#ifdef Q_OS_WIN
    GString sCpuid;//�洢cpuid���ַ���
    INT32 nCpuid[4];//�洢�Ĵ�������

    //��ȡcpuid
    __cpuid(nCpuid,0x01);

    //�ѽ����ʽ�������ַ���
    char pbufer[17];
    sprintf_s(pbufer,17,"%.8X%.8X",nCpuid[3],nCpuid[0]);//��ʽ���ַ���
    sCpuid = GString(GLatin1String(pbufer));//��charת����GString
    return sCpuid;
#else
    /*��ubuntu 12.04.1�ϲ��Կ��Ի�ȡ��cpuid�ţ�����Ϊ������������е�Linux��Ӳ��������ģ����ܱ�֤������ȷ*/
//#define cpuid(in,a,b,c,d) asm("cpuid":"=a"(a),"=b"(b),"=c"(c),"=d"(d):"a"(in));
    //����AT&T���Ļ����룬�������cpuid���
    int eax,ebx,ecx,edx;//�洢�Ĵ���������
    GString sCpuid;//�洢cpuid���ַ���
    __cpuid(1,eax,ebx,ecx,edx);
    char pbufer[17];
    sprintf(pbufer, "%.8X%.8X",edx,eax);//��ʽ���ַ���
    sCpuid = GString(GLatin1String(pbufer));//��charת����GString
    return sCpuid;
#endif
}

/****************************************************************************************************
  ���ߣ� ruanlz 2015-07-14
  �������ƣ�getDiskSerialNoString
  ���أ� GString
  ���ܣ� ��ȡϵͳ�ĵ�һ��Ӳ�̵����кţ�����һ����c�̻���ϵͳ�����ڵ�Ӳ��
  ע�⣺ ��ȡӲ��idʱ����������й���ԱȨ�޲��ܻ�ȡ�����򷵻ؿ�
  ����ϵͳ��֧��windows95�����ϰ汾��windows����ϵͳ���ݲ�֧����������ϵͳ��
****************************************************************************************************/
#ifdef Q_OS_WIN
//��WORD��������ֽ���Ϊlittle-endian�����˳��ַ�����β�Ŀո�
void ToLittleEndian(PUSHORT pWords, int nFirstIndex, int nLastIndex, LPTSTR pBuf)
{
    int index;
    LPTSTR pDest = pBuf;
    for(index = nFirstIndex; index <= nLastIndex; ++index)
    {
        pDest[0] = pWords[index] >> 8;
        pDest[1] = pWords[index] & 0xFF;
        pDest += 2;
    }
    *pDest = 0;

    //trim space at the endof string; 0x20: _T(' ')
    --pDest;
    while(*pDest == 0x20)
    {
        *pDest = 0;
        --pDest;
    }
}

//�˳��ַ�����ʼλ�õĿո�
void TrimStart(LPTSTR pBuf)
{
    if(*pBuf != 0x20)
    {
        return;
    }

    LPTSTR pDest = pBuf;
    LPTSTR pSrc = pBuf + 1;
    while(*pSrc == 0x20)
        ++pSrc;

    while(*pSrc)
    {
        *pDest = *pSrc;
        ++pDest;
        ++pSrc;
    }
    *pDest = 0;
}

GString getDiskSerialNoString()
{
    TCHAR  szSerialNo[24];
    BYTE IdentifyResult[sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1];
    DWORD dwBytesReturned;
    GETVERSIONINPARAMS get_version;
    SENDCMDINPARAMS send_cmd = { 0 };

    HANDLE hFile = CreateFile(L"\\\\.\\PHYSICALDRIVE0", GENERIC_READ | GENERIC_WRITE,
                              FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    if(hFile == INVALID_HANDLE_VALUE)
    {
        return GString("");
    }

    //get version
    DeviceIoControl(hFile, SMART_GET_VERSION, NULL, 0,
                    &get_version, sizeof(get_version), &dwBytesReturned, NULL);
    //identify device

    //send_cmd.irDriveRegs.bCommandReg = (get_version.bIDEDeviceMap & 0x10)? ATAPI_ID_CMD : ID_CMD;
    //˵���� ����ATAPI_ID_CMD����ʽȥ��ȡӲ����Ϣʱ���ȡ������ID_CMD����Ի�ȡ����ʱ��õ����ϻ�û�в������
    //      ��ʱ���������û�и��õĽ��������������ʱ�ȸ�Ϊ����ID_CMD�������ʽȥ��ȡӲ����Ϣ��
    send_cmd.irDriveRegs.bCommandReg = (get_version.bIDEDeviceMap & 0x10)? ID_CMD : ID_CMD;
    DeviceIoControl(hFile, SMART_RCV_DRIVE_DATA, &send_cmd, sizeof(SENDCMDINPARAMS) - 1,
                    IdentifyResult, sizeof(IdentifyResult), &dwBytesReturned, NULL);
    CloseHandle(hFile);

    //��ȡ���
    PUSHORT pWords = (USHORT*)(((SENDCMDOUTPARAMS*)IdentifyResult)->bBuffer);

    ToLittleEndian(pWords, 10, 19, szSerialNo);
    TrimStart(szSerialNo);
    QString sDiskSerialNo;
    sDiskSerialNo = QString::fromWCharArray(szSerialNo);
    return sDiskSerialNo;
}
#else
//��windows����ϵͳͳһ���ؿ��ַ���
GString getDiskSerialNoString()
{
    return GString("");
}
#endif

/****************************************************************************************************
  ���ߣ� ruanlz 2015-07-14
  �������ƣ�getComputerGUID
  ���أ� GString
  ���ܣ� ��ȡ����Ψһ��ʾ�����ؽ����32λ���ַ���
  ע�⣺ ��Ϊ������getDiskSerialNoString������������û�й���ԱȨ���·��صĴ������кſ���
        �ǿյģ����й���ԱȨ�޺�û�й���ԱȨ�޵�����£��˺����ķ���ֵ���ܲ�һ����
****************************************************************************************************/
#ifdef Q_OS_WIN
GString getComputerGUID()
{
    GString sCpuid,sDiskSerialNo;
    GString sComputerGUID;

    //��ȡcpuid�ʹ������к�
    sCpuid = getCPUIdString();
    sDiskSerialNo = getDiskSerialNoString();
    sComputerGUID = sCpuid + sDiskSerialNo;
    return sComputerGUID;
}
#endif


#ifdef Q_OS_WIN
unsigned getNetworkCardCount()
{
    LANA_ENUM leAdapt;
    NCB ncb;
    memset(&ncb, 0, sizeof(ncb));

    ncb.ncb_command = NCBENUM;
    ncb.ncb_buffer = (unsigned char*)&leAdapt;
    ncb.ncb_length = sizeof(leAdapt);

    if (Netbios(&ncb) == 0)
    {
        return leAdapt.length;
    }

    return 0;
}

#endif

GString getMacString()
{
#ifdef Q_OS_WIN

    //int nCount = getNetworkCardCount();
    NCB ncb;
    ADAPTER_STATUS adapt;

    GLDVector<GString> vecRes;
    memset(&ncb, 0, sizeof(ncb));

    UCHAR uRetCode;
    LANA_ENUM   lenum;
    ncb.ncb_command  =  NCBENUM;
    ncb.ncb_buffer  =  (UCHAR  * ) & lenum;
    ncb.ncb_length  =   sizeof (lenum);
    uRetCode  =  Netbios(  & ncb );

    for (int i = 0; i < lenum.length; ++i)
    {
        memset(  & ncb,  0 ,  sizeof (ncb) );
        ncb.ncb_command  =  NCBRESET;
        ncb.ncb_lana_num  =  lenum.lana[i];
        uRetCode  =  Netbios(&ncb);
        if (NRC_GOODRET != uRetCode)
        {
            continue;
        }
        memset(&ncb, 0 , sizeof(ncb));
        ncb.ncb_command = NCBASTAT;
        ncb.ncb_lana_num = lenum.lana[i];
        strcpy_s((char*)ncb.ncb_callname, sizeof(ncb.ncb_callname), "*");
        ncb.ncb_buffer = (unsigned char*)&adapt;
        ncb.ncb_length = sizeof(adapt);

        char szBuff[128] = { '\0' };

        Netbios(&ncb);
#ifdef _MSC_VER
        sprintf_s(
#else
        sprintf(
#endif
                szBuff, "%02X-%02X-%02X-%02X-%02X-%02X\r\n",
                adapt.adapter_address[0],
                adapt.adapter_address[1],
                adapt.adapter_address[2],
                adapt.adapter_address[3],
                adapt.adapter_address[4],
                adapt.adapter_address[5]);

        vecRes.push_back(GString(szBuff));
    }

    if (vecRes.size() > 0)
    {
        return vecRes[0];
    }
#else
    struct ifreq ifreq;
    int sock;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) > 0)
    {
         strcpy(ifreq.ifr_name, "");
         if (ioctl(sock, SIOCGIFADDR, &ifreq) > 0)
         {
             char szBuff[128] = { '\0' };
             sprintf(szBuff, "%02X-%02X-%02X-%02X-%02X-%02X\r\n",
                     (unsigned char)ifreq.ifr_ifru.ifru_addr.sa_data[0],
                     (unsigned char)ifreq.ifr_ifru.ifru_addr.sa_data[1],
                     (unsigned char)ifreq.ifr_ifru.ifru_addr.sa_data[2],
                     (unsigned char)ifreq.ifr_ifru.ifru_addr.sa_data[3],
                     (unsigned char)ifreq.ifr_ifru.ifru_addr.sa_data[4],
                     (unsigned char)ifreq.ifr_ifru.ifru_addr.sa_data[5]);

             return GString(szBuff);
         }
    }
#endif

    return GString("");
}

/****************************************************************************************************
  ���ߣ� yanyq-a 2013-07-30
  ������ const GString&, const GString&
  ���أ� GString
  ���ܣ� ��ȡע�����Ӧ��ֵ(��ӦԭGrandFileUtils::GetShellFolderPath)
****************************************************************************************************/
GString valueFromRegistry(const GString &regPath, const GString &regKey)
{
    GSettings oSetting(regPath, GSettings::NativeFormat);
    GString result = oSetting.value(regKey, "").toString();
    if ((result.length() > 0) && !((result.right(1) == "\\") || result.right(1) == "/"))
    {
        result += "/";
    }
    return GDir::fromNativeSeparators(result);
}

GString environmentVariable(const GString &envVAR)
{
    QByteArray vardir = qgetenv(envVAR.toStdString().data());

    if (vardir.size() > 0 )
    {
        return vardir;
    }

    return envVAR;
}

bool setEnvironmentVariable(const GString &name, const GString &value)
{
    // todo
    return false;
    G_UNUSED(name)
    G_UNUSED(value)
}

/****************************************************************************************************
  ���ߣ� yanyq-a 2013-07-30
  ������ ��
  ���أ� GString
  ���ܣ� ��ȡ��ǰ�û����ĵ�Ŀ¼
****************************************************************************************************/
GString getUserDocumentsPath()
{
    return QDir::fromNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).append('/'));
}

/****************************************************************************************************
  ���ߣ� yanyq-a 2013-07-30
  ������ ��
  ���أ� GString
  ���ܣ� ��ȡ��ǰ�û���Ӧ�ó�������Ŀ¼
****************************************************************************************************/
GString getUserAppDataPath()
{
#ifdef WIN32
    return getSpecialFolderPath(CSIDL_APPDATA);
#else
    return GString();
#endif
}

/****************************************************************************************************
  ���ߣ� yanyq-a 2013-08-09
  ������ ��
  ���أ� gint64
  ���ܣ� ���������ڴ�
****************************************************************************************************/
gint64 getAvailPhysMem()
{
#ifdef Q_OS_WIN
    MEMORYSTATUSEX oMemory;
    oMemory.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&oMemory);
    return oMemory.ullAvailPhys;
#else
    FILE *pfd;
    char *pend;
    gint64 nFree = 0;
    char szBuff[256] = { '\0' };

    pfd = fopen("/proc/meminfo", "r");

    while (true)
    {
        memset(szBuff, 0, 256);
        pend = fgets(szBuff, 256, pfd);

        if (NULL == pend) break;
        if (strncmp(szBuff, "MemFree", 7) == 0)
        {
            nFree = atoll(szBuff);
            break;
        }
    }

    return nFree;
#endif
}

/**************************************************************************
  ���ߣ� yanyq-a 2013-08-09
  ������ ��
  ���أ� unsigned long
  ���ܣ� �����ڴ�ʹ����
**************************************************************************/
unsigned long memoryUsage()
{
#ifdef Q_OS_WIN
    MEMORYSTATUSEX oMemory;
    oMemory.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&oMemory);
    return oMemory.dwMemoryLoad;
#else
    FILE *pfd;
    char *pend;
    gint64 nTotal = 0;
    gint64 nFree = 0;
    char szBuff[256] = { '\0' };

    pfd = fopen("/proc/meminfo", "r");

    while (true)
    {
        memset(szBuff, 0, 256);
        pend = fgets(szBuff, 256, pfd);

        if (NULL == pend) break;
        if (strncmp(szBuff, "MemTotal", 8) == 0)
        {
            nTotal = atoll(szBuff);
        }
        if (strncmp(szBuff, "MemFree", 7) == 0)
        {
            nFree = atoll(szBuff);
        }
    }

    if (nTotal <= 0)
    {
        return 0;
    }
    else
    {
        return ((nTotal - nFree) * 100) / nTotal;
    }
#endif
}

GString getSpecialFolderPath(int CSIDL)
{
#ifdef WIN32
    wchar_t path[MAX_PATH];
    if (SHGetSpecialFolderPath(0, path, CSIDL, FALSE))
        return QDir::fromNativeSeparators(QString::fromWCharArray(path).append('/'));
    else
        return GString();
#else
    return GString();
#endif
}
