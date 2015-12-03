/*!
 *@file glodontreedrawinfo.h
 *@brief {�����������νṹ}
 *
 *@author Gaosy
 *@date 2012.9.7
 *@remarks {remarks}
 *Copyright (c) 1998-2012 Glodon Corporation
 */

#ifndef GLDTREEDRAWINFO_H
#define GLDTREEDRAWINFO_H

#include <QVector>
#include <QAbstractItemModel>
#include "GLDHeaderView.h"
#include "GLDIntList.h"

/*!   
 *@struct: TreeViewItem
 *@brief {���νṹ��һ���ڵ㣬�洢����һ�е��������νṹ�����Ϣ������������ʾ}
 *@author Gaosy 
 *@date 2012.9.10
 */
struct GTreeViewItem
{
    GTreeViewItem() : parentIndex(-1), expanded(true), hasChildren(false),
        hasMoreSiblings(false), childCount(0), hidden(0), treeLevel(0), modelIndex(QModelIndex()) {}

    int parentIndex; // parent item index in viewItems
    uint expanded : 1;
    uint hasChildren : 1; // if the item has visible children (even if collapsed)
    uint hasMoreSiblings : 1;
    uint childCount : 28; // total number of children
    uint hidden : 1;
    uint treeLevel : 16;
    QModelIndex modelIndex;
};

/*!   
 *@class: GlodonTreeDrawInfo
 *@brief {��������TableView�����νṹ����¼�����νṹ��ȫ����Ϣ}
 *@author Gaosy 
 *@date 2012.9.10
 */
class GLDTABLEVIEWSHARED_EXPORT GlodonTreeDrawInfo : public QObject
{
public:
    GlodonTreeDrawInfo(QObject *parent) : QObject(parent)
    {
        m_treeColumn = 0;
        m_header = NULL;
        model = NULL;
    }
    ~GlodonTreeDrawInfo();

    /*!
     *��model��ȡ���νṹ��ȫ�����ݵ�����
     *@return int
     */
    int modelSectionCount() const;

    /*!
     *ͨ��TableView�е�����model����ʼ�����νṹ
     *@param[in]  newModel  TableView�е�����model
     *@return ��
     */
    void setModel(QAbstractItemModel *newModel);

    /*!
     *���ݸ�����index��ȡ���Ӧ���к�
     *@param[in]  index
     *@return int
     */
    int rowNo(QModelIndex index);
    /**
     * @brief �������������ν���ʾ��
     * @param value
     */
    void setTreeColumn(int value);
    int treeColumn();

    /**
     * @brief ����һ����������ʾ��Row���õ��ýڵ����һ���������Ľڵ����
     * @param parentRow
     * @return
     */
    int lastChildRow(int parentRow);

    void reset();

    void calculateRollOut();
    /**
     * @brief ����һ����������ʾ��row���õ��ýڵ�ĸ��ڵ�
     * @param row
     * @return
     */
    int calculateRoot(int row);

public:

    //���νṹ��Ҫ�����нڵ�ļ���
    QVector<GTreeViewItem> m_viewItems;

    //TableView����ֱ��ͷ���������νṹ��չ�����۵�����������ʱ
    //��ʾ�����أ���չ�����۵���������
    GlodonHeaderView *m_header;

    //TableView�е�����model
    QAbstractItemModel *model;

    void doExpandItem(int row, QSet<int> &oExpandRows);
    int doCollapseItem(int row, QSet<int> &oCollapseRows);

public Q_SLOTS:

    /*!
     *Ϊparent�м���һ�����У��������²��������ڵ��к�
     *@param[in]  parent  
     *@return int
     */
    int insertViewItem(int parent, QModelIndex index);

    /*!
     *ɾ��һ��
     *@param[in]  row  Ҫɾ������
     *@return ��
     */
    void removeViewItem(int row);

    /*!
     *�ƶ�һ���ࣩ��
     *@param[in]  parent             Ҫ�ƶ����еĸ��ڵ��к�
     *@param[in]  first              Ҫ�ƶ��������丸�ڵ��µ���ʼ�к�
     *@param[in]  last               Ҫ�ƶ��������丸�ڵ��µ�ĩβ�к�
     *@param[in]  destinationParent  �ƶ�Ŀ�ĵصĸ��ڵ��к�
     *@param[in]  row                �ƶ�Ŀ�ĵ����丸�ڵ��µ�λ��
     *@return ��
     */
    void moveViewItem(int parent, int first, int last, int destinationParent, int row);

    /*!
     *չ��һ��
     *@param[in]  row
     *@return ��
     */
    void expandItem(int row);

    /*!
     *�۵�һ��
     *@param[in]  row  
     *@return ��
     */
    int collapseItem(int row);

    /*!
     *չ��ȫ���ڵ�
     *@return ��
     */
    void expandAll();

    /*!
     *�۵�ȫ���ڵ�
     *@return ��
     */
    void collapseAll();

    /*!
     *����model�еĸ��ӹ�ϵ����ʼ���������νṹ
     *@param[in]  expandAll  Ĭ��ȫ��չ��
     *@return ��
     */
    void init(bool expandAllLevel = true);

private:
    void setChildItemsExpand(QSet<int> &oExpandRows, int row);

    /**
     * @brief �����νṹǰ�����ת��Ϊ���Խṹ
     */
    void transformTreeByLevel(int &index, const QModelIndex &parent, int level);
    void transformModelFromTreeToLine();

    void refreshModelIndexAfterMove(int parent, int row);
    void refreshModelIndexAfterInsertOrRemove(int row, int parent, bool insert);
    void refreshChildModelIndex(int parent);

    // Todo: ǰ�������treeBuildӦ�úϲ�
    void buildTree(bool shouldExpandAllLevel, bool buildHeaderLater = false);
    void switchNodeExpandState(
            bool shouldExpandAllLevel, bool buildHeaderLater, int i,
            QSet<int> &hiddenSections, QSet<int> &visibleSections);

    int setChildItemsCollapse(int row, QSet<int> &oCollapseRows);

    /**
     * @brief �ݹ��ȡ������
     * @param index
     * @return �����У������ӽڵ����
     */
    int childRowCount(QModelIndex index  = QModelIndex()) const;

private:
    int m_treeColumn;//��ʾ���νṹ����
};

#endif // GLDTREEDRAWINFO_H
