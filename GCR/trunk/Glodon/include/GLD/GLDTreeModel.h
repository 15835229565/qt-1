/*!
 *@file glodontreemodel.h
 *@brief {ר��Ϊ���νṹ��ʾʱʹ�õ��м�̬Model}
 *
 *@author gaosy-a
 *@date 2012.9.7
 *@remarks {remarks}
 *Copyright (c) 1998-2012 Glodon Corporation
 */

#ifndef GLDTREEMODEL_H
#define GLDTREEMODEL_H

#include <QAbstractItemModel>
#include <QMimeData>
#include "GLDTreeDrawInfo.h"
#include "GLDAbstractItemModel.h"
#include "GLDGlobal.h"

/*!   
 *@class: GlodonTreeModel
 *@brief {ר��ΪTableView�����νṹ��ʾ��ʹ�õ��м�̬Model�����������ι�ϵ��Modelת��ȥ�����ι�ϵʹ��}
 *@author Gaosy 
 *@date 2012.9.10
 */
class GLDTABLEVIEWSHARED_EXPORT GlodonTreeModel : public GlodonAbstractItemModel
{
    Q_OBJECT
public:
    /*!
     *GlodonTreeModel�Ĺ��췽������ԭʼ���и��ӽṹ��model�ĸ��ӽṹȥ��
     *@param[in]  pModel  ���и��ӽṹ��ԭʼmodel
     *@param[in]  parent
     *@return ��
     */
    explicit GlodonTreeModel(QAbstractItemModel *pModel, QObject *parent = 0);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

    QMap<int, QVariant> itemData(const QModelIndex &index) const;
    bool setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles);

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value,
                       int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QStringList mimeTypes() const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                              int row, int column, const QModelIndex &parent);
    bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row,
                         int column, const QModelIndex &parent) const;
    QModelIndex dataIndex(int row, int column) const;
    QModelIndex dataIndex(const QModelIndex &index) const;

    QModelIndex treeIndex(const QModelIndex &dataIndex) const;

    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);

public:
    //�洢���ṹ��Ӧ����Ϣ����ÿһ�е�level���Ƿ����ӽڵ㡢�Ƿ��и��ڵ㡢�Ƿ�չ�����Ƿ���ʾ���Ƿ����ֵ�
    GlodonTreeDrawInfo *drawInfo;

    //ԭʼ���и��ӽṹ��model
    QAbstractItemModel *model;

    //ͳһ�ĸ��ڵ�
    QModelIndex root;

private Q_SLOTS:
    void onRowRemoved(const QModelIndex &parent, int first, int last);
    void onRowInserted(const QModelIndex &parent, int first, int last);
    void onRowMoved(const QModelIndex &parent, int start, int end, const QModelIndex &destination, int row);
    void onUpdate(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                  const QVector<int>&roles = QVector<int>());
    void onResetModel();

    int visualRowNo(const QModelIndex &parent, int row) const;
};

#endif // GLDTREEMODEL_H
