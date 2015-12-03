#ifndef GLDTREEVIEW_H
#define GLDTREEVIEW_H

#include <QTreeView>
#include <QLabel>
#include <QStyledItemDelegate>
#include "GLDTableView_Global.h"

class GLDTreeDefaultDelegaet;

class GLDTABLEVIEWSHARED_EXPORT GlodonTreeView : public QTreeView
{
    Q_OBJECT
public:
    enum STATE{
        NONE,
        DragSection
    };

    enum DragStyle
    {
        DotLineStyle,
        LabelStyle
    };

public:
    GlodonTreeView(QWidget *parent = 0);

public:
    inline bool childNodeDragable() const { return m_rowDragable; }
    inline void setChildNodeDragable(bool val) { m_rowDragable = val; }

    /*!
     * \brief �ڵ�չ��ʱ���Զ�����������λ��
     * \param value
     * \warning ���ͨ��expand�źţ������������أ�����Ҫ���������������ź�֮�������ø�ѡ��
     */
    void setAutoResetScrollBarAfterExpand(bool value);
    inline bool autoResetScrollBarAfterExpand() { return m_autoResetScrollBarAfterExpand; }

    void reset();

signals:
    void canSectionMove(QModelIndexList from, QModelIndex to, Qt::KeyboardModifiers keyModifiers, bool &canMove, QCursor &cursor);
    void sectionMove(QModelIndexList from, QModelIndex to, Qt::KeyboardModifiers keyModifiers);

protected:
    bool viewportEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

protected:
    virtual QStyleOptionViewItem initOption();
    virtual void afterExpandedChanged(const QModelIndex &index, bool expanded);
    virtual void canDrag(QModelIndexList from, QModelIndex to, Qt::KeyboardModifiers keyModifiers, bool &canMove, QCursor &cursor);
    virtual void moveIndex(QModelIndexList from, QModelIndex to, Qt::KeyboardModifiers keyModifiers);

private slots:
    void doExpanded(const QModelIndex &index);
    void doCollapsed(const QModelIndex &index);
    void autoResetScrollBarOnExpand(const QModelIndex &index);
    /*!
     * \brief �ڹرձ༭�󣬽��༭�в������쳣�׳�
     * \param editor
     * \param hint
     */
    void afterCloseEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint = QAbstractItemDelegate::NoHint);

private:
    void init();
    void setupIndexIndicator(QModelIndexList indexs, QPoint pt);
    void updateIndexIndicator(QPoint pt);
    QModelIndex findLastModelIndex(const QModelIndex &index, const QModelIndex &parentIndex, int nCurrentHeight);
    /*!
     * \brief �����쳣��Ϣ�������ڱ༭��ɺ󽫱༭�в������쳣�׳�
     * \param errCode
     * \param errMessage
     */
    void setErrorMessage(int errCode, const QString &errMessage);

private:
    bool m_rowDragable;
    QPoint m_ptStart;
    QLabel *m_pIndicator;
    QModelIndexList m_indexFrom;
    DragStyle m_dragStyle;

    STATE m_state;
    bool m_canSectionMove;
    QModelIndex m_expandIndex;
    bool m_autoResetScrollBarAfterExpand;
    int m_errCode;
    QString m_errMessage;
private:
    friend class GLDTreeDefaultDelegaet;
};

class GLDTABLEVIEWSHARED_EXPORT GLDTreeDefaultDelegaet : public QStyledItemDelegate
{
public:
    GLDTreeDefaultDelegaet(QObject *parent = 0);
    virtual ~GLDTreeDefaultDelegaet() {}
public:
    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const;
private:
    void doSetModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index);
};

#endif // GLDTREEVIEW_H
