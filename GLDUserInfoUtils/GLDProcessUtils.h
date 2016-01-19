#ifndef GLDPROCESSFUNC_H
#define GLDPROCESSFUNC_H

#include <qt_windows.h>
#include <WinNT.h>

#include <QList>
#include <QString>
#include <QStringList>

namespace GlodonProcessInfo
{
    class GLDProcessFunc
    {
    public:
        static ULONGLONG getCpuUsage(DWORD processID);
        static ULONGLONG getCpuUsage(const QString &processName);

        //��ǰָ�����̵�ռ�õ��ڴ�KBΪ��Ԫ
        static SIZE_T getMemoryInfo(DWORD processID);
        static SIZE_T getMemoryInfo(const QString &processName);

        static SIZE_T getMemoryInfo(HANDLE processID);

        static DWORD getIDByName(const QString &processName);
        static QString getNameByID(DWORD processID);

    private:
        static HANDLE getHandleByName(const QString &processName);
        static HANDLE getHandleByID(DWORD processId);

    public:
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
