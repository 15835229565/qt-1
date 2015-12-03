#ifndef GLDEVENT_H
#define GLDEVENT_H

#include <QObject>
#include <QEvent>
#include "GLDSystem.h"
#include "GLDGlobal.h"

const unsigned short c_GM_BASE = 2000;

enum GLDEventType
{
    GM_BASE = c_GM_BASE,
    GM_PREV = c_GM_BASE + 0, // ��һ��
    GM_NEXT = c_GM_BASE + 1, // ��һ��
    GM_FIRST = c_GM_BASE + 2, // ����
    GM_Last = c_GM_BASE + 3, // ĩ��
    GM_MOVEUP = c_GM_BASE + 4, // ����һ��
    GM_MOVEDOWN = c_GM_BASE + 5, // ����һ��
    GM_MOVELEFT = c_GM_BASE + 6, // ����һ��
    GM_MOVERIGHT = c_GM_BASE + 7, // ����һ��
    GM_INSERTCOL = c_GM_BASE + 8, // ����һ��
    GM_DELETECOL = c_GM_BASE + 9, // ɾ��һ��
    GM_INSERTROW = c_GM_BASE + 10, // ����һ��
    GM_DELETEROW = c_GM_BASE + 11, // ɾ��һ��
    GM_DUPLICATEROW = c_GM_BASE + 12, // ����һ��
    GM_ZAP = c_GM_BASE + 13, // ɾ��������
    GM_EXPAND = c_GM_BASE + 14, // չ��
    GM_COLLAPSE = c_GM_BASE + 15, // �۵�
    GM_EXPANDALL = c_GM_BASE + 16, // չ��ȫ��
    GM_COLLAPSEALL = c_GM_BASE + 17, // �۵�ȫ��
    GM_LEVELUP = c_GM_BASE + 18, // ��������
    GM_LEVELDOWN = c_GM_BASE + 19, // ��������
    GM_SETCOLROW = c_GM_BASE + 20, // ��������
    GM_SETSEL = c_GM_BASE + 21, // ȫѡ
    GM_CUT = c_GM_BASE + 22,    // ����
    GM_COPY = c_GM_BASE + 23,   // ����
    GM_PASTE = c_GM_BASE + 24, // ճ��
    GM_CLEAR = c_GM_BASE + 25, // ɾ��
    GM_PASTEASCHILD = c_GM_BASE + 26, // ��Ϊ��ճ��

    GM_QUERYPREV = c_GM_BASE + 50, // ������һ��
    GM_QUERYNEXT = c_GM_BASE + 51, // ������һ��
    GM_QUERYFIRST = c_GM_BASE + 52, // ��������
    GM_QUERYLAST = c_GM_BASE + 53, // ����ĩ��
    GM_QUERYMOVEUP = c_GM_BASE + 54, // ��������һ��
    GM_QUERYMOVEDOWN = c_GM_BASE + 55, // ��������һ��
    GM_QUERYMOVELEFT = c_GM_BASE + 56, // ��������һ��
    GM_QUERYMOVERIGHT = c_GM_BASE + 57, // ��������һ��
    GM_QUERYINSERTCOL = c_GM_BASE + 58, // �������һ��
    GM_QUERYDELETECOL = c_GM_BASE + 59, // ����ɾ��һ��
    GM_QUERYINSERTROW = c_GM_BASE + 60, // �������һ��
    GM_QUERYDELETEROW = c_GM_BASE + 61, // ����ɾ��һ��
    GM_QUERYDUPLICATEROW = c_GM_BASE + 62, // ������һ��
    GM_QUERYZAP = c_GM_BASE + 63, // ����ɾ��������
    GM_QUERYEXPAND = c_GM_BASE + 64, // ����չ��
    GM_QUERYCOLLAPSE = c_GM_BASE + 65, // �����۵�
    GM_QUERYEXPANDALL = c_GM_BASE + 66, // ����չ��ȫ��
    GM_QUERYCOLLAPSEALL = c_GM_BASE + 67, // �����۵�ȫ��
    GM_QUERYLEVELUP = c_GM_BASE + 68, // ����������
    GM_QUERYLEVELDOWN = c_GM_BASE + 69, // ����������
    GM_QUERYLESETCOLROW = c_GM_BASE + 70, // ������������
    GM_QUERYSETSEL = c_GM_BASE + 71, // ����ȫѡ
    GM_QUERYCUT = c_GM_BASE + 72, // �������
    GM_QUERYCOPY = c_GM_BASE + 73, // ������
    GM_QUERYPASTE = c_GM_BASE + 74, // ����ճ��
    GM_QUERYCLEAR = c_GM_BASE + 75, // ����ɾ��
    GM_QUERYPASTEASCHILD = c_GM_BASE + 76, // ������Ϊ��ճ��
    GM_DELAYSETRECORD = c_GM_BASE + 77, // �ӳ����õ�ǰrecord

    GM_SetScrollBarStep = c_GM_BASE + 101,
    GM_DocViewCalculatePage = c_GM_BASE + 102,

    GM_GSPBASE = c_GM_BASE + 1000,
    GM_GTPBASE = c_GM_BASE + 1500,
    GM_APPBASE = c_GM_BASE + 2000
};

typedef PtrInt GLDWParam;
typedef PtrInt GLDLParam;
typedef PtrInt GLDEventResult;

class GLDCOMMONSHARED_EXPORT GLDEvent : public QEvent
{
public:
    GLDEvent(GLDEventType type, GLDWParam wParam = 0, GLDLParam lParam = 0);

    GLDWParam wParam() const;
    GLDWParam lParam() const;

    GLDEventType type() const;
    GLDEventResult result() const;
    void setResult(GLDEventResult value);
private:
    GLDWParam m_wParam;
    GLDLParam m_lParam;
    GLDEventResult m_result;
};

#endif // GLDEVENT_H
