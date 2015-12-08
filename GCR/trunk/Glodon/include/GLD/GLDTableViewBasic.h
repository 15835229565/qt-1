/*!
 *@brief {����༭�ؼ�}
 *
 *@date 2015.1.6
 *@remarks {}
 *Copyright (c) 1998-2015 Glodon Corporation
 */

#pragma once

#include <QScrollBar>
#include <QLinkedList>

#include "GLDHeaderView.h"
#include "GLDAbstractItemView.h"
#include "GLDTableCornerButton.h"
#include "GLDIntList.h"
#include "GLDList.h"
#include "GLDCustomCommentFrame.h"

class GlodonScrollBar;

struct GlodonTableViewPainterInfo;

const int c_MinColWidth            = 10;     // ��˫���Զ��������ʱ��С���
const int c_Indent                 = 10;     // ��ʶ��ι�ϵ������֮��ľ���
const int c_HalfWidth              = 5;      // �ڲ��мӼ��ŵ������ε�һ����
const int c_CheckBoxWidth          = 13;     // ��ѡ����

/*!
 *@class: GSpanCollection
 *@brief {���ڴ������кϲ�����ع���}
 *@author Gaosy
 *@date 2012.9.7
 */
class GLDTABLEVIEWSHARED_EXPORT GSpanCollection
{
public:
    struct GSpan
    {
        int m_top;
        int m_left;
        int m_bottom;
        int m_right;
        bool will_be_deleted;
        GSpan()
            : m_top(-1), m_left(-1), m_bottom(-1), m_right(-1), will_be_deleted(false) { }

        GSpan(int row, int column, int rowCount, int columnCount)
            : m_top(row), m_left(column), m_bottom(row + rowCount - 1), m_right(column + columnCount - 1),
              will_be_deleted(false) { }

        inline int top() const
        {
            return m_top;
        }
        inline int left() const
        {
            return m_left;
        }
        inline int bottom() const
        {
            return m_bottom;
        }
        inline int right() const
        {
            return m_right;
        }
        inline int height() const
        {
            return m_bottom - m_top + 1;
        }
        inline int width() const
        {
            return m_right - m_left + 1;
        }
    };

    ~GSpanCollection()
    {
        clear();
    }

    void addSpan(GSpan *span);
    void updateSpan(GSpan *span, int old_height);
    GSpan *spanAt(int x, int y) const;
    void clear();
    QList<GSpan *> spansInRect(int x, int y, int w, int h) const;

    void updateInsertedRows(int start, int end);
    void updateInsertedColumns(int start, int end);
    void updateRemovedRows(int start, int end);
    void updateRemovedColumns(int start, int end);

    typedef QLinkedList<GSpan *> SpanList;
    SpanList spans;

private:
    typedef QMap<int, GSpan *> SubIndex;
    typedef QMap<int, SubIndex> Index;
    Index m_nIndex;

    bool cleanSpanSubIndex(SubIndex &subindex, int end, bool update = false);
};

Q_DECLARE_TYPEINFO(GSpanCollection::GSpan, Q_MOVABLE_TYPE);

/**
 * @brief
 *      top<<0, bottom<<8, left<<16, right<<24
 */
union GBorderLineWidthHelper
{
    enum
    {
        top,
        bottom,
        left,
        right,
        count
    };

    int widths;
    unsigned char lineWiths[count];
};

enum TreeDecorationStyle
{
    NoDecoration,
    NormalStyle,
    NormalNoLineStyle,
    OSStyle
};

enum Margin
{
    LeftMargin,
    RightMargin,
    TopMargin,
    BottomMargin
};

enum UpdateHeaderViewType
{
    uhVertical,
    uhHorizontal,
    uhBoth
};

enum RangeFillingStyle
{
    rfsVertical,
    rfsHorizontal,
    rfsBoth
};

enum SelectBorderWidth
{
    TwoPixel = 2,
    ThreePixel = 3
};

/*!
 *@class: GlodonTableView
 *@brief {����༭�ؼ����ṩ�����ݱ༭����ʾ�ȹ��ܣ�֧�����νṹ��ʾ}
 *@author Gaosy
 *@date 2012.9.7
 */
class GLDTABLEVIEWSHARED_EXPORT GLDTableView : public GlodonAbstractItemView
{
    Q_OBJECT

    Q_PROPERTY(bool showGrid READ showGrid WRITE setShowGrid)
    Q_PROPERTY(Qt::PenStyle gridStyle READ gridStyle WRITE setGridStyle)
    Q_PROPERTY(bool sortingEnabled READ isSortingEnabled WRITE setSortingEnabled)
    Q_PROPERTY(bool wordWrap READ wordWrap WRITE setWordWrap)
    Q_PROPERTY(bool cornerButtonEnabled READ isCornerButtonEnabled WRITE setCornerButtonEnabled)
    Q_PROPERTY(int fixedRowCount READ fixedRowCount WRITE setFixedRowCount)
    Q_PROPERTY(int fixedColCount READ fixedColCount WRITE setFixedColCount)

public:
    explicit GLDTableView(QWidget *parent = 0);
    ~GLDTableView();

    /**
     * @brief ����tableView��Model
     * @param model
     */
    void setModel(QAbstractItemModel *model);

    /*����ѡ�����*/

    /**
     * @brief �Ƿ��ڱ༭״̬
     * @return
     */
    bool isEditing() const;
    /**
     * @brief �жϸ������У��ж�Ӧ�ĸ����Ƿ��ܽ���༭״̬(��ReadOnly��ͬ)
     * @param row
     * @param column
     * @return
     */
    bool cellCanGetEdit(int row, int column);

    /**
     * @brief �Ƿ���ʾ������
     * @return
     */
    virtual bool isDisplayFilter();

    /**
     * @brief �Ƿ��Ǻϼ���λ�ڱ��
     * @return
     */
    virtual bool totalRowAtFooter() const;

    /**
     * @brief �����Ƿ���������
     * @param enable
     */
    void setSortingEnabled(bool enable);
    bool isSortingEnabled() const;

    /**
     * @brief
     *      �����Զ��и�
     *
     * @details
     *      ��������п�Ϳؼ�Ĭ�ϴ�С���Զ�����������и�
     *
     * @param accordingCols �Զ������и߲ο����п����
     */
    void setSuitRowHeights(const GIntList &accordingCols);
    GIntList suitRowHeights();

    /**
     * @brief
     *      �����Զ��п�
     *
     * @details
     *      ����������е����ݺͿؼ�Ĭ�ϴ�С�Զ�����������п�
     *
     * @param suitColWidths �Զ������п����
     */
    void setSuitColWidths(const GIntList &suitColWidthCols);
    GIntList suitColWidths();

    /**
     * @brief
     *      ���ú����п�
     *
     * @details
     *      ������������е�����Զ�����������п�
     *
     * @param fitColWidths �̶��п����
     */
    void setFitColWidths(const GIntList &fitColWidthsCols);
    GIntList fitColWidths();

    /**
     * @brief �����Ƿ�������
     * @param allowCopy
     */
    void setAllowCopy(bool allowCopy);
    bool allowCopy() const;

    /**
     * @brief �����Ƿ�����ճ��
     * @param allowPaste
     */
    void setAllowPaste(bool allowPaste);
    bool allowPaste() const;

    /**
     * @brief �������Ͻ�Button�Ƿ����
     * @param enable
     */
    void setCornerButtonEnabled(bool enable);
    bool isCornerButtonEnabled() const;

    /**
     * @brief �����µĿؼ�������ǿ�������ģ�͵�����Զ��󶨣�
     * @param widget
     */
    void setCornerWidget(QWidget *widget);
    QWidget *cornerWidget() const;

    /**
     * @brief �����Ƿ�����ѡ����䣨����ѡ���⣩
     * @param enable
     */
    void setAllowRangeFilling(bool enable);
    bool allowRangeFilling() const;

    /**
     * @brief ѡ��������ʽ(ֻ����ֱ��ˮƽ�����߶�����)
     * @param style
     */
    void setRangeFillingStyle(RangeFillingStyle style);
    RangeFillingStyle rangeFillingStyle();

    /**
     * @brief �����Ƿ�������ѡ(�����ֱ��ͷ��ѡ��һ����)
     * @return
     */
    bool allowSelectRow() const;
    void setAllowSelectRow(bool value);

    /**
     * @brief �����Ƿ�������ѡ(���ˮƽ��ͷ��ѡ��һ����)
     * @return
     */
    bool allowSelectCol() const;
    void setAllowSelectCol(bool value);

    /**
     * @brief ����ѡ�����ʱ���Ƿ�ʹ��EditRole
     * @return
     */
    bool cellFillEditField() const;
    void setCellFillEditField(bool value);

    /*!
     *���ù̶��ɱ༭����
     *@param[in]  fixedColCount  �̶��ɱ༭����
     *@return ��
     */
    virtual void setFixedColCount(int fixedColCount);
    int fixedColCount() const;

    /*!
     *���ù̶��ɱ༭����
     *@param[in]  fixedRowCount  �̶��ɱ༭����
     *@return ��
     */
    void setFixedRowCount(int fixedRowCount);
    int fixedRowCount() const;

    /**
     * @brief �����Ƿ��ӳ�ˢ��
     * @param delay
     */
    void setResizeDelay(bool delay);

    /**
     * @brief �����Ƿ������ѡ��ק
     * @param value
     */
    void setAllowRangeMoving(bool value);
    bool allowRangeMoving() const;

    /*!
     *�жϸ����߼����Ƿ����أ�true��ʾ���أ�false��ʾ��ʾ
     *@param[in]  row  �߼��к�
     *@return bool
     */
    bool isRowHidden(int row) const;

    /*!
     *���ø����߼��е�����״̬
     *@param[in]  row   �߼��к�
     *@param[in]  hide  true��ʾ���أ�false��ʾ��ʾ
     *@return ��
     */
    void setRowHidden(int row, bool hide);

    /*!
     *�жϸ����߼����Ƿ����أ�true��ʾ���أ�false��ʾ��ʾ
     *@param[in]  column  �߼��к�
     *@return bool
     */
    bool isColumnHidden(int column) const;
    /*!
     *���ø����߼��е�����״̬
     *@param[in]  column   �߼��к�
     *@param[in]  hide     true��ʾ���أ�false��ʾ��ʾ
     *@return ��
     */
    void setColumnHidden(int column, bool hide);

    /*!
     *������������index��
     *@param[in]  index
     *@param[in]  hint   ������ʽ
     *@return ��
     */
    void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible);

    /*!
     *���ݸ������߼����кţ����ظø��������ϲ������������
     *@param[in]  row     �߼��к�
     *@param[in]  column  �߼��к�
     *@return int
     */
    int rowSpan(int row, int column) const;

    /*!
     *���ݸ������߼����кţ����ظø��������ϲ������������
     *@param[in]  row     �߼��к�
     *@param[in]  column  �߼��к�
     *@return int
     */
    int columnSpan(int row, int column) const;

    /*!
     * \brief ���ݾ������кţ����غϲ��������ϽǸ��ӵ�QModelIndex�����޿ɼ�����
     * \param row
     * \param column
     * \return
     */
    QModelIndex spanAt(int row, int column);

    /**
     * @brief ���ݸ�����������
     * @param column
     * @param order
     */
    void sortByColumn(int column, Qt::SortOrder order);

    /**
     * @brief ��ѡ��קʱ����ԭλ�õ������������䵽�µ�λ��
     * @param src
     * @param dest
     */
    void doRangeMoving(QRect src, QRect dest);

    /**
     * @author duanb
     * @param bCanCopyText ֪ͨ�û���ѡ�������Ƿ���Խ��и���
     * @return GString
     * ����ѡ�����ݵ����а�
     */
    GString copyTextFromSelections(bool* bCanCopyText = 0);
    bool pasteFromClipboard();

    /**
     * @brief ������ת����һ��QModelIndex��List����
     * @param rect ��Ҫת��������
     * @return
     */
    QList<QModelIndex> rangeToList(QRect rect);

    /**
     * @brief �ѽ������õ���ǰ���ڴ��ڱ༭״̬�Ŀؼ���
     */
    void resetEditorFocus();
    /**
     * @brief ˮƽ��ͷ
     * @return
     */
    GlodonHeaderView *horizontalHeader() const;
    virtual void setHorizontalHeader(GlodonHeaderView *header);

    /**
     * @brief ��ֱ��ͷ
     * @return
     */
    GlodonHeaderView *verticalHeader() const;
    void setVerticalHeader(GlodonHeaderView *header);

    /**
     * @brief ������tableView�����½���ʾһ����ʡ�Ժŵ�button
     * @param value
     */
    void setShowEllipsisButton(bool value);
    bool isShowEllipsisButton();

    /**
     * @brief ���÷Ǳ༭״̬ʱ����ʾ�༭��ʽ
     * @return
     */
    GlodonAbstractItemView::EditStyleDrawType editStyleDrawType() const;
    void setEditStyleDrawType(GlodonAbstractItemView::EditStyleDrawType drawType);

    /*������ѡ��*/
    /**
     * @brief �����Ƿ���ʾ����
     * @param show
     */
    void setShowGrid(bool show);
    bool showGrid() const;

    /*!
     * \brief �ں����ͷ���������ͷ����ʱ���Ƿ���Ʊ߿���
     * \param value
     */
    void setDrawTopAndLeftBorderLine(bool value);
    bool drawTopAndLeftBorderLine();

    /**
     * @brief ���ø�����ʽ(ʵ�ߣ����ߵ�)
     * @return
     */
    void setGridStyle(Qt::PenStyle style);
    Qt::PenStyle gridStyle() const;

    void setWordWrap(bool on);
    bool wordWrap() const;

    /**
     * @brief ����ѡ�е�Ԫ���Ӧ�ı�ͷ�Ƿ������ʾ
     * @return
     */
    void setHighlightSections(bool value);
    bool highlightSections() const;

    /**
     * @brief ���ø��߿��
     * @param value
     */
    void setGridLineWidth(int value);
    int gridLineWidth() const;

    /**
     * @brief ���ø�����ɫ
     * @param value
     */
    virtual void setGridLineColor(QColor value);
    QColor gridLineColor() const;

    /*!
     * \brief �ڱ�ͷ���أ��ҹ���ģʽΪItemʱ�����Ƶ���������ϱ߿������߿��ߵ���ɫ
     * \param value
     */
    void setFrameLineColor(QColor value);
    QColor frameLineColor() const;

    /*!
     *����ѡ������ɫ
     * \param value
     */
    void setSelectedBoundLineColor(QColor value);
    QColor selectedBoundLineColor() const;

    /*!
     *����ѡ�����߿�(Ĭ��Ϊ2)
     * \param value
     */
    void setSelectedBoundLineWidth(SelectBorderWidth lineWidth);
    int selectedBoundLineWidth() const;

    /*!
     *����ʧȥ���㣬ѡ������ɫ
     * \param value
     */
    void setNoFocusSelectedBoundLineColor(QColor value);
    QColor NoFocusSelectedBoundLineColor() const;

    /**
     * @brief �����Ƿ��д�ֱ�������
     * @param value
     */
    void setShowVerticalGridLine(bool value);
    bool showVerticalGridLine() const;

    /**
     * @brief �Ƿ���ˮƽ����ĸ���
     * @return
     */
    void setShowHorizontalGridLine(bool value);
    bool showHorizontalGridLine() const;

    /**
     * @brief ���ñ�񱳾�ɫ
     * @param value
     */
    void setGridColor(QColor value);

    /**
     * @brief ������ʾ��ǰѡ�и��ӵı���ɫ
     * @param showBackColor
     */
    void setShowCurCellBackgroundColor(bool showBackColor) { m_bShowCurCellBackgroundColor = showBackColor; }
    bool showCurCellBackgroundColor() { return m_bShowCurCellBackgroundColor; }

    /**
     * @brief �����Ƿ����Զ�����
     * @return
     */
    bool isCustomStyle() const;
    void setIsCustomStyle(bool value);

    /**
     * @brief �����ṩ������Ӣ�ӣ�����TableView
     * @param factor
     */
    void zoomTableView(double factor);

    /**
     * @brief ���ý�������ڵ��еı���ɫ����ɱ�ѡ��ʱ����ɫ
     * @param isShow
     */
    void setAlwaysShowRowSelectedBgColor(bool isShow);
    bool alwaysShowRowSelectedBgColor();

    /*!
     *�Ƿ�����ͨ����Ԫ����߸ı��и��п�,Ĭ��ֵΪfalse
     *@return ��
     */
    void setAllowResizeCellByDragGridLine(bool canResize);
    bool allowResizeCellByDragGridLine();

    /**
     * @brief ���ûس��������ֻ����enterJumpʱ�������ִ������Ϊ
     *        1�����û�н���༭��ʽ����Enter��������༭��ʽ-����Enter-���˳��༭��ʽ���ҽ����ƶ�����һ����-����Enter
     *           -������༭��ʽ
     *        2������Ѿ����ڱ༭��ʽ����Enter-���˳��༭��ʽ���ҽ����ƶ�����һ������
     * @return
     */
    bool enterJump() const;
    void setEnterJump(bool value);

    /**
     * @brief ���ü򻯰�س����񣬿���enterJump��ͬʱ����enterJumpProʱ�������ִ������Ϊ
     *        1�����û�н���༭��ʽ����Enter-������༭��ʽ-����Enter-���˳��༭��ʽ�������ƶ�����һ�����ӣ�����ʹ
     *           ��һ���ӽ���༭��ʽ-����Enter-���˳��༭��ʽ�������ƶ�����һ�����ӣ�����ʹ��һ���ӽ���༭��ʽ
     *        2������Ѿ����ڱ༭��ʽ����Enter-���˳��༭��ʽ�������ƶ�����һ�����ӣ�����ʹ��һ���ӽ���༭��ʽ
     * @return
     */
    bool enterJumpPro() const;
    void setEnterJumpPro(bool value);

    /**
     * @brief �����Ƿ�ʹ�û�ϱ���ɫ����ǰѡ�и��ӵı���ɫΪ���ӱ������ɫ�Ļ�ɫ��Ĭ��Ϊ��ɫ��
     * @return
     */
    void setUseBlendColor(bool value);
    bool useBlendColor() const;

    /**
     * @brief ����ѡ������ı�����ɫ
     * @return
     */
    void setSelectedCellBackgroundColor(QColor value);
    QColor selectedCellBackgroundColor() const;

    /*�༭���*/
    /*!
     *������index���ӽ���༭״̬
     *@param[in]  index
     *@return ��
     */
    void edit(const QModelIndex &index);

    /**
     * @brief ǿ���˳��༭״̬���밴EscЧ��һ��
     */
    void forceCloseEditor();

    /**
     * @brief �����Ƿ���ʾ�����п��и�ʱ����Ϣ��ʾ��Ĭ��ֵΪtrue
     * @param value
     */
    void setDisplayResizeInfoFrame(bool value);

    /*!
     * \brief ������ע
     * \param index
     * \param value
     */
    GCustomCommentFrame *addComment(const QModelIndex &index, QString value);

    /*!
     * \brief �༭��ע
     * \param index
     */
    GCustomCommentFrame *editComment(const QModelIndex &index);

    /*!
     * \brief ��ʾ/������ע
     * \param index
     * \param isShow
     */
    GCustomCommentFrame *showOrHideCommentPersistent(const QModelIndex &index, bool isShow = true);

    /*!
     * \brief �ñ�ע���Ƿ�����ʾ
     * \param index
     * \return
     */
    bool isShowComment(const QModelIndex &index);

    /*!
     * \brief ɾ����ע
     * \param index
     */
    void deleteComment(const QModelIndex &index);

    /*!
     * \brief ��ʾ������������ע
     * \param isShow
     */
    void showOrHideAllCommentPersistent(bool isShow = true);

    /*!
     * \brief ���ص�ǰindex����ע�����
     * \param index
     */
    const GCustomCommentFrame *findComment(const QModelIndex &index) const;

    /**
     * @brief �������б�ע���Ƿ�ˢ�¡��ýӿ���Ϊ�˱����ע���������λ��ƣ�����tableview resetʱ�и�ʧЧ��
     * ����λ��ƻ�۵����һ�Σ��ӿ����Ч�ʣ�Ҳ������tableview����ʧЧ����
     * @param enable ����Ϊ�棬���б�ע������Ϊˢ�£��������б�ע������ˢ��һ��
     */
    void setCommentsUpdatesEnabled(bool enable);

    /**
     * @brief �Ƿ�ʧȥ�����˳��༭״̬
     * @return
     */
    bool closeEditorOnFocusOut();
    /**
     * @brief �����Ƿ�ʧȥ�����˳��༭״̬
     * @param value
     * @param ignoreActiveWindowFocusReason  �Ƿ�������������������ʧȥ����
     */
    void setCloseEditorOnFocusOut(bool value, bool ignoreActiveWindowFocusReason = false);

    /*!
     * \brief �����ڴ���comboBox�༭��ʽʱ���Ƿ�ʹ���Զ���ʾ���ܣ�Ĭ��Ϊ��ʾ
     * \return
     */
    bool useComboBoxCompleter() const;
    void setUseComboBoxCompleter(bool value);

    /*ˢ�����*/

    /*!
     *�����������壬���»���
     *@return ��
     *@see �μ�GlodonAbstractItemView::doItemsLayout()
     */
    void doItemsLayout();

    /**
     * @brief ���¼����Զ��и��п������п�
     */
    virtual void refreshDisplayColRow();
    /**
     * @brief ˢ��һ������(�ڿ���������ѡ���ƶ����ܵ�ʱ�򣬺ڿ���ˢ�·�Χ֮��)
     * @param logicIndexֻ���������ƶ�ʱ��logicalIndex��visualIndex��ͬ
     */
    void updateModelIndex(const QModelIndex &logicIndex);

    virtual void update(const QModelIndex &logicalIndex);

    /**
     * @brief ˢ��һ��
     * @param col
     */
    void updateCol(int col);

    /**
     * @brief ˢ��һ��
     * @param row
     */
    void updateRow(int row);

    /**
     * @brief ˢ������tableView
     */
    void updateAll();

    /**
     * ��������
     */
    void updateHeaderView(const UpdateHeaderViewType updateType);

    /*QModelIndex���*/
    /*!
     * TODO: delete
     *@return ��
     */
    virtual QModelIndex treeIndex(const QModelIndex &index) const;

    /*!
     *TODO: delete
     *@return ��
     */
    virtual QModelIndex dataIndex(const QModelIndex &index) const;
    /*!
     *TODO: delete
     *@param[in]  pos  �����
     *@return QModelIndex
     */
    QModelIndex indexAt(const QPoint &pos) const;

    /**
     * @brief ��ʾIndexת��Ϊ�߼�Index
     * @param visualIndex
     * @return
     */
    QModelIndex logicalIndex(QModelIndex visualIndex);
    /**
     * @brief �߼�Indexת��Ϊ��ʾIndex
     * @param logicalIndex
     * @return
     */
    QModelIndex visualIndex(const QModelIndex &logicalIndex);

    /*!
     *�������б�ѡ�е�QModelIndex
     *@return QModelIndexList
     */
    QModelIndexList selectedIndexes() const;

    /**
     * @brief ����һ�����к��к���ɵ�rect������һ��dataIndex����
     * @param rect
     * @return
     */
    QModelIndexList indexesFromRect(QRect rect, int &rowCount, int &columnCount);

    /*����λ�����*/
    /*!
     *���ݸ������߼��кţ����������λ��
     *@param[in]  row  �߼��к�
     *@return int
     */
    int rowViewportPosition(int row) const;

    /**
     * @brief ���ݸ�������ʾ�кţ����������λ�ã���ȥ�˹�����ƫ�ƣ�
     * @param visualRow ��ʾ�к�
     * @return
     */
    int rowVisualPosition(int visualRow) const;

    /*!
     *���ݸ���y���꣬���ظ�λ�õ��߼��к�
     *@param[in]  y  y��������
     *@return int
     */
    int rowAt(int y) const;
    /**
     * @brief ���ݸ�����y���꣬���ظ�λ�õ���ʾ�к�
     * @param y
     * @return
     */
    int visualRowAt(int y) const;

    /*!
     *�����и�
     *@param[in]  row     �߼��к�
     *@param[in]  height  ���и�
     *@param[in]  isManual  �Ƿ��Զ��壬Ӱ���Ƿ�д��Model
     *@return ��
     */
    void setRowHeight(int row, int height, bool isManual = true);

    /*!
     *���ݸ����߼��кţ������и�
     *@param[in]  row  �߼��к�
     *@return int
     */
    int rowHeight(int row) const;

    /**
     * @brief ���ݸ�����ʾ�кţ������и�
     * @param visualRow ��ʾ�к�
     * @return
     */
    int visualRowHeight(int visualRow) const;

    /*!
     *���ݸ������߼��кţ����������λ��
     *@param[in]  column  �߼��к�
     *@return int
     */
    int columnViewportPosition(int column) const;

    /**
     * @brief ���ݸ�������ʾ�кţ����������λ�ã���ȥ�˹�����ƫ�ƣ�
     * @param visualColumn ��ʾ�к�
     * @return
     */
    int columnVisualPosition(int visualColumn) const;

    /*!
     *���ݸ���x���꣬���ظ�λ�õ��߼��к�
     *@param[in]  x  x��������
     *@return int
     */
    int columnAt(int x) const;

    /**
     * @brief ���ݸ���x���꣬���ظ�λ�õ���ʾ�к�
     * @param x
     * @return
     */
    int visualColumnAt(int x) const;

    /*!
     *�����п�
     *@param[in]  column  �߼��к�
     *@param[in]  width   ���п�
     *@return ��
     */
    void setColumnWidth(int column, int width);

    /*!
     *���ݸ����߼��кţ������п�
     *@param[in]  column  �߼��к�
     *@return int
     */
    int columnWidth(int column) const;

    /**
     * @brief ���ݸ�����ʾ�кţ������п�
     * @param visualColumn ��ʾ�к�
     * @return
     */
    int visualColumnWidth(int visualColumn) const;

    /*!
     *���ظ���logicIndex�Ļ���λ��
     *@param[in]  index
     *@return QRect
     */
    QRect visualRect(const QModelIndex &index) const;

    /**
     * @brief ������ʾ������ɵ�Rect��������Ƶ�λ��
     * @param rowColNo
     * @return
     */
    QRect visualRectForRowColNo(const QRect &rowColNo);

    /*!
     *����QItemselectionModel�����ڼ�¼��ǰ��ѡ������
     *@param[in]  selectionModel
     *@return ��
     *@see �μ�GlodonAbstractItemView::setSelectionModel(QItemSelectionModel *selectionModel)
     */
    void setSelectionModel(QItemSelectionModel *selectionModel);

    /*!
     *��ӡ���ܣ���δʵ��
     *@return ��
     */
    void print();

    /*!
     * \brief ���ø����Ƿ�ֶλ��ƣ��ر��⹦�ܣ�����߻���Ч��
     * \param drawBoundLine
     */
    void setDrawBoundLine(bool drawBoundLine);
    bool drawBoundLine();

public Q_SLOTS:
    /*!
     *ѡ��һ��
     *@param[in]  row  �߼��к�
     *@return ��
     */
    void selectRow(int row);

    /*!
     *ѡ��һ��
     *@param[in]  column  �߼��к�
     *@return ��
     */
    void selectColumn(int column);

    /*!
     *����һ��
     *@param[in]  row  �߼��к�
     *@return ��
     */
    virtual void hideRow(int row);

    /*!
     *����һ��
     *@param[in]  column  �߼��к�
     *@return ��
     */
    void hideColumn(int column);

    /*!
     *��ʾһ��
     *@param[in]  row  �߼��к�
     *@return ��
     */
    void showRow(int row);

    /*!
     *��ʾһ��
     *@param[in]  column  �߼��к�
     *@return ��
     */
    void showColumn(int column);

    /*!
     *�������߼���resize���ʺ����ݵĸ߶�
     *@param[in]  row  �߼��к�
     *@return ��
     */
    void resizeRowToContents(int row);

    /*!
     * \brief ���ݸ������ݼ��������е��иߣ���Ӧ��
     */
    void resizeRowsToContents();

    /*!
     *�������߼���resize���ʺ����ݵĸ߶�
     *@param[in]  column  �߼��к�
     *@return ��
     */
    void resizeColumnToContents(int column);

    /*!
     * \brief ���ݸ������ݼ��������е��п���Ӧ��
     */
    void resizeColumnsToContents();

    /*!
     *�����е��иߵ��������ʸ߶�
     *@param[in]  calcAllColumns  �Ƿ����������н��м���
     *@return ��
     */
    void setSuitRowHeightForAll(bool value, bool calcAllColumns = false);

    /*!
     *�����е��п���������ʿ��
     *@param[in]  calcAllRows  �Ƿ����������н��м���
     *@return ��
     */
    void setSuitColWidthForAll(bool value, bool calcAllRows = false);

    void sortByColumn(int column);

    /*!
     *ѡ���������߼���
     *@param[in]  start  �߼��к�
     *@param[in]  end    �߼��к�
     *@return ��
     */
    void selectColumns(int start, int end);

    /*!
     *ѡ���������߼���
     *@param[in]  start  �߼��к�
     *@param[in]  end    �߼��к�
     *@return ��
     */
    void selectRows(int start, int end);
    void setCurrentIndex(const QModelIndex &dataIndex);
    /**
     * @brief ͨ���кţ��кţ����ý���񣬸��кţ��к�Ϊ�����к��кţ�û�и��ӽṹ
     * @param row
     * @param column
     */
    void setCurrentIndex(int row, int column);
    void onScrolled(int offset);

protected slots:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());
    void onHeaderDataChanged(Qt::Orientation orientation, int, int);

    void closeEditor(QWidget *editor, bool &canCloseEditor, GlodonDefaultItemDelegate::EndEditHint hint);
    void commitData(QWidget *editor, bool &canCloseEditor);

    void canRowMoved(int from, int to, bool &canMove);
    void rowMoved(int row, int oldIndex, int newIndex);
    void canColumnMoved(int from, int to, bool &canMove);
    void columnMoved(int column, int oldIndex, int newIndex);
    void rowResized(int row, int oldHeight, int newHeight, bool isManual);
    /**
     * @brief ColumnHeaderView������Сʱ������øòۣ�������filterTableView,footTableView,GSPTableView
     *        ʱ�����ȵ�������ĵ�����С������Ȼ����ø÷����������ͱ��������Զ��п������п����filterTableView
     *        ��С�������Ե����
     * @param column
     * @param oldWidth
     * @param newWidth
     */
    virtual void columnResized(int column, int oldWidth, int newWidth, bool isManual = false);
    void rowCountChanged(int oldCount, int newCount);
    void columnCountChanged(int oldCount, int newCount);

    /**
     * @brief �����У��У���Сʱ�����㵱ǰ�У��У������Ĵ�С�����һ���ʾ�򣨺�����paint�����У�
     * @param mousePostion ����λ��
     * @param direction  headerview�ķ���
     * @param state ��ǰ������״̬(mousePress, mouseMove, mouseRelease)
     */
    virtual void showSectionResizingInfoFrame(const QPoint &mousePosition, Qt::Orientation direction, GlodonHeaderView::ResizeState state);

Q_SIGNALS:
    void rangeFill(QRect src, QRect dest, bool &handled);
    void rangeFill(QModelIndexList src, QModelIndexList dest, int rowCount, int ColumnCount, bool &handled);

    void expanded(int index);
    void collapsed(int index);

    void onEllipsisButtonClick();

    //for��ҳ���
    void columnNewWidths(GIntList *newWidths);
    void enableFitColWidths(bool enable);

protected:
    GLDTableView(GLDTableViewPrivate &, QWidget *parent);

    virtual void doSetModel(QAbstractItemModel *model);
    virtual bool canRangeFill(const QRect &rect);
    bool doCanRangeFill(const QRect &rect);

    void scrollContentsBy(int dx, int dy);
    bool isEditorInFixedColAfterHScroll();
    bool isEditorInFixedRowAfterVScroll();

    QStyleOptionViewItem viewOptions() const;

    /*!
     *����TableView�и��������Ĳ���
     *@return ��
     */
    void updateGeometries();

    void paintEvent(QPaintEvent *e);
    void timerEvent(QTimerEvent *event);

    virtual void onBoolCellPress(QMouseEvent *event);
    virtual void onMousePress(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

    bool viewportEvent(QEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);
    void leaveEvent(QEvent *event);
    void wheelEvent(QWheelEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void showEvent(QShowEvent *event);

    int horizontalOffset() const;
    int verticalOffset() const;
    QModelIndex moveCursor(GlodonAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers);

    void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command);
    /**
     * @brief ����ʵ��ѡ�����������selection(ʵ��ѡ���������߼�ѡ���������������ƶ�ʱ������)
     * @param visualTL ʵ��ѡ�������topLeftModelIndex
     * @param visualBR ʵ��ѡ�������bottomRightModelIndex
     * @param command
     */
    void setSelectionByIndex(
            const QModelIndex &visualTL, const QModelIndex &visualBR,
            QItemSelectionModel::SelectionFlags command);

    QRegion visualRegionForSelection(const QItemSelection &selection) const;
    QRegion visualRegionForSelectionWithSelectionBounding(const QItemSelection &selection) const;
    int sizeHintForRow(int row) const;
    int sizeHintForColumn(int column) const;

    int calcSuitHeight(const QList<int> &oNeedCalcHeightCols, int nLogicalRow);
    int calcSuitWidth(int nLogicalCol);

    void verticalScrollbarAction(int action);
    void horizontalScrollbarAction(int action);

    bool isIndexHidden(const QModelIndex &index) const;

    bool inBoolCell(const QPoint pos) const;

    void selectionChanged(const QItemSelection &selected,
                          const QItemSelection &deselected);
    void currentChanged(const QModelIndex &current,
                        const QModelIndex &previous);

    bool isLegalData();
    void setLegalData(bool value);

    bool event(QEvent *event);

    /*!
     * \brief ��ȡ��һ���ɼ��У����й̶���ʱ����ȡ���ǵ�һ���ǹ̶�����Ŀɼ���
     * \return
     */
    int firstVisualRow() const;
    int lastVisualRow() const;

    /*!
     * \brief ��ȡ��һ���ɼ��У����й̶���ʱ����ȡ���ǵ�һ���ǹ̶�����Ŀɼ���
     * \return
     */
    int firstVisualCol() const;
    int lastVisualCol() const;

    GIntList needCalcSuitRowHeightColsInViewport();

    /**
     * @brief ��ȡ�����Rect���Ͻǵ�ModelIndex
     * @param rowColRect
     * @return
     */
    QModelIndex topLeftIndex(const QRect &rowColRect) const;
    /**
     * @brief ��ȡ�����Rect�����½ǵ�ModelIndex
     * @param rowColRect
     * @return
     */
    QModelIndex bottomRightIndex(const QRect &rowColRect) const;

    void bindMergeCell();

    virtual void rebuildGridRows(const GLDList<QModelIndex> &arrRows);

    /*!
     * TODO: delete
     * \return Ϊ����ʾ���εĸ��ӵ������������е�ˮƽ�����ƫ��(��Ҫ�����ɵ�ϸ�ߺ�branchͼ��ռȥ�Ŀ��)
     */
    virtual int treeCellDisplayHorizontalOffset(int row, int col, bool isOldMinTextHeightCalWay = true) const;
    void doMoveCurrent(const QModelIndex &oldIndex, const QModelIndex &newIndex,
                       QItemSelectionModel::SelectionFlags command, MoveReason moveReason);

    virtual QAbstractItemModel* itemModel()
    {
        return model();
    }

    inline int currentGridLineWidth() const;
    inline QPen currentGridPen();

    bool edit(const QModelIndex &index, EditTrigger trigger, QEvent *event);
    void syncStateToDelegate(GlodonDefaultItemDelegate *delegate);

    void beforeReset();
    void doReset();
    void afterReset();

    /**
     * @brief ��������ʱ���������(src����dest������ModelIndex��ɣ��Ҷ��ǽ�����ʾ��λ�ã���д�÷�����ʵ���Լ�������߼�
     *                          ʱ����Ҫ����ʾ��λ�ø�Ϊ�߼�λ��)
     * @param src ԭѡ������
     * @param dest ����Ŀ������
     */
    virtual void doRangeFill();

    /*!
     *@brief ��������Ļ���
     *@param[in]  painter     ����
     *@param[in]  drawRegion  ��������
     *@return ��
     */
    void paint(QPainter &painter, const QRegion &drawRegion);

protected:
    virtual void afterCurrentChanged(const QModelIndex &current, const QModelIndex &previous);
    virtual void afterExpandedChanged(int index, bool expand, bool emitSignal);
    virtual void afterManualChangedRowHeight(int index, int rowHeight);
    virtual void afterManualChangedColWidth(int index, int colWidth);

protected:
    QRect m_oRangeSrc;
    QRect m_oRangeDest;
    QRect m_tempRangeRect;//������ʱ�洢ѡ���ƶ�ʱ���������Rect
    QRect m_preTempRangeRect;//������ʱ�洢ѡ���ƶ�ʱ��֮ǰ��Rect
    int m_nRangeCurRow;
    int m_nRangeCurCol;
    QRect m_dirtyArea;
    bool m_bShowCurCellBackgroundColor; //�Ƿ���ʾѡ�������е�ǰ��Ԫ��ı���ɫ

protected:
    void drawCellBorderLine(
            QPainter &painter, const QRect &cellRect, const QRegion &spans,
            int gridLineWidth, int borderLineWidth, const QVariant &borderLineColor, Qt::Orientation direction);

    void drawCellBorderLine(
            QPainter &painter, const QLine& line, bool needDraw);

    virtual void drawCellBorderLine(
            QPainter &painter, const QRect &cellRect, const QRegion &spans,
            const QModelIndex &index);

    /**
     * @brief ����EllipsisButton��λ��
     */
    virtual void resetEllipsisButtonLocation();

    /**
     * @brief
     *      ���ˮƽ�ʹ�ֱ��ͷ���ɼ�������Ҫ�ڱ����ϱߺ���߻��ƿ���.

       @details
            ����ֻ��Ҫ�ڹ�����صĺ���������ʱ�����������߼���

     * @param painter
     */
    virtual void drawTopAndLeftBorderLine(QPainter &painter);

    void drawEachRow(QPainter &painter, QRegion &spans, const QRect &params);
    void drawEachColumn(QPainter &painter, QRegion &spans, const QRect &params);

    /**
     * @brief ����boolֵ��model��
     * @param currIndex
     */
    void setBoolEditValue(QModelIndex &currIndex);

protected:
    // �ع�updateGeometries
    void updateVerticalHeaderGeometry(int nVerticalHeaderWidth);
    void updateHorizontalHeaderGeometry(int nHorizontalHeaderHeight);
    void updateConrnerWidgetGeometry(int nVerticalHeaderWidth, int nHorizontalHeaderHeight);
    void updateHorizontalScrollBar(const QSize &oViewportSize);
    void updateVerticalScrollBar(const QSize &oViewportSize);
    int colCountBackwardsInViewPort(const QSize &oViewportSize);
    int rowCountBackwardsInViewPort(const QSize &oViewportSize);

private:
    int lastVisualRowInDirtyArea(const GlodonHeaderView *verticalHeader) const;
    void adjustCurrentDirtyArea(uint verticalBottom, uint horizontalRight);
    void adjustColumnByLayoutDirection(int &firstVisualColumn, int &lastVisualColumn);
    void drawGridCellFromRowToColumn(QPainter &painter, GlodonTableViewPainterInfo &info, QBitArray &drawn, QStyleOptionViewItem &option);
    void calcTopRowAndAlternateBase(int bottom, int &top, bool &balternateBase);

private:
    /**
     * @brief ���Ƹ��ָ��ӱ߿�
     * @param painter
     * @param params
     * @param spans
     * @param option
     */
    void drawCellBorderLines(QPainter &painter, const QRect &params, QRegion &spans, QStyleOptionViewItem &option);

    /**
     * @brief ���л��Ʊ߿���
     * @param painter
     * @param params
     * @param spans
     * @param option
     */
    void drawBorderLinesByRow(QPainter &painter, const QRect &params, QRegion &spans, QStyleOptionViewItem &option);

    /**
     * @brief ���л��Ʊ߿���
     * @param painter
     * @param params
     * @param spans
     * @param option
     */
    void drawBorderLinesByCol(QPainter &painter, const QRect &params, QRegion &spans, QStyleOptionViewItem &option, int row);

    /**
     * @brief ���ݵ�ǰ״̬����ѡ���
     * @param painter
     * @param offset
     */
    void drawSelectionBorderLines(QPainter &painter, const QPoint &offset);

    /**
     * @brief ��������״̬����ѡ����䣬��ѡ���ƶ����£�ѡ������ı߿���
     * @param painter
     */
    void drawSelectionBorderLines(QPainter &painter);

    void drawGridLines(QPainter &painter, const QRect &params, QRegion &spans);

    //���ڵ�����Ԫ�����½ǵĵ�Ԫ���index
    QModelIndex calculationRightBottomIndex(QModelIndex drawIndex);

    int firstVisableColumn();
    int firstVisableRow();

    void adjustCommonBorder(const QLine &line, QList<QLine> &rectVisablelBorders);
    void adjustCommonBorder(const QLine &lineTopOfCell, QList<QLine> &rectVisablelBorders,
                            const QLine& adjustedLineTopOfCell);
    void adjustCommonBorder(const QRect &rect, QList<QLine> &rectVisablelBorders);

    void appendHideCellBorder(const QRect &rect, QList<QLine> &rectHideBorder);

    /*!
     *@brief ��������߿�
     *@param[in]  painter
     *@param[in]  offset  ƫ�Ƶ�
     *@return ��
     */
    void drawRangeFillingState(QPainter &painter, const QPoint &offset);

    /**
     * @brief ��ѡ����קʱ������קʱ��ɫʵ�߿�
     * @param painter
     * @param offset
     */
    void drawRangeMovingState(QPainter &painter);

    QRect initRangeFillingDest();
    /**
     * @brief �ж�Point�Ƿ��ڿ��������ƶ��ķ�Χ
     * @param p
     * @return
     */
    bool inRangeMovingRegion(const QPoint &p);

    /**
     * @brief ��ʼ��ѡ����קʱ��Ŀ��λrangeDest��ֵ
     * @return ����ֵΪfalse��˵�����ںϲ����Ҳ������Ϸ�������ִ�б��β����ĺ�������
     */
    bool initRangeMovingDest();

    /**
     * @brief ��ȡ��ǰѡ������ľ��δ�С
     * @return  ModelIndex��ϳɵ�Rect
     */
    QRect visualRectForSelection();
    void initRangeAction();
    /**
     * @brief ����ѡ���ƶ�ʱ������
     * @return
     */
    QRect calcRangeMovingRegion();
    /**
     * @brief ѡ����䣬ѡ���ƶ�ʱ������CurrentRow��CurrentColumn
     * @param pos
     */
    void setCurRangeRowAndCol(QPoint pos);
    //void doRangeFill();
    void addNewRow(int newRowCount);
    /**
     * @brief �����У��У���Сʱ��������ʾ���е���Ϣ
     * @param mousePosition
     * @return
     */
    QString resizeInfoText(QPoint mousePosition, Qt::Orientation);
    /**
     * @brief ����headerview�������õ����У��У���Сʱ����ʼ�߶ȣ���ȣ�
     */
    void setResizeStartPosition(Qt::Orientation);

    /**
     * @brief �����Զ��п�
     * @param col
     */
    void setGridDisplayColWidths();

    void refreshDisplayRows(GLDList<QModelIndex> &arrRows);
    void refreshDisplayRows();

    /**
     * @brief �����Զ��и�
     * @param cols ��Ҫ������Զ��иߵ���
     */
    void setGridDisplayRowHeights();

    int getSuitRowHeight(int row);

    /**
     * @brief ��������п�
     * @param col
     */
    void adjustColWidths(int currentResizeCol);

    /**
     * @brief ͨ��ö������Margin,��ȡtop,left,right,bottom��margin
     * @param modelIndex
     * @param margin
     * @return
     */
    int cellMargin(const QModelIndex &modelIndex, Margin margin) const;

    GCustomCommentFrame *findOrCreateCommentFrame(const QModelIndex &index, bool createCommentIfNotFind = true);

    /**
     * @brief ��ȡ�ұ߻��ߵױ��߿�
     * @param boundLine
     * @param isRightBoundLine �Ƿ����ұ�
     * @param compareWithGridLine �Ƿ�����߱Ƚ�
     * @return
     */
    int borderLineWidth(const QVariant &boundLine, bool isRightBoundLine) const;

    int borderLineSubtractGridLineWidth(const QVariant &boundLine, bool isRightBoundLine) const;

    /*!
    *@brief ������������index��
    *@param[in]  index
    *@param[in]  hint   ������ʽ
    *@param[in]  cellHeight ��Ԫ��ĸ߶�
    *@return ��
    */
    void scrollVerticalTo(const QModelIndex &index, ScrollHint &hint, int nCellHeight);

    /*!
    *@brief ����������������ӹ�����������ָ����Index��
    *@param[in]  index
    *@param[in]  hint   ������ʽ
    *@param[in]  cellHeight ��Ԫ��Ŀ��
    *@return ��
    */
    void scrollVerticalPerItemTo(const QModelIndex &index, ScrollHint &hint, int nCellHeight);

    /*!
    *@brief ����������������ع�����������ָ����Index��
    *@param[in]  index
    *@param[in]  hint   ������ʽ
    *@param[in]  cellHeight ��Ԫ��Ŀ��
    *@return ��
    */
    void scrollVerticalPerPixelTo(const QModelIndex &index, ScrollHint &hint, int nCellWidth);

    /*!
    *@brief ������������index��
    *@param[in]  index
    *@param[in]  hint   ������ʽ
    *@param[in]  cellWidth ��Ԫ��Ŀ��
    *@return ��
    */
    void scrollHorizontalTo(const QModelIndex &index, ScrollHint &hint, int nCellWidth);

    /*!
    *@brief ����������������ӹ�����������ָ����Index��
    *@param[in]  index
    *@param[in]  hint   ������ʽ
    *@param[in]  cellWidth ��Ԫ��Ŀ��
    *@return ��
    */
    void scrollHorizontalPerItemTo(const QModelIndex &index, ScrollHint &hint, int nCellWidth);

    /*!
    *@brief ����������������ع�����������ָ����Index��
    *@param[in]  index
    *@param[in]  hint   ������ʽ
    *@param[in]  cellWidth ��Ԫ��Ŀ��
    *@return ��
    */
    void scrollHorizontalPerPixelTo(const QModelIndex &index, ScrollHint &hint, int nCellWidth);

    /**
     * @brief �ж�ѡ�������ܷ���и���
     * @param[in]  indexList
     */
    bool checkSelectionCopyEnable(const QModelIndexList& indexList) const;

    /**
     * @brief ��һ�������QModelIndexList�л�ȡ���е�Ԫ�������
     * @param indexList
     * @return
     */
    GString getContentsFromOrderedIndexList(const QModelIndexList & indexList);

    /**
     * @brief ���ݼ���������������䵥Ԫ��
     * @param[in]   indexList       �����ĵ�Ԫ��QModelIndex
     * @param[in]   sClipBoardText  ������������
     * @param[out]  nPasteRowCount  �������
     * @param[out]  nPasteColCount  �������
     */
    void fillCellsOnClipBoardText(const QModelIndexList &indexList, GString &sClipBoardText,
                                  int & nPasteRowCount, int & nPasteColCount);

    /**
    * @brief ����ѡ������
    * @param[in]   indexList       �����ĵ�Ԫ��QModelIndex
    * @param[in]   nPasteRowCount  ճ������
    * @param[in]   nPasteColCount  ճ������
    */
    void setNewSelection(const QModelIndexList &indexList, int & nPasteRowCount, int & nPasteColCount);

    /**
     * @brief ����Ԫ����ֵ,��ֵ��������Ҫ���ǵ�Ԫ���ֻ��������,�ú�����Ҫ����pasteFromClipboard()������
     * @param index    QModelIndex
     * @param variant  ��Ҫ�趨��ֵ
     */
    void setCellData(const QModelIndex &index, const QVariant &variant);

    /*!
     * \brief ���ظ���logicIndex�Ļ���λ�ã����а����߿���
     * \param index
     * \return
     */
    QRect visualRectIncludeBoundingLineWidth(const QModelIndex &index) const;

    // MoveCursor�ع�
    int getBottomVisibleRow();
    int getRightVisibleCol();
    int getLastVisualRow(int nBottom);
    int getLastVisualCol(int nRight);

    QModelIndex leftTopVisualIndex(int nRight, int nBottom);

    void updateVisualCursor();
    void adjustRightToLeftCursorAction(CursorAction cursorAction);

    void dealWithMoveUp(int &nLastVisualRow, int &nLastVisualCol);
    void dealWithMoveDown(int &nLastVisualRow, int &nLastVisualCol, int nBottom);

    QModelIndex getLeftPageCursorIndex();
    void dealWithMoveLeft(int &nLastVisualRow, int &nLastVisualCol, int nRight, int nBottom, CursorAction cursorAction);

    QModelIndex getRightPageCursorIndex(int nRight);
    void dealWithMoveRight(int &nLastVisualRow, int &nLastVisualCol, int nRight, int nBottom, CursorAction cursorAction);

    void dealWithMoveHome(int &nLastVisualRow, int &nLastVisualCol, int nRight, int nBottom, Qt::KeyboardModifiers modifiers);
    void dealWithMoveEnd(int &nLastVisualRow, int &nLastVisualCol, int nRight, int nBottom, Qt::KeyboardModifiers modifiers);

    QModelIndex getUpPageCursorIndex();
    QModelIndex getDownPageCursorIndex(int nBottom);

    QModelIndex getCursorIndex(int nLastVisualRow, int nLastVisualCol);

    bool copyOrPastOperation(QKeyEvent *event);
    bool openEditOrScrollContent(QKeyEvent *event);
    void dealWithKeyEnterPress(QKeyEvent *event);

    void clickEditorButtonAccordingToEditStyleDrawType(QModelIndex index, QMouseEvent *event);
    void processEnterJumpAfterCloseEdit(GlodonDefaultItemDelegate::EndEditHint hint);
    void resetEnterJumpPreState();

    /**
     *@brief �Ƿ���Ҫ��ʾ�༭��ʽ�Ļ���
     *@param[in]  testIndex  ������modelIndex
     *@return true:��Ҫ false:����Ҫ
     */
    bool shouldDoEditorDraw(const QModelIndex &testIndex) const;

    // ScrollTo�ع�
    int firstVisualIndexAfterHorizontalScroll(const QModelIndex &index, ScrollHint &hint, int nCellWidth);
    int getHorizontalHiddenSectionCountBeforeIndex(int nHorizontalIndex);

    bool isPositionAtTopForRowExchange(int nVerticalPosition, int nVerticalOffset);
    int firstVisualIndexAfterVerticalScroll(const QModelIndex &index, ScrollHint &hint, int nCellHeight);
    int getVerticalHiddenSectionCountBeforeIndex(int nVerticalIndex);

    /*!
    *���úϲ���
    *@param[in]  row         �ϲ������Ͻ��߼��к�
    *@param[in]  column      �ϲ������Ͻ��߼��к�
    *@param[in]  rowSpan     �ϲ�����������������úϲ������������ĸ�����
    *@param[in]  columnSpan  �ϲ�����������������úϲ���ĺ�������ĸ�����
    *@return ��
    */
    void setSpan(int row, int column, int rowSpan, int columnSpan);

    /*!
     *������кϲ�
     *@return ��
     */
    void clearSpans();

    /**
     * @brief �˺�����Ҫ�޸��ڿ���ʧȥ�����˳��༭״̬ʱ,����onCommitEditor�ź������ӵĲ���
     *        ����canCloseEditor����Ϊfalse,���������Զ�����������
     */
    void processScrollBarAfterCanNotCloseEditor();

private:
    // �ع�ScrollContentsBy
    void scrollHorizontalContentsBy(int dx);
    void scrollVerticalContentsBy(int dy);
    void updateFirstLine(int dx, int dy);

    bool commitDataAndCloseEditorInIngnoreFocusOut();

    // �ع�MousePressEvent
    void dealWithSpecialMousePressOperations(const QModelIndex &index, QMouseEvent *event);
    void dealWithResizeCellWhenPressGridLine(QMouseEvent *event);
    bool shouldDoRangeFill(QMouseEvent *event);
    bool shouldDoRangeMove(QMouseEvent *event);
    bool shoudDoResizeCellByDragGridLine(QMouseEvent *event);

    // �ع�MouseMoveEvent
    bool shouldSetRangeFillMouseShape(const QPoint &pos);
    void setRangeFillMouseShape(bool bHasCursor);
    void getRangeFillingCurRowAndCol(int nOldRow, int nOldColumn, const QPoint &pos);
    bool shouldSetRangeMoveMouseShape(const QPoint &pos);
    void setRangeMoveMouseShape(bool bHasCursor);
    void updateTempRangeRect();
    bool shouldSetResizeCellByDragGridLineMouseShape(QMouseEvent *event);
    void setResizeCellByDragGridLineMouseShape(QMouseEvent *event);
    void dealWithResizeCellWhenDragGridLine(QMouseEvent *event);
    void recoverCursor();
    void dealWithCurCommet(const QPoint &pos);
    void dealWithRangeFillingOnMouseMove(bool bHasCursor, const QPoint &pos);
    void dealWithRangeMovingOnMouseMove(const QPoint &pos);
    bool isInRangeFilling();
    bool isInRangeMoving();
    bool isInResizingCellByDragGridLine(QMouseEvent *event);
    void updateRangeFillingRect(int nOldRow, int nOldColumn);

    // �ع�mouseReleaseEvent
    void completeRangeFilling();
    void completeRangeMoving();
    void completeResizeCellByDragGridLine(QMouseEvent *event);
    void initRangeValuesAndUpdateViewport();

    // �ع�doRangeFill
    bool doRangeFillHandled();
    void doRangeFillToTop();
    void doRangeFillToBottom();
    void doRangeFillToLeft();
    void doRangeFillToRight();
    void setSrcIndexDataToDestIndex(const QModelIndex &oSrcLogicalIndex, QModelIndex &oDestLogicalIndex);

    // �ع�SectionResizing
    void initSectionResizingInfoFrame(const QPoint &mousePostion, Qt::Orientation direction);
    void updateSectionResizingInfoFrameText(Qt::Orientation direction);

    // �ع�bindMergeCell
    void adjustVisualRect(int &nFirstVisualRow, int &nFirstVisualCol, int &nLastVisualRow, int &nLastVisualCol);
    void adjustVisualRow(int &nFirstVisualRow, int &nLastVisualRow) const;
    void adjustVisualCol(int &nFirstVisualCol, int &nLastVisualCol) const;

    void calcAndSetSpan(const int nFirstVisualRow, const int nLastVisualRow, const int nFirstVisualCol, const int nLastVisualCol);
    void initMergeCellState(const int nFirstVisualRow, const int nLastVisualRow, const int nFirstVisualCol, const int nLastVisualCol,
            QVector<QBitArray> &oCellMergeState);
    int findLastSpanRow(
            const int nCurMergeID, const int nRow, const int nLastVisualRow, const int nCurLogicalCol);
    int findLastSpanCol(const int nCurMergeID, const int nCol, const int nLastVisualCol, const int nCurLogicalRow);
    void setMergeCellState(int nRow, int nSpanRow, int nCol, int nSpanCol, QVector<QBitArray> &oCellMergeState);

    void initResizeInfoFrames(Qt::Orientation direction);

private Q_SLOTS:
    void _q_selectRow(int row);
    void _q_selectColumn(int column);
    void _q_selectRows(int left, int top, int right, int bottom);
    void _q_selectColumns(int left, int top, int right, int bottom);
    void _q_updateSpanInsertedRows(const QModelIndex &parent, int start, int end);
    void _q_updateSpanInsertedColumns(const QModelIndex &parent, int start, int end);
    void _q_updateSpanRemovedRows(const QModelIndex &parent, int start, int end);
    void _q_updateSpanRemovedColumns(const QModelIndex &parent, int start, int end);

    void writeComment(const QString &value);
    void onDrawComment(const QModelIndex &index, bool &canShow);
protected Q_SLOTS:
    void resetCommentPosition(bool isMove = false, int dx = 0, int dy = 0);
private:
    Q_DECLARE_PRIVATE(GLDTableView)
    Q_DISABLE_COPY(GLDTableView)

private:
    friend class GlodonTableViewToExcel;
    friend class GlodonDefaultItemDelegate;
};

class GlodonScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    explicit GlodonScrollBar(QWidget *parent=0);
    explicit GlodonScrollBar(Qt::Orientation orientation, QWidget *parent=0);

protected:
    void enterEvent(QEvent *event);

private:
    QWidget *m_pParent;
};

