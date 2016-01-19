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

        // ��ǰָ�����̵�ռ�õĹ�����(�ڴ�),KBΪ��Ԫ
        static SIZE_T getCurrentWorkingSet(DWORD processID);
        static SIZE_T getCurrentWorkingSet(const QString &processName);

        // ��ǰָ�����̵�ռ�õķ�ֵ������(�ڴ�),KBΪ��Ԫ
        static SIZE_T getPeekWorkingSet(DWORD processID);
        static SIZE_T getPeekWorkingSet(const QString &processName);

        // ��ǰָ�����̵�ռ�õ�ר�ù�����(�ڴ�),KBΪ��Ԫ
        static ulong getPrivateWorkingSet(DWORD processID);
        static SIZE_T getPrivateWorkingSet(const QString &processName);

        // ��ǰָ�����̵�ռ�õĹ�������(�ڴ�),KBΪ��Ԫ
        static ulong getSharedWorkingSet(DWORD processID);
        static SIZE_T getSharedWorkingSet(const QString &processName);


        static QString getNameByID(DWORD processID);
    private:
        static DWORD getIDByName(const QString &processName);

        static SIZE_T getCurrentWorkingSet(HANDLE handle);
        static SIZE_T getPeekWorkingSet(HANDLE handle);

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
