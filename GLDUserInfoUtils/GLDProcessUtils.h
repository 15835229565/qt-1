#ifndef GLDPROCESSFUNC_H
#define GLDPROCESSFUNC_H

#include <qt_windows.h>
#include <WinNT.h>

#include <QList>
#include <QString>
#include <QStringList>

namespace GlodonProcessInfo
{
    ULONGLONG getCpuUsage(DWORD processID);
    ULONGLONG getCpuUsage(const QString &processName);

    // ��ǰָ�����̵�ռ�õĹ�����(�ڴ�),KBΪ��Ԫ
    SIZE_T getCurrentWorkingSet(DWORD processID);
    SIZE_T getCurrentWorkingSet(const QString &processName);

    // ��ǰָ�����̵�ռ�õķ�ֵ������(�ڴ�),KBΪ��Ԫ
    SIZE_T getPeekWorkingSet(DWORD processID);
    SIZE_T getPeekWorkingSet(const QString &processName);

    // ��ǰָ�����̵�ռ�õ�ר�ù�����(�ڴ�),KBΪ��Ԫ
    ulong getPrivateWorkingSet(DWORD processID);
    SIZE_T getPrivateWorkingSet(const QString &processName);

    // ��ǰָ�����̵�ռ�õĹ�������(�ڴ�),KBΪ��Ԫ
    ulong getSharedWorkingSet(DWORD processID);
    SIZE_T getSharedWorkingSet(const QString &processName);

    QString getNameByID(DWORD processID);
    DWORD getIDByName(const QString &processName);

    SIZE_T getCurrentWorkingSet(HANDLE handle);
    SIZE_T getPeekWorkingSet(HANDLE handle);

    HANDLE getHandleByName(const QString &processName);
    HANDLE getHandleByID(DWORD processId);

    HANDLE getCurrentID();
}


#endif // GLDPROCESSFUNC_H
