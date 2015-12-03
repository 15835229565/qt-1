/*!
 *@file gfilterview.h
 *@brief {ɸѡ��}
 *����ɸѡ����е�����
 *@author Gaosy
 *@date 2012.9.7
 *@remarks {λ����ˮƽ��ͷ֮�£�Ŀǰ��֧�ֵ���}
 *Copyright (c) 1998-2012 Glodon Corporation
 */

#ifndef GLDFILTERVIEW_H
#define GLDFILTERVIEW_H

#include "GLDHeaderView.h"
#include <QComboBox>

class GFilterViewPrivate;

/*!   
 *@class: GFilterView
 *@brief {ΪGrid�ṩɸѡ�еĹ��ܣ����Զ���ɸѡ��ʽ��Ĭ��ΪComboBox��ʽ}
 *@author Gaosy 
 *@date 2012.9.7
 */
class GLDTABLEVIEWSHARED_EXPORT GFilterView : public GlodonHeaderView
{
    Q_OBJECT
public:
    /*!
     *GFilterView���췽��
     *@param[in]  parent  ��widget
     *@return ��
     */
    GFilterView(QWidget *parent);

    /*!
     *��ȡlogicalIndex��һ�е�ɸѡ�ؼ�������
     *@param[in]  logicalIndex  ��Ҫ��ȡɸѡ�ؼ����ݵ��߼��кţ�Model�е��кţ�
     *@return QString 
     */
    QString filterData(int logicalIndex);

    /*!
     *ΪGFilterView����model��������Ϊ�˿�����ʾ��������û����������
     *@param[in]  model  
     *@return ��
     */
    void setModel(QAbstractItemModel *model);

    /*!
     *ʹGFilterView��ȡTableView��ʹ�õ�Model������Ĭ��ɸѡ��ʽ�Ľ���
     *@param[in]  filterModel  TableView��ʹ�õ�Model
     *@return ��
     */
    void setFilterDataModel(QAbstractItemModel *filterModel);

    /*!
     *��ȡindex���ڸ��ӵĴ�С
     *@param[in]  index  
     *@return QRect
     */
    QRect visualRect(const QModelIndex &index) const;

    /*!
     *GFilterView�Ļ��Ʒ���
     *@param[in]  e  
     *@return ��
     */
    void paintEvent(QPaintEvent *e);

    /*!
     *��ȡ�ؼ��ĸ߶�
     *@return int
     */
    int height() const;

public:
    //TableView�е�����Model������Filter��ɸѡ�г�ʼ��
    QAbstractItemModel *m_pFilterDataModel;
    void resetFilter(int col);
public Q_SLOTS:
    /*!
     *����ͬ��resize����
     *@param[in]  logicalIndex  resize�����������߼��У�Model�е��У�
     *@param[in]  oldSize       resizeǰ���еĿ��
     *@param[in]  size          resize����еĿ��
     *@return ��
     */
    void resizeSection(int logicalIndex, int oldSize, int size);

    /*!
     *����ͬ�����ƶ�����
     *@param[in]  logicalIndex  ���ƶ������������߼��У�Model�е��У�
     *@param[in]  oldSize       ���ƶ�ǰ����������λ��
     *@param[in]  size          ���ƶ������������λ��
     *@return ��
     */
    void moveSection(int logicalIndex, int from, int to);

    /*!
     *����ɸѡ�ؼ���ֵ�ĸı�
     *@return ��
     */
    void filterChanged();

    /*!
     *����ӦΪ����״̬����widgetΪ����״̬
     *@return ��
     */
    void hideHiddenSection(int hbarPos);

    void filterDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    void initFilterWidget();

Q_SIGNALS:
    void onFilterChanged(int column);
    QWidget* onQueryFilterWidget(int logicalIndex);

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
    void paintSection(int beginToHideIndex) const;
    void keyPressEvent(QKeyEvent *event);
    mutable bool m_bHideFlag;
private:
    Q_DECLARE_PRIVATE(GFilterView)
};

#endif // GLDFILTERVIEW_H
