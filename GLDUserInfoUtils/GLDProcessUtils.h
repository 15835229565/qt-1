#ifndef GLDPROCESSFUNC_H
#define GLDPROCESSFUNC_H

#include <qt_windows.h>
#include <WinNT.h>

#include <QList>
#include <QString>
#include <QStringList>

namespace GLDProcessInfo
{
    class GLDProcessFunc
    {
    public:
        static ULONGLONG getCpuUsage(DWORD processID);
        static ULONGLONG getCpuUsage(const QString &processName);

        //��ǰָ�����̵�ռ�õ��ڴ�KBΪ��Ԫ
        static ULONGLONG getMemoryInfo(DWORD processID);
        static ULONGLONG getMemoryInfo(const QString &processName);

        static DWORD getIDByName(const QString &processName);
        static QString getNameByID(DWORD processID);

        static bool isProcessRunning(TCHAR *szEXEName);
        static bool isProcessRunning(const QStringList &exeNameList);
        static bool isProcessRunning(const QString &processName);
        static bool killProcess(const QString &lpProcessName);
        static QStringList getPathByName(const QString &lpProcessName);
        static bool killProcessByAbPath(const QString &lpProcessPath);
        static QList<DWORD> getProcessIDList(const QStringList &processNameList);

        //����ָ������,��Ҫ�Ƿ�ֹ·�����пո��������
        static void startProcess(const QString &strExe, const QStringList &params);
        static void startProcess(const QString &strExe);
        static HANDLE getCurrentID();
    };
}


#endif // GLDPROCESSFUNC_H
