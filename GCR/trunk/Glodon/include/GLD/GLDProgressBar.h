/*!
*@file
*@brief ������
*@author wangdz
*@date 2014��12��13��
*@remarks
*
*Copyright (c) 1998-25 Glodon Corporation
*/

#ifndef GLDPROGRESSBAR_H
#define GLDPROGRESSBAR_H

#include <QEvent>
#include <QWaitCondition>
#include <QProgressDialog>
#include "GLDWidget_Global.h"

class GLDWIDGETSHARED_EXPORT GLDProgressBar: public QObject
{
    Q_OBJECT

public:
    GLDProgressBar(QWidget *parent = NULL);
    ~GLDProgressBar();

public:
    /**
    * @brief ���õ�ǰ��������ֵ
    */
    void setValue(const int);
    /**
    * @brief ���ý������ı߽緶Χ
    * @param[in] minimum ��������С�ı߽�ֵ
    * @param[in] maximum ���������ı߽�ֵ
    * @note ������minimum = maximum = 0ʱ������ֽ�����busy��״ָ̬ʾ
    * @see QProgressDialog::setRange,setMinimum,setMaximum
    *
    */
    void setRange(int minimum, int maximum);
    /**
    * @brief �ڷ����̵߳���ˢ�·�������Ҫ֪ͨ���̸߳���m_progressDlg��value
    * @param[in] pos ��������ǰ�߽�ֵ
    */
    void updateProgress(int pos);
    /**
    * @brief ��ʾ������
    */
    void show();

    virtual bool event(QEvent *event);
    /**
    * @brief ���ؽ�����
    */
    void hide();
    /**
    * @brief �õ���ǰ������λ��
    * @param[in] pos ��������ǰ�߽�ֵ
    */
    int getProgressPos();
    /**
    * @brief ���ý������Ĵ�С
    * @param[in] width  ���
    * @param[in] height  �߶�
    */
    void setSize(int width, int height);
    void setPos(int x, int y);
    /**
    * @brief ���ý������Ϸ��ı���Ϣ
    * ע���˷���һ��Ҫ��resize����֮ǰʹ��  ����resize������ʧЧ
    */
    void setText(const QString &str);

private:
    bool isCreateThread();

private:
    int m_cachePos;
    Qt::HANDLE m_barThreadId;
    QProgressDialog *m_progressDlg;
    QWaitCondition m_waitobj;
};
#endif
