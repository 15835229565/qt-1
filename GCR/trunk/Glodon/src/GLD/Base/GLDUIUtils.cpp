#include "GLDUIUtils.h"

#include <QIcon>
#include <QPixmap>
#include <QPainter>
#include <QMessageBox>
#include "GLDWidget_Global.h"
#include "GLDFileUtils.h"
#include "GLDStrings.h"

const char *SPrompt				= QT_TRANSLATE_NOOP("GLD", "Prompt");// "��ʾ");
const char *rsConfirmCaption	= QT_TRANSLATE_NOOP("GLD", "Confirm");// "ȷ��");
const char *rsErrorCaption		= QT_TRANSLATE_NOOP("GLD", "Error");// "����");
const char *rsWarningCaption	= QT_TRANSLATE_NOOP("GLD", "Warning");// "����");
const char *rsMsgDlgOK			= QT_TRANSLATE_NOOP("GLD", "OK");// "ȷ��");
const char *rsMsgDlgCancel		= QT_TRANSLATE_NOOP("GLD", "Cancel");// "ȡ��");


void showPrompt(const GString &msg, bool bShowClose, QWidget *parent)
{
    if (bShowClose)
        QMessageBox::information(parent, getGLDi18nStr(SPrompt), msg, QMessageBox::Ok);
    else
    {
        QMessageBox messageBox;
        messageBox.setParent(parent);
        messageBox.setWindowTitle(getGLDi18nStr(SPrompt));
        messageBox.setText(msg);
        messageBox.setStandardButtons(QMessageBox::Ok);
        Qt::WindowFlags wFlags = Qt::CustomizeWindowHint | Qt::WindowTitleHint;
        messageBox.setWindowFlags(wFlags);
        messageBox.setIcon(QMessageBox::Information);
        messageBox.exec();
    }
}

////////////////////////////////////////////////////////////////////////////////
//��ƣ�Linc 2009.10.26
//���ܣ�ȷ�϶Ի���
//������AMsg -- ������Ϣ��
//      cancelButton -- �ͷŰ���Cancel��ť
//���أ�ѡ��İ�ť
//ע�⣺�ᾡ��ѡ�� Vista ���� TaskDialogs
////////////////////////////////////////////////////////////////////////////////
int confirmDlg(const GString msg, bool cancelButton, QWidget *parent)
{
    if (cancelButton)
    {
        return QMessageBox::question(parent, getGLDi18nStr(rsConfirmCaption), msg, QMessageBox::Yes, QMessageBox::No,
                                     QMessageBox::Cancel);
    }
    else
    {
        return QMessageBox::question(parent, getGLDi18nStr(rsConfirmCaption), msg, QMessageBox::Yes, QMessageBox::No);
    }
}

void showError(const GString &msg, QWidget *parent)
{
    QMessageBox::critical(parent, getGLDi18nStr(rsErrorCaption), msg, QMessageBox::Ok);
}

void showWarnning(const GString &msg, QWidget *parent)
{
    QMessageBox::warning(parent, getGLDi18nStr(rsWarningCaption), msg, QMessageBox::Ok);
}

int showConfirm(const GString &msg, QWidget *parent)
{
    return QMessageBox::question(parent, getGLDi18nStr(rsConfirmCaption), msg, QMessageBox::Yes, QMessageBox::No);
}
