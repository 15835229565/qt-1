/********************************************************************
���ģ���ʹ�õ�Qt GUI,��������õ�Ԫ����ʹ��Qt+=GUI��������벻ͨ����by huy-a.
********************************************************************/
#ifndef GLDUIUTILS_H
#define GLDUIUTILS_H

#include "GLDStrUtils.h"
#include <QMessageBox>
#include "GLDStrings.h"
extern const char *rsConfirmCaption;

GLDCOMMONSHARED_EXPORT void showPrompt(const GString &msg, bool bShowClose = true, QWidget *parent = NULL);
GLDCOMMONSHARED_EXPORT void showError(const GString &msg, QWidget *parent = NULL);
GLDCOMMONSHARED_EXPORT void showWarnning(const GString &msg, QWidget *parent = NULL);
GLDCOMMONSHARED_EXPORT int showConfirm(const GString &msg, QWidget *parent = NULL);

GLDCOMMONSHARED_EXPORT int confirmDlg(const GString msg, bool cancelButton = false, QWidget *parent = NULL);

//bool createDesktopPromtInfo(const GString &linkPath, const GString &iconPath, int nInfoNumber);

//ȱʡ������MessageBox����
class GLDCOMMONSHARED_EXPORT GLDDefaultConfirmSettingFuc
{
public:
    inline void operator()(QMessageBox &box)
    {
        box.setDefaultButton(QMessageBox::Ok);
        box.setStyleSheet("QPushButton:default {color: blue}");
    }
};

template<typename T>
int confirmDlg(const GString msg, bool cancelButton, QWidget *parent, T Func)
{
    QMessageBox::StandardButtons standardBtns = QMessageBox::Ok | QMessageBox::No;

    if (cancelButton)
    {
        standardBtns |= QMessageBox::Cancel;
    }

    QMessageBox tempBox(QMessageBox::Question, getGLDi18nStr(rsConfirmCaption), msg, standardBtns, parent);
    Func(tempBox);
    return tempBox.exec();
}

inline int confirmDlgEx(const GString msg, bool cancelButton = false, QWidget *parent = NULL)
{
    return confirmDlg(msg, cancelButton, parent, GLDDefaultConfirmSettingFuc());
}

#endif // GLDUIUTILS_H
