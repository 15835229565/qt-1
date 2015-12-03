/*!
 *@file glodonfootertableview.h
 *@brief {����ɸѡ�м��ϼ��й��ܵ�Grid}
 *
 *@author Gaosy
 *@date 2012.9.7
 *@remarks {remarks}
 *Copyright (c) 1998-2012 Glodon Corporation
 */

#ifndef GLDFOOTERTABLEVIEW_H
#define GLDFOOTERTABLEVIEW_H

#include "GLDFilterTableView.h"
#include "GLDFooterView.h"
#include "GLDFooterModel.h"

class GlodonFooterTableViewPrivate;

/*!   
 *@class: GlodonFooterGrid
 *@brief {����ɸѡ�м��ϼ��й��ܵ�Grid��ɸѡ�п������أ��ϼ�����Ҫ����setModel}
 *@author Gaosy 
 *@date 2012.9.10
 */
class GLDTABLEVIEWSHARED_EXPORT GlodonFooterTableView : public GlodonFilterTableView
{
    Q_OBJECT

public:
    /*!
     *GlodonFooterGrid���췽��
     *@param[in]  parent  ��widget
     *@return ��
     */
    GlodonFooterTableView(QWidget *parent);

    /*!
     *����GlodonFooterGrid��ˮƽ��ͷ����ֱ��ͷ�����塢ɸѡ�С��ϼ��е�λ�ã�
     *���ϼ������ڱ�����·�
     *@return ��
     */
    void updateGeometries();

    /*!
     *Ϊ�ϼ�������model
     *@param[in]  model  �ϼ�����ʾ�ͱ༭��Ҫ��model
     *@return ��
     */
    void setFooterModel(QAbstractItemModel *model);

    /*!
     *����ˮƽ��ͷ����footer���ϼ��У����ͷ��resize��moveSection�ź�����
     *@param[int]  header  ˮƽ��ͷ
     *@return ��
     */
    void setHorizontalHeader(GlodonHeaderView *header);
    void setModel(QAbstractItemModel *model);

    bool totalRowAtFooter() const;
    void setTotalRowAtFooter(bool value);

    void setTotalRowCount(int value);
    void paintEvent(QPaintEvent *e);
    void setGridColor(QColor value);
    void setGridLineColor(QColor value);
    void setFixedColCount(int fixedColCount);
public:
    //�ϼ���
    GFooterView *footer();

protected Q_SLOTS:
    void beforeReset();
    void doReset();
    void afterReset();

protected:
    GlodonFooterTableView(GlodonFooterTableViewPrivate &dd, QWidget *parent);
    void resetModel();
    void createModel();

protected:
    void updateFooterGeometry(int nVerticalHeaderWidth);

private:
    Q_DECLARE_PRIVATE(GlodonFooterTableView)

    void changeVerticalHeaderDrawWidth();

protected Q_SLOTS:
    virtual void currentChanged(const QModelIndex &current, const QModelIndex &previous);
    void columnResized(int column, int oldWidth, int newWidth, bool isManual = false);
    void setCurrentIndex(const QModelIndex &dataIndex);
    void setCurrentIndexForFooter(const QModelIndex &current);
};

#endif // GLDFOOTERTABLEVIEW_H
