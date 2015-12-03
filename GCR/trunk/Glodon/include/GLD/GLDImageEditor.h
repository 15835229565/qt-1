/*!
 *@file gimageeditor.h
 *@brief {ͼƬѡ��ؼ�}
 *����QImage�������ݵ�Ĭ�ϱ༭��ʽ
 *@author Gaosy
 *@date 2012.9.7
 *@remarks {}
 *Copyright (c) 1998-2012 Glodon Corporation
 */

#ifndef GLDIMAGEEDITOR_H
#define GLDIMAGEEDITOR_H

#include <QPushButton>
#include <QLabel>
#include "GLDWidget_Global.h"
/*!   
 *@class: GImageEditor
 *@brief {ͼƬѡ��ؼ�����Ϊ��ʾͼƬ�ĸ��ӵ�Ĭ�ϱ༭��ʽ}
 *@author Gaosy 
 *@date 2012.9.10
 */
class GLDWIDGETSHARED_EXPORT GImageEditor : public QWidget
{
    Q_OBJECT
public:
    /*!
     *GImageEditor���췽��
     *@param[in]  parent  ��widget
     *@return ��
     */
    explicit GImageEditor(QWidget *parent = 0);

    /*!
     *GImageEditor��������
     *@return ��
     */
    virtual ~GImageEditor();

    /*!
     *GFilterView�Ļ��Ʒ���
     *@param[in]  e  
     *@return ��
     */
    void paintEvent(QPaintEvent *);

    /*!
     *ΪGImageEditor���õ�ǰͼƬ
     *@param[in]  img  ���õ�ǰ��ͼƬ
     *@return ��
     */
    void setImage(QImage img);

    /*!
     *���ص�ǰͼƬ
     *@return QImage
     */
    QImage image();
    
private:
    //GImageEditor�Ҳ�İ�ť������󵯳��ļ�ѡ��Ի���
    //����ѡ���µ�ͼƬ
    QPushButton *m_button;

    //������GImageEditor�л��Ƶ�ǰͼƬ
    QLabel *m_label;

    //��ΪQLabel������͸���ģ�����ں����һ��QFrame���ư�ɫ����
    //ȥ��͸��Ч��
    QFrame *m_frame;

private slots:
    void editorButtonClicked();
};

#endif // GLDIMAGEEDITER_H
