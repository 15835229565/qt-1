#ifndef GLDPROCESSFUNC_H
#define GLDPROCESSFUNC_H

#include <qt_windows.h>

#include <WinNT.h>

#include <QList>
#include <QString>
#include <QStringList>

class CpuUsage
{
public:
    CpuUsage(DWORD dwProcessID);
    ULONGLONG getUsageEx();
    ULONGLONG getSystemNonIdleTimes();
    ULONGLONG getProcessNonIdleTimes();

private:
    ULONGLONG subtractTimes(const FILETIME& ftA, const FILETIME& ftB);
    ULONGLONG addTimes(const FILETIME& ftA, const FILETIME& ftB);
    bool enoughTimePassed();
    inline bool isFirstRun() const { return (m_dwLastRun == 0); }

    //system total times
    FILETIME m_ftPrevSysKernel;
    FILETIME m_ftPrevSysUser;

    //process times
    FILETIME m_ftPrevProcKernel;
    FILETIME m_ftPrevProcUser;

    ULONGLONG m_ullPrevSysNonIdleTime;//��������ͺ���ı�����¼�ϴλ�ȡ�ķ�idle��ϵͳcpuʱ��ͽ���cpuʱ��.
    ULONGLONG m_ullPrevProcNonIdleTime;//�����ֻ��һ������, �ڹ��캯�������ʼ������..

    ULONGLONG m_nCpuUsage;
    ULONGLONG m_dwLastRun;
    DWORD m_dwProcessID;
    HANDLE m_hProcess;
    volatile LONG m_lRunCount;
};

class GLDProcessFunc
{
public:
    static ULONGLONG getCpuUsage(const QString &processName);
    static ULONGLONG getCpuUsage(DWORD processID);
    //��ǰָ�����̵�ռ�õ��ڴ�KBΪ��Ԫ
    static ULONGLONG getMemoryInfo(const QString &processName);
    static ULONGLONG getMemoryInfo(DWORD processID);
    static DWORD getIDByName(const QString &processName);
    static QString getNameByID(DWORD processID);
    static bool isProcessRunning(TCHAR *szEXEName);
    static bool isProcessRunning(const QStringList &exeNameList);
    static bool isProcessRunning(const QString &processName);
    static bool killProcess(const QString &lpProcessName);
    static QStringList getPathByName(const QString &lpProcessName);
    static bool killProcessByAbPath(const QString &lpProcessPath);
    static QList<DWORD> getProcessIDList(const QStringList &processNameList);
    //����ָ��������Ҫ�Ƿ�ֹ·�����пո��������
    static void startProcess(const QString &strExe, const QStringList &params);
    static void startProcess(const QString &strExe);
    static HANDLE getCurrentID();

};

#endif // GWSPROCESSFUNC_H
