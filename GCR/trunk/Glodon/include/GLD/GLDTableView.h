/*!
 *@file GLDTableView.h
 *@brief {����༭�ؼ�}
 *
 *@remarks {}
 *Copyright (c) 1998-2015 Glodon Corporation
 */

#pragma once

#include "GLDTableViewBasic.h"

const GString c_sTableViewQssFile = ":/qsses/GLDTableView.qss";

class GlodonTableViewPrivate;
class GlodonTreeDrawInfo;

class GLDTABLEVIEWSHARED_EXPORT GlodonTableView :  public GLDTableView
{
    Q_OBJECT

public slots:
    /*!
     *����һ��
     *@param[in]  row  �߼��к�
     *@return ��
     */
    virtual void hideRow(int row);
    void groupChanged(QVector<int> newGroup);

public:
    explicit GlodonTableView(QWidget *parent = 0);
    ~GlodonTableView();
    /*!
     *����ģʽ�£�չ��ĳһ�У���ָ���Ƿ����ź�
     *@param[in]  row         �߼��к�
     *@param[in]  emitSignal  �Ƿ����ź�
     *@return ��
     */
    void expand(int row, bool emitSignal);

    /*!
     *����ģʽ�£��۵�ĳһ�У���ָ���Ƿ����ź�
     *@param[in]  row         �߼��к�
     *@param[in]  emitSignal  �Ƿ����ź�
     *@return ��
     */
    void collapse(int row, bool emitSignal);

    /*!
     *����ģʽ�£��ж�ĳһ���Ƿ�չ��
     *@param[in]  row  �߼��к�
     *@return bool
     */
    bool isRowExpanded(int row);

    /*!
     *����ģʽ�£�չ��ȫ���ڵ�
     *@return ��
     */
    virtual void expandAll();

    /*!
     *����ģʽ�£��۵�ȫ���ڵ�
     *@return ��
     */
    virtual void collapseAll();

    /*!
     *���ø��ڵ㣬ͨ������QModelIndex()
     *@param[in]  index  һ��ΪQModelIndex()
     *@return ��
     *@see �μ�GlodonAbstractItemView::setRootIndex(const QModelIndex &index)
     */
    void setRootIndex(const QModelIndex &index);

    /*!
     *��ȡ���Ӷ�Ӧ��treeModel�е�index
     *@return ��
     */
    virtual QModelIndex treeIndex(const QModelIndex &index) const;

    /*!
     *��ȡ���Ӷ�Ӧ��dataModel�е�index
     *@return ��
     */
    virtual QModelIndex dataIndex(const QModelIndex &index) const;

    /*!
     *������ʾ����£���ȡ��ǰ���Ӷ�Ӧ��dataModel�е�index
     *@return ��
     */
    QModelIndex currentDataIndex() const;

    /**
     * @brief �����Ƿ����νṹ��ʾ
     *        ��setModel��ʹ��
     *        ���ø÷������ᵼ��֮ǰ���õ��и߲�������
     *        �����ȵ��ø÷������������и�
     * @param value
     */
    void setIsTree(bool value);
    bool isTree() const;

    /**
     * @brief �����Ƿ����ģʽ��ʾ
     * @param value
     */
    void setIsGroupMode(bool groupModeEnable);

    bool isGroupMode() const;

    /**
     * @brief ����������ʾ�£�չ��/�۵�ͼ�����ʽ
     * @param style
     */
    void setTreeDecorationStyle(TreeDecorationStyle style);
    TreeDecorationStyle treeDecorationStyle() const;

    void setTreeDrawInfo(GlodonTreeDrawInfo *tableViewDrawInfo);
    GlodonTreeDrawInfo *treeDrawInfo();

    /**
     * @brief �����νṹʱ��ѡ���۵��ĸ����Ƿ�ͬʱѡ����
     * @return
     */
    bool isAddChildToSelection();
    void setAddChildToSelection(bool value);

    /**
     * @brief �������νṹ���ڵ��к�
     * @param column
     */
    void setTreeColumn(int column);
    int treeColumn();

protected slots:
    void reBuildTree();

    virtual void dataChanged(const QModelIndex &topLeft,
                             const QModelIndex &bottomRight,
                             const QVector<int> &roles);

protected:
    explicit GlodonTableView(GlodonTableViewPrivate &dd, QWidget *parent = 0);

    void doSetIsTree(bool value);
    virtual void doSetModel(QAbstractItemModel *model);

    /*!
     * \brief cellShowTreeWidthOffset
     * \return Ϊ����ʾ���εĸ��ӵ������������е�ˮƽ�����ƫ��(��Ҫ�����ɵ�ϸ�ߺ�branchͼ��ռȥ�Ŀ��)
     */
    int treeCellDisplayHorizontalOffset(int row, int col, bool isOldMinTextHeightCalWay = true) const;

    virtual void onBoolCellPress(QMouseEvent *event);
    virtual void onMousePress(QMouseEvent *event);
    virtual bool event(QEvent *event);

    virtual QAbstractItemModel* itemModel();

private:
    /**
     * @brief �����ǰ�ڵ�Ϊ�۵�״̬����ô��ѡ����ʱ���������е��Ӷ����ӵ�selection��
     * @param topLeft
     * @param bottomLeft
     * @param selection ��ǰ��Ҫ��ӵ�selectionModel�е�selection
     * @param isRowSelect �������ѡ״̬������Ҫ�жϸ����Ƿ����۵�
     */
    void setChildSelection(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                                            QItemSelection &selection, bool isRowSelect);
											
    void doGMExpand(GLDEvent *event);

    void doGMQueryExpand(GLDEvent *event);

    void doGMCollapse(GLDEvent *event);

    void doGMQueryCollapse(GLDEvent *event);

    void doGMExpandAll(GLDEvent *event);

    void doGMQueryExpandAll(GLDEvent *event);

    void doGMCollapseAll(GLDEvent *event);

    void doGMQueryCollapseAll(GLDEvent *event);

private:
    Q_DECLARE_PRIVATE(GlodonTableView)
    Q_DISABLE_COPY(GlodonTableView)
};
