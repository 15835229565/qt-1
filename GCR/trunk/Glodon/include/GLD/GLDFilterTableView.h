/*!
 *@file glodonfiltertableview.h
 *@brief {�ṩɸѡ���ܵ�Grid}
 *
 *@author Gaosy
 *@date 2012.9.7
 *@remarks {remarks}
 *Copyright (c) 1998-2012 Glodon Corporation
 */

#ifndef GLDFILTERTABLEVIEW_H
#define GLDFILTERTABLEVIEW_H

#include "GLDTableView.h"
#include "GLDFilterView.h"
#include "GLDGlobal.h"

class GlodonFilterTableViewPrivate;

/*!
 *@class: GlodonFilterTableView
 *@brief {�ṩɸѡ�е�Grid��ͨ����ɸѡ������ɸѡ��ʽ�����Զ���ɸѡ��ʽ��Ĭ��ΪComboBox}
 *@author Gaosy
 *@date 2012.9.10
 */
class GLDTABLEVIEWSHARED_EXPORT GlodonFilterTableView : public GlodonTableView
{
    Q_OBJECT

public:
    /*!
        *GlodonFilterTableView���췽��
        *@param[in]  parent  ��widget
        *@return ��
        */
    GlodonFilterTableView(QWidget *parent);

    /*!
        *ΪGlodonFilterTableView����model,����������ʾ�ͱ༭��ͬʱΪfilter��ɸѡ�У�����model
        *@param[in]  model
        *@return ��
        */
    void setModel(QAbstractItemModel *model);

    /*!
        *GlodonFilterTableView�Ļ��Ʒ��������ø���GlodonTableView�Ļ��Ʒ���
        *@param[in]  e
        *@return ��
        *@see �μ�GlodonTableView::paintEvent(QPaintEvent *e)
        */
    void paintEvent(QPaintEvent *e);

    /*!
        *����ˮƽ��ͷ����filter��ɸѡ�У����ͷ��resize��moveSection�ź�����
        *@param[in]  header  ˮƽ��ͷ
        *@return ��
        */
    void setHorizontalHeader(GlodonHeaderView *header);

    /*!
        *�����Ƿ���ʾfilter��ɸѡ�У�
        *@param[in]  hide  trueΪ����filter��ɸѡ�У���falseΪ��ʾfilter��ɸѡ�У�
        *@return ��
        *@warning ���ʹ�õ���GSPDataSource��������GSPDataSource��setActive�������ù����пɼ�
        */
    void setIsDisplayFilter(bool show);
    /**
        * @brief �Ƿ���ʾ������
        * @return
        */
    bool isDisplayFilter();

    /*!
        *����GlodonFilterTableView��ˮƽ��ͷ����ֱ��ͷ�����塢ɸѡ�е�λ�ã�
        *��ɸѡ������ˮƽ��ͷ�ͱ���֮��
        *@return ��
        */
    void updateGeometries();

    /*!
        *���ù̶��ɱ༭����
        *@param[in]  fixedColCount  �̶��ɱ༭����
        *@return ��
        */
    void setFixedColCount(int fixedColCount);

    //ɸѡ��
    GFilterView *filter();
    void setGridColor(QColor value);
    void setGridLineColor(QColor value);

public Q_SLOTS:
    /*!
        *����Ĭ������µ�ɸѡ
        *@param[in]  column  The memory area to copy from.
        *@return ��
        */
    void changeViewItemsForFilter(int column);

protected Q_SLOTS:
    void columnResized(int column, int oldWidth, int newWidth, bool isManual = false);

Q_SIGNALS:
    bool onFilterData(int row);

protected:
    GlodonFilterTableView(GlodonFilterTableViewPrivate &dd, QWidget *parent);
    void timerEvent(QTimerEvent *event);
    void resetModel(QAbstractItemModel *dataModel);

    virtual void resetEllipsisButtonLocation();

    bool isFilterHide();

protected:
    // �ع�updateGeometries
    void updateFilterViewGeometry(int nFilterViewHeight);
    void updateHorizontalHeaderGeometry(int nHorizontalHeaderHeight, int nFilterViewHeight);

private:
    bool m_bDisplayFilter;
    Q_DECLARE_PRIVATE(GlodonFilterTableView)
};

#endif // GLDFILTERTABLEVIEW_H
