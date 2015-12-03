/*!
 *@file gfooterview.h
 *@brief {�ϼ���}
 *�̶�����ʾ��TableView���·�
 *@author Gaosy
 *@date 2012.9.7
 *@remarks {֧�ֶ��У��ɽ��кϲ�����Ҫ����setModel}
 *Copyright (c) 1998-2012 Glodon Corporation
 */

#ifndef GLDFOOTERVIEW_H
#define GLDFOOTERVIEW_H

#include "GLDTableView.h"

class GFooterViewPrivate;

/*!   
 *@class: GFooterView
 *@brief {�ϼ��У�ΪGrid�ṩ�ϼ��й��ܣ�֧�ֶ��кͺϲ�����Ҫ����setModel}
 *@author Gaosy 
 *@date 2012.9.7
 */
class GLDTABLEVIEWSHARED_EXPORT GFooterView : public GlodonTableView
{
    Q_OBJECT

public:
    /*!
     *GFooterView���췽��
     *@param[in]  parent  ��widget
     *@return ��
     */
    GFooterView(QWidget *parent);

    /*!
     *ΪGFooterView����model,���ںϼ��е�������ʾ�ͱ༭����������TableView�������ݶ���
     *@param[in]  model  
     *@return ��
     */
    void setModel(QAbstractItemModel *model);

    /*!
     *��ȡ�ؼ��ĸ߶�
     *@return int
     */
    int height() const;
    void paintEvent(QPaintEvent *e);
    void resetCurrentIndex(const QModelIndex &current);

    void setVerticalHeaderDrawWidth(int width);

Q_SIGNALS:
    void currentIndexChanged(const QModelIndex &current);

public Q_SLOTS:
    /*!
     *����ͬ��resize����
     *@param[in]  logicalIndex  resize�����������߼��У�Model�е��У�
     *@param[in]  oldSize       resizeǰ���еĿ��
     *@param[in]  size          resize����еĿ��
     *@return ��
     */
    void resizeSection(int logicalIndex, int oldSize,int size);
    /*!
     *����ͬ�����ƶ�����
     *@param[in]  logicalIndex  ���ƶ������������߼��У�Model�е��У�
     *@param[in]  oldSize       ���ƶ�ǰ����������λ��
     *@param[in]  size          ���ƶ������������λ��
     *@return ��
     */
    void moveSection(int logicalIndex, int from, int to);
    void setOffset(int offset);
    void currentChanged(const QModelIndex &current, const QModelIndex &previous);
private:
    Q_DECLARE_PRIVATE(GFooterView)
};

/**
 * @brief FooterView��Delegate, ���ܱ༭
 */
class GLDTABLEVIEWSHARED_EXPORT GFooterViewDelegate : public GlodonDefaultItemDelegate
{
public:
    explicit GFooterViewDelegate(QObject *parent = 0);
    GEditStyle editStyle(const QModelIndex &index, bool &readOnly) const;
};

#endif // GLDFOOTERVIEW_H

