/*!
 *@file glodonabstractitemview.h
 *@brief {����View�ĳ���}
 *������һЩ��Ҫ���̣���༭������¼���setModel��
 *@author Gaosy
 *@date 2012.9.7
 *@remarks {remarks}
 *Copyright (c) 1998-2012 Glodon Corporation
 */

#ifndef GLDABSTRACTITEMVIEW_H
#define GLDABSTRACTITEMVIEW_H

#include <QObject>
#include <QPointer>
#include <QAbstractItemModel>
#include <QApplication>
#include <QEvent>
#include <QMimeData>
#include <QPainter>
#include <QPair>
#include <QRegion>
#include <QPainter>
#include <QBasicTimer>
#include <QElapsedTimer>
#include <QModelIndex>
#include <QDialog>
#include <QAbstractScrollArea>
#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include "GLDString.h"
#include "GLDEvent.h"
#include "GLDDefaultItemDelegate.h"
#include "GLDTextEdit.h"
#include "GLDCommentFrame.h"

class QLabel;
class QMenu;
class QDrag;
class QEvent;
class GlodonAbstractItemView;
class GlodonAbstractItemViewPrivate;

/*!   
 *@struct: GEditorInfo
 *@brief {����༭��ʽ�����ڿ��ٴ�ȡ�༭����ؼ�}
 *@author Gaosy 
 *@date 2012.9.7
 */
struct GEditorInfo {
    GEditorInfo(QWidget *e, bool s): widget(QPointer<QWidget>(e)), isStatic(s) {}

    GEditorInfo(): isStatic(false) {}

    QPointer<QWidget> widget;
    bool isStatic;
};

typedef QHash<QWidget *, QPersistentModelIndex> GEditorIndexHash;
typedef QHash<QPersistentModelIndex, GEditorInfo> GIndexEditorHash;

typedef QPair<QRect, QModelIndex> GItemViewPaintPair;
typedef QList<GItemViewPaintPair> GItemViewPaintPairs;

/*!   
 *@class: GEmptyModel
 *@brief {��Model��û�����ݣ������ڳ�ʼ��ʱʹ��}
 *@author Gaosy 
 *@date 2012.9.7
 */
class GLDTABLEVIEWSHARED_EXPORT GEmptyModel : public QAbstractItemModel
{
public:
    explicit GEmptyModel(QObject *parent = 0) : QAbstractItemModel(parent) {}

    QModelIndex index(int, int, const QModelIndex &) const { return QModelIndex(); }

    QModelIndex parent(const QModelIndex &) const { return QModelIndex(); }

    int rowCount(const QModelIndex &) const { return 0; }

    int columnCount(const QModelIndex &) const { return 0; }

    bool hasChildren(const QModelIndex &) const { return false; }

    QVariant data(const QModelIndex &, int) const { return QVariant(); }
};

/*!   
 *@class: GlodonAbstractItemView
 *@brief {����View�ĳ����࣬���������ݱ༭������¼�������װ�أ�setModel����ѡ���ƶ����㡢���ñ༭��ʽ�ȹ��ܣ����̣�}
 *@author Gaosy 
 *@date 2012.9.7
 */
class GLDTABLEVIEWSHARED_EXPORT GlodonAbstractItemView : public QAbstractScrollArea
{
    Q_OBJECT

    Q_ENUMS(SelectionMode SelectionBehavior ScrollHint ScrollMode DragDropMode)
    Q_FLAGS(EditTriggers)
    Q_PROPERTY(bool autoScroll READ hasAutoScroll WRITE setAutoScroll)
    Q_PROPERTY(int autoScrollMargin READ autoScrollMargin WRITE setAutoScrollMargin)
    Q_PROPERTY(EditTriggers editTriggers READ editTriggers WRITE setEditTriggers)
    Q_PROPERTY(bool tabKeyNavigation READ tabKeyNavigation WRITE setTabKeyNavigation)
#ifndef QT_NO_DRAGANDDROP
    Q_PROPERTY(bool showDropIndicator READ showDropIndicator WRITE setDropIndicatorShown)
    Q_PROPERTY(bool dragEnabled READ dragEnabled WRITE setDragEnabled)
    Q_PROPERTY(bool dragDropOverwriteMode READ dragDropOverwriteMode WRITE setDragDropOverwriteMode)
    Q_PROPERTY(DragDropMode dragDropMode READ dragDropMode WRITE setDragDropMode)
    Q_PROPERTY(Qt::DropAction defaultDropAction READ defaultDropAction WRITE setDefaultDropAction)
#endif
    Q_PROPERTY(bool alternatingRowColors READ alternatingRowColors WRITE setAlternatingRowColors)
    Q_PROPERTY(SelectionMode selectionMode READ selectionMode WRITE setSelectionMode)
    Q_PROPERTY(SelectionBehavior selectionBehavior READ selectionBehavior WRITE setSelectionBehavior)
    Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(Qt::TextElideMode textElideMode READ textElideMode WRITE setTextElideMode)
    Q_PROPERTY(ScrollMode verticalScrollMode READ verticalScrollMode WRITE setVerticalScrollMode)
    Q_PROPERTY(ScrollMode horizontalScrollMode READ horizontalScrollMode WRITE setHorizontalScrollMode)

public:
    /*!
     *@enum: SelectionMode
     *@brief {ѡ��ģʽ}
     *@author Gaosy
     *@date 2012.9.10
     */
    enum SelectionMode {
        NoSelection,
        SingleSelection,
        MultiSelection,
        ExtendedSelection,
        ContiguousSelection
    };

    /*!
     *@enum: SelectionBehavior
     *@brief {ѡ����Ϊ��ѡ���ӡ�ѡ�С�ѡ��}
     *@author Gaosy
     *@date 2012.9.10
     */
    enum SelectionBehavior {
        SelectItems,
        SelectRows,
        SelectColumns
    };

    /*!
     *@enum: ScrollHint
     *@brief {����������λ�ÿ���}
     *@author Gaosy
     *@date 2012.9.10
     */
    enum ScrollHint {
        EnsureVisible,
        PositionAtTop,
        PositionAtBottom,
        PositionAtCenter
    };

    /*!
     *@enum: EditTrigger
     *@brief {����༭״̬�ķ�ʽ}
     *@author Gaosy
     *@date 2012.9.10
     */
    enum EditTrigger {
        NoEditTriggers = 0,
        CurrentChanged = 1,
        DoubleClicked = 2,
        SelectedClicked = 4,
        EditKeyPressed = 8,
        AnyKeyPressed = 16,
        AllEditTriggers = 31
    };

    Q_DECLARE_FLAGS(EditTriggers, EditTrigger)

    /*!
     *@enum: ScrollMode
     *@brief {������ʽ��������ӹ�����������ع���}
     *@author Gaosy
     *@date 2012.9.10
     */
    enum ScrollMode {
        ScrollPerItem,  // ��ûһ�񣬼�һ������ɿɼ���Ϊ���ɼ�
        ScrollPerPixel
    };

    // �Ǳ༭״̬�£�ֻҪ��ʾ�༭��ʽ������ʾ���ɲ���������Ҫ��ȡ����
    enum EditStyleDrawType {
        SdtNone = 0,         // ����ʾ�༭��ʽ
        SdtCurrentCell = 1,  // ��ʾ�������ڸ��ӵı༭��ʽ
        SdtCurrentRow = 2,   // ��ʾ���������еı༭��ʽ
        SdtCurrentCol = 3,   // ��ʾ���������еı༭��ʽ
        SdtAll = 4           // ���еı༭��ʽ����ʾ
    };
    /*!
     *@enum: DragDropMode
     *@brief {��ק��ʽ}
     *@author Gaosy
     *@date 2012.9.10
     */
    enum DragDropMode {
        NoDragDrop,
        DragOnly,
        DropOnly,
        DragDrop,
        InternalMove
    };

    /*!
     *@enum: State
     *@brief {��ǰView��״̬}
     *@author Gaosy
     *@date 2012.9.10
     */
    enum State {
        NoState,              // ����Ĭ��״̬
        DraggingState,        // ������קItem
        DragSelectingState,   // ����ѡ��Item
        EditingState,         // ���ڱ༭Item
        ExpandingState,       // ����չ���ڵ�
        CollapsingState,      // �����۵��ڵ�
        AnimatingState,       // View���ڶ���״̬
        RangeFillingState,    // ���ڽ�����������
        RangeMovingState,     // ���ڽ��п�ѡ��ק
        DragResizingState     // ������ק�ı��С
    };

    /*!
     *@enum: State
     *@brief {���񿪹ؿ���ʱ��ǰ���ӵ�״̬}
     *@author Chenq-a
     *@date 2013.9.5
     */
    enum EnterMovingState {
        FirstFocus,   // ��һ�λ�ø��ӽ���
        Editting,     // �����˱༭��
        LastFocus     // �ӱ༭���˳�ʱ��ý������ʱ״̬
    };

    /*!
     *@enum: CursorAction
     *@brief {�ƶ�����ķ���}
     *@author Gaosy
     *@date 2012.9.13
     */
    enum CursorAction {
        MoveUp,
        MoveDown,
        MoveLeft,
        MoveRight,
        MoveHome,
        MoveEnd,
        MovePageUp,
        MovePageDown,
        MoveNext,
        MovePrevious
    };

public:
    explicit GlodonAbstractItemView(QWidget *parent = 0);
    ~GlodonAbstractItemView();

public:
    // һ��Qt����
    // 1. ����ѡ��
    /**
     * @brief QAbstractItemView���������ҵ����������ֵ��Item���ƶ���ȥ��ѡ�С�
     *        ���������ֵΪ�գ�����������
     * @param search Ҫ���ҵ�ֵ
     */
    virtual void keyboardSearch(const QString &search);

    /**
     * @brief QAbstractItemView�������������뷨����
     * @param query ���ֿ��ƣ����������
     */
    virtual QVariant inputMethodQuery(Qt::InputMethodQuery query) const;

    /**
     * @brief QAbstractItemView����������Item��Tab��backTab���п���
     * @param enable
     */
    void setTabKeyNavigation(bool enable);
    bool tabKeyNavigation() const;

#ifndef QT_NO_DRAGANDDROP
    /**
     * @brief QAbstractItemView����������ViewPort�Ƿ�������ק����Item
     * @param enable
     */
    void setDragEnabled(bool enable);
    bool dragEnabled() const;

    /**
     * @brief QAbstractItemView����������Drag\Dropʱ��ViewPort�Ĳ���
     * @param behavior
     */
    void setDragDropMode(DragDropMode behavior);
    DragDropMode dragDropMode() const;

    /**
     * @brief QAbstractItemView����������ViewPort�ϵ�Item���϶��ͷ�ʱ�Ĳ���
     *        �����true����ԭ����Item�滻Ϊ�϶���Item
     *        �����false�������һ���µ�Item
     * @param overwrite
     */
    void setDragDropOverwriteMode(bool overwrite);
    bool dragDropOverwriteMode() const;

    /**
     * @brief QAbstractItemView����������Ĭ�ϵ�Drop����
     * @param dropAction
     */
    void setDefaultDropAction(Qt::DropAction dropAction);
    Qt::DropAction defaultDropAction() const;

    /**
     * @brief QAbstractItemView��������������קItem�ͽ�����קItemʱ���Ƿ���ʾ��ʾ
     * @param enable
     */
    void setDropIndicatorShown(bool enable);
    bool showDropIndicator() const;
#endif

    // 2. ���ѡ��
    /**
     * @brief QAbstractItemView����������QStyleOptionViewItem�ṹ�壬������������
     */
    virtual QStyleOptionViewItem viewOptions() const;

    /**
     * @brief QAbstractItemView�������飬������������������Index
     * @param index Ŀ��Index
     * @param hint
     */
    virtual void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) = 0;

    /**
     * @brief ����ѡ��ģʽ������Ϊ��ѡ����ѡ��
     * @param mode
     */
    void setSelectionMode(GlodonAbstractItemView::SelectionMode mode);
    GlodonAbstractItemView::SelectionMode selectionMode() const;

    /**
     * @brief ����ѡ��ģʽ����ѡ��������ѡ
     * @param behavior Ĭ��ֵ SelectItems
     */
    void setSelectionBehavior(GlodonAbstractItemView::SelectionBehavior behavior);
    GlodonAbstractItemView::SelectionBehavior selectionBehavior() const;

    /**
     * @brief ���ô�ֱ�������Ĺ���ģʽ��������ӹ�����������ع�����
     * @param mode
     */
    void setVerticalScrollMode(ScrollMode mode);
    ScrollMode verticalScrollMode() const;

    /**
     * @brief ����ˮƽ�������Ĺ���ģʽ��������ӹ�����������ع�����
     * @param mode
     */
    void setHorizontalScrollMode(ScrollMode mode);
    ScrollMode horizontalScrollMode() const;

    /*!
     *@brief ���ø��б���ɫ��ͬ
     *@param[in]  enable
     *@return ��
     */
    void setAlternatingRowColors(bool enable);
    bool alternatingRowColors() const;

    /*!
     *@brief ����Itemͼ���С
     *@param[in]  enable
     *@return ��
     */
    void setIconSize(const QSize &size);
    QSize iconSize() const;

    /**
     * @brief ��ȡ/���ã��Զ���������
     * @return
     */
    void setAutoScrollMargin(int margin);
    int autoScrollMargin() const;

    /**
     * @brief ����Ҽ���ʱ������tooltip����
     * @return ��
     */
    void setToolTipFrameHide();

public:
    // Glodon����
    // 1. ����ѡ��
    /**
     * @brief �����Ƿ�ѡ���ƶ�
     * @param value
     */
    virtual void setAllowRangeMoving(bool value);
    virtual bool allowRangeMoving() const;

    /**
     * @brief �Ƿ��ܿ�ʼdrag
     * @param indexes
     * @return
     */
    virtual bool canStartDrag(QModelIndexList indexes);

    // 2. ���ѡ��
    /**
     * @brief �����Ƿ�����ȫѡ
     * @return
     */
    void setAllowSelectAll(bool value);
    bool allowSelectAll() const;

    /**
     * @brief ���������е����ֻ���ʱ�Ƿ��ð����м��
     * @return
     */
    void setGridTextIncludeLeading(bool value);
    bool gridTextIncludeLeading() const;

    /**
     * @brief �����ק������ʱ���Ƿ����ɿ�������ʱ�̲Ž��б������Ĺ���
     * @param value
     */
    void setScrollBarTracking(bool value);
    bool scrollBarTracking() const;

    /**
     * @brief ���ñ��ViewPort������ɫ
     * @return
     */
    virtual void setGridColor(QColor value);
    QColor gridColor() const;

    /**
     * @brief ���õ�����������ʾ��ȫʱ���Ƿ���ʾ��ʾ��
     * @param value
     * @param showIndexContext ���toolTipRoleû��ֵ���Ƿ���ʾ�����е�ֵ
     */
    void setIsShowHint(bool value, bool showIndexContent = false);
    void setShowHintDelay(int time);

    /**
     * @brief ��ȡ/���ã���ֱ�����������ֵ
     * @return
     */
    void setVerticalScrollBarValue(int value);
    int verticalScrollbarValue();

    /**
     * @brief �����Ƿ���ȫ��ʾ��ǰ����ĸ��ӣ���Ҫ���ڿ����ڵ�ǰ���Ӳ�����ʾʱ�ĵ����Ϊ����:�Ƿ������������ʹ�ø���ȫ��ʾ
     * @param value
     * @note ����layout�����£�û�й�����ʱ����ʾ����ȫ����󲻻���Ч��
     */
    void setShowPressIndex(bool value);

    /**
     * @brief ��ȡ/���ã������������ֵ
     * @return
     */
    void setHorizontalScrollbarValue(int value);
    int horizontalScrollbarValue();

    /**
     * @brief �õ�StyleOptionViewItem
     */
    QStyleOptionViewItem StyleOptionViewItem();

public:
    virtual QWidget *initCustomComment(const QModelIndex &index, GString &text);
    virtual QRect visualRect(const QModelIndex &index) const = 0;
    virtual QModelIndex indexAt(const QPoint &point) const = 0;
    GCommentFrame *commentFrame();

public:
    virtual void setModel(QAbstractItemModel *model);
    QAbstractItemModel *model() const;

    QSize sizeHintForIndex(const QModelIndex &index) const;
    virtual int sizeHintForRow(int row) const;
    virtual int sizeHintForColumn(int column) const;

    void setDataModel(QAbstractItemModel *dataModel);
    QAbstractItemModel *dataModel() const;

    /*!
     *����QItemselectionModel�����ڼ�¼��ǰ��ѡ������
     *@param[in]  selectionModel
     *@return ��
     */
    virtual void setSelectionModel(QItemSelectionModel *selectionModel);
    QItemSelectionModel *selectionModel() const;

    /*!
     *����QAbstractItemDelegate�����༭��ʽ��ĿǰĬ�ϳ�ʼ��ΪGlodonDefaultItemDelegate
     *�����Ҫ�������ñ༭��ʽ�����GlodonDefaultItemDelegate����
     *�����ȼ�����rowDelegate��columnDelegate��Ĭ�������rowDelegate��columnDelegateΪ��
     *@param[in]  delegate
     *@return ��
     */
    void setItemDelegate(GlodonDefaultItemDelegate *delegate);
    GlodonDefaultItemDelegate *itemDelegate() const;

    QModelIndex currentIndex() const;
    QModelIndex rootIndex() const;


    void openPersistentEditor(const QModelIndex &index);
    void closePersistentEditor(const QModelIndex &index);

    /*!
     *��ȡ����index��QAbstractItemDelegate�����ȼ�˳��Ϊ
     *rowDelegate > columnDelegate > itemDelegate
     *@param[in]  index
     *@return QAbstractItemDelegate*
     */
    GlodonDefaultItemDelegate *itemDelegate(const QModelIndex &index) const;

    /**
     * @brief �����ڱ༭״̬��ModelIndex
     * @return
     */
    QModelIndex editorModelIndex();

    /**
     * @brief ���ý���༭״̬�ķ�ʽ
     * @param triggers
     */
    void setEditTriggers(EditTriggers triggers);
    EditTriggers editTriggers() const;

    void setAutoScroll(bool enable);
    bool hasAutoScroll() const;

    /*!
     *Ϊ������index���ó־��Եı༭��ʽ����delegate�ı༭��ʽ���������ڣ�
     *���ַ�ʽ�ı༭�ؼ�widget������ʾ�������������˳��༭״̬������
     *@param[in]  index
     *@param[in]  widget
     *@return ��
     */
    void setIndexWidget(const QModelIndex &index, QWidget *widget);
    QWidget *indexWidget(const QModelIndex &index) const;

    /*!
     *Ϊ�����߼������ñ༭��ʽQAbstractItemDelegate�������ȼ�����columnDelegate��itemDelegate
     *@param[in]  row       �߼��к�
     *@param[in]  delegate
     *@return ��
     */
    void setItemDelegateForRow(int row, GlodonDefaultItemDelegate *delegate);
    GlodonDefaultItemDelegate *itemDelegateForRow(int row) const;

    /*!
     *Ϊ�����߼������ñ༭��ʽQAbstractItemDelegate�������ȼ�����rowDelegate������itemDelegate
     *@param[in]  column    �߼��к�
     *@param[in]  delegate
     *@return ��
     */
    void setItemDelegateForColumn(int column, GlodonDefaultItemDelegate *delegate);
    GlodonDefaultItemDelegate *itemDelegateForColumn(int column) const;

    /*!
     * \brief �������Ǵ��ڱ༭״̬���������tableView������еı༭��ʽ����������������setModel֮���dataSource�������ã�
     * \return
     */
    bool alwaysShowEditorPro();
    void setAlwaysShowEditorPro(bool value);

    /**
     * @brief �Ƿ�����������λ
     * @param value
     */
    void setIsSearchModel(bool value);
    bool isSearchModel();

    void setTextElideMode(Qt::TextElideMode mode);
    Qt::TextElideMode textElideMode() const;

#ifdef Q_NO_USING_KEYWORD
    inline void update() { QAbstractScrollArea::update(); }
#else
    using QAbstractScrollArea::update;
#endif

    /**
     * @brief �ж��Ƿ�����קѡ��״̬
     * @return
     */
    bool dragSelectingState(){return state() == DragSelectingState;}

Q_SIGNALS:
    void pressed(const QModelIndex &index);
    void clicked(const QModelIndex &index);
    void doubleClicked(const QModelIndex &index);

    void activated(const QModelIndex &index);
    void entered(const QModelIndex &index);
    void viewportEntered();
    void onQueryImageRatioMode(const QModelIndex &index, GlodonDefaultItemDelegate::GAspectRatioMode &ratioMode);
    void onQueryFloatOrDoubleViewFormat(const QModelIndex &index, QString &text);
    void onQueryIndexDataType(const QModelIndex &index, GlodonDefaultItemDelegate::GDataType &dataType);
    void onCommitEditor(const QModelIndex &index, QVariant data, bool &commit);
    void onCloseEditor(const QModelIndex &index, QVariant data, bool &close);
    void onPressEnter(GlodonAbstractItemView::CursorAction &direction);
    void onbeforeMoveCurrent(const QModelIndex &oldIndex, const QModelIndex &newIndex,
                             QItemSelectionModel::SelectionFlags &command,
                             MoveReason moveReason, bool &canMove);
    void onAfterMoveCurrent(const QModelIndex &oldIndex, const QModelIndex &newIndex,
                            QItemSelectionModel::SelectionFlags &command, MoveReason moveReason);
    void canShowComment(const QModelIndex &index, bool &canShow);

    void onEditorCanCopy(bool yes);
    void onEditorCanCut(bool yes);
    void onEditorCanPaste(bool yes);
    void onEditorCanDelete(bool yes);
    void isInEditing(bool yes);

    void onEditorCopy();
    void onEditorCut();
    void onEditorPaste();
    void onEditorDelete();

public Q_SLOTS:
    /*!
     *��������View
     *@return ��
     */
    virtual void reset();

    virtual void setRootIndex(const QModelIndex &index);
    virtual void doItemsLayout();

    /*!
     *ѡ������View
     *@return ��
     */
    virtual void selectAll();

    /*!
     *������index���ӽ���༭״̬
     *@param[in]  index
     *@return ��
     */
    virtual void edit(const QModelIndex &index);

    /*!
     *�������ѡ��
     *@return ��
     */
    void clearSelection();

    /*!
     *���ø�����indexΪ����
     *@param[in]  index
     *@return ��
     */
    virtual void setCurrentIndex(const QModelIndex &index);

    void scrollToTop();
    void scrollToBottom();

    /*!
     *����index���ڸ���
     *@param[in]  index
     *@return ��
     */
    virtual void update(const QModelIndex &index);

    /**
     * @brief �ύ���ݲ��رձ༭��
     */
    bool commitDataAndCloseEditor();

    void showToolTip(const QModelIndex &index);

    void editorCopy();
    void editorCut();
    void editorPaste();
    void editorDelete();

protected Q_SLOTS:
    virtual void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());
    virtual void rowsInserted(const QModelIndex &parent, int start, int end);
    virtual void rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end);
    virtual void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    virtual void currentChanged(const QModelIndex &current, const QModelIndex &previous);
    virtual void updateEditorData();
    virtual void updateEditorGeometries();
    virtual void updateGeometries();
    virtual void verticalScrollbarAction(int action);
    virtual void horizontalScrollbarAction(int action);
    virtual void verticalScrollbarValueChanged(int value);
    virtual void horizontalScrollbarValueChanged(int value);
    virtual void closeEditor(QWidget *editor, bool &canCloseEditor, GlodonDefaultItemDelegate::EndEditHint hint);
    virtual void commitData(QWidget *editor, bool &canCloseEditor);
    virtual void editorDestroyed(QObject *editor);

    virtual void doSelectionChanged();
    virtual void doEditorCopyAvailable(bool);
    virtual void doCursorPositionChanged();
    virtual void doCursorPositionChanged(int, int);

protected:
    GlodonAbstractItemView(GlodonAbstractItemViewPrivate &dd, QWidget *parent = 0);

    void setHorizontalStepsPerItem(int steps);
    int horizontalStepsPerItem() const;
    void setVerticalStepsPerItem(int steps);
    int verticalStepsPerItem() const;

    virtual bool moveCurrent(const QModelIndex &oldIndex, const QModelIndex &newIndex,
                             QItemSelectionModel::SelectionFlags command, MoveReason moveReason);

    virtual void beforeMoveCurrent(const QModelIndex &oldIndex, const QModelIndex &newIndex,
                                   QItemSelectionModel::SelectionFlags command, MoveReason moveReason, bool &canMove);
    virtual void doMoveCurrent(const QModelIndex &oldIndex, const QModelIndex &newIndex,
                               QItemSelectionModel::SelectionFlags command, MoveReason moveReason);
    virtual void afterMoveCurrent(const QModelIndex &oldIndex, const QModelIndex &newIndex,
                                  QItemSelectionModel::SelectionFlags command, MoveReason moveReason);

    virtual QModelIndex moveCursor(CursorAction cursorAction,
                                   Qt::KeyboardModifiers modifiers) = 0;

    virtual int horizontalOffset() const = 0;
    virtual int verticalOffset() const = 0;

    virtual bool isIndexHidden(const QModelIndex &index) const = 0;

    virtual void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command) = 0;
    virtual QRegion visualRegionForSelection(const QItemSelection &selection) const = 0;
    virtual QModelIndexList selectedIndexes() const;

    virtual bool edit(const QModelIndex &index, EditTrigger trigger, QEvent *event);

    virtual QItemSelectionModel::SelectionFlags selectionCommand(const QModelIndex &index,
                                                                 const QEvent *event = 0) const;
    virtual bool isLegalData();
    virtual void setLegalData(bool value);

#ifndef QT_NO_DRAGANDDROP
    virtual void startDrag(Qt::DropActions supportedActions);
#endif

    State state() const;
    void setState(State state);

    void scheduleDelayedItemsLayout();
    void executeDelayedItemsLayout();

    void setDirtyRegion(const QRegion &region);
    void scrollDirtyRegion(int dx, int dy);

    void startAutoScroll();
    void stopAutoScroll();
    void doAutoScroll();

    bool focusNextPrevChild(bool next);
    bool event(QEvent *event);
    bool viewportEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void leaveEvent(QEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

#ifndef QT_NO_DRAGANDDROP
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);
#endif

    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);
    void timerEvent(QTimerEvent *event);
    void inputMethodEvent(QInputMethodEvent *event);

    bool inLinkCell(const QPoint &pos);

#ifndef QT_NO_DRAGANDDROP
    enum DropIndicatorPosition { OnItem, AboveItem, BelowItem, OnViewport };
    DropIndicatorPosition dropIndicatorPosition() const;
#endif

    bool setNewCurrentSelection(QKeyEvent *event, QPersistentModelIndex oNewCurrent);

    /**
     * @brief ͬ��һЩ��ǵ�Delegate����
     */
    virtual void syncStateToDelegate(GlodonDefaultItemDelegate *delegate);

    /*!
     *������Viewǰ�Ĳ���
     *@return ��
     */
    virtual void beforeReset();

    /*!
     *����View
     *@return ��
     */
    virtual void doReset();

    /*!
     *ִ��View���ú�Ĳ���
     *@return ��
     */
    virtual void afterReset();

protected:
    void doGMFirst(GLDEvent *event);
    void doGMQueryFirst(GLDEvent *event);
    void doGMPrev(GLDEvent *event);
    void doGMQueryPrev(GLDEvent *event);
    void doGMNext(GLDEvent *event);
    void doGMQueryNext(GLDEvent *event);
    void doGMLast(GLDEvent *event);
    void doGMQueryLast(GLDEvent *event);
    void doGMSetSel(GLDEvent *event);
    void doGMQuerySetSel(GLDEvent *event);
    void doGMSetColRow(GLDEvent *event);

private:
    void controlEditorNormalActions(const QModelIndex &index);
    void setEditorActSignals(QWidget *editor);
    bool connectEditorSignal(QWidget *sender, const char *name,
                             QWidget *receiver, const char *slotName);
    bool editorHasSelText(QWidget *editor);
    bool editorReadOnly(QWidget *editor);
    void resetActAvailable(QWidget *editor);
    void disableEditorActions();

    bool isComment(const QPersistentModelIndex &index);

    /**
     * @brief �������edit(Edit�ڲ����������Ŀؼ���ӡ��eventFilter������viewport)��װEventFilter
     * @param widget
     * @param delegate
     */
    void installEventFilterWidthEdit(QWidget *widget, GlodonDefaultItemDelegate *delegate);

    // mousePressEvent�ع�
    void dealWithSelectionAndAutoScroll(QModelIndex index, QMouseEvent *event);

    // KeyPressEvent�ع�
#ifdef QT_KEYPAD_NAVIGATION
    void dealWithKeyPadNavigation(QKeyEvent *event);
#endif

    QPersistentModelIndex getNewCurrentAccordingToKeyPressOperation(QKeyEvent *event);
    void scrollToNewCurrent(QKeyEvent *event, QPersistentModelIndex &oNewCurrent);
    void dealWithEventAcception(QKeyEvent *event);

    // mouseMoveEvent�ع�
    void setSelectionAndScrollToOnMouseMove(
            const QModelIndex &oCurIndex, QMouseEvent *event, const QPoint &oPrePoint, const QPoint &oCurPoint);

    // TimerEvent�ع�
    void showCurIndexToolTip();
    void doLayoutAndScroll();
    // doAutoScroll�ع�
    void scrollVerticalScrollBar(int nVerticalValue, QScrollBar *verticalScroll);
    void scrollHorizontalScrollBar(int nHorizontalValue, QScrollBar *horizontalScroll);

    // CommitEditor�ع�
    void removeNonPersistentEditor(QWidget *editor);
    void setEditorFocus(QWidget *editor);
    void dealWithEndEditHint(GlodonDefaultItemDelegate::EndEditHint hint);

    void resetEditorFocus();

    /*!
     * \brief �����ύ���ݺ͹رձ༭��,δ�ܹرձ༭��ʱ,�򽫱༭���ı�ȫ��ѡ��
     * \param canCloseEditor
     */
    void doCommitDataAndCloseEditor(bool &canCloseEditor);

    /**
     * @brief ͨ��delegate��Model��д������
     * @param[in]  pDelegate
     * @param[in]  editor
     * @param[in]  index
     * @param[in]  canCloseEditor
     */
    void setModelData(GlodonDefaultItemDelegate *pDelegate, QWidget *editor,
                      const QModelIndex & index, bool &canCloseEditor);

    /**
     * @brief �������ݵĺϷ���
     * @param[in]  pDelegate
     * @param[in]  canCloseEditor
     */
    void setLegitimacyOfData(GlodonDefaultItemDelegate *pDelegate, bool & canCloseEditor);

private Q_SLOTS:
    void _q_columnsAboutToBeRemoved(const QModelIndex &parent, int start, int end);
    void _q_columnsRemoved(const QModelIndex &index, int start, int end);
    void _q_columnsInserted(const QModelIndex &index, int start, int end);
    void _q_rowsInserted(const QModelIndex &index, int start, int end);
    void _q_rowsRemoved(const QModelIndex &index, int start, int end);
    void _q_modelDestroyed();
    void _q_layoutChanged();
    void _q_headerDataChanged();

private:
    Q_DECLARE_PRIVATE(GlodonAbstractItemView)
    Q_DISABLE_COPY(GlodonAbstractItemView)

    friend class QAccessibleItemRow;
    friend class QListModeViewBase;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(GlodonAbstractItemView::EditTriggers)

class GLDTABLEVIEWSHARED_EXPORT GAbstractItemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    friend class GlodonAbstractItemViewPrivate;
};

enum GLDScrollBarType
{
    gsbtAll = 0,
    gsbtVertical = 1,
    gsbtHorizon = 2
};

#endif // GLDABSTRACTITEMVIEW_H
