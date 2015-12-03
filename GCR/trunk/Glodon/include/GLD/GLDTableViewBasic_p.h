#pragma once

#include "GLDAbstractItemView_p.h"
#include "GLDTableViewBasic.h"

class QPushButton;

enum RangeFillHandlePositon
{
    LeftBottom,
    RightBottom,
    RightTop
};

/*!
 *@GLDTableViewPrivate
 *@brief { GLDTableView ��Ӧ�ġ�˽���ࡱ�����������⹫��}
 *@author Gaosy
 *@date 2012.9.7
 */
class GLDTABLEVIEWSHARED_EXPORT GLDTableViewPrivate : public GlodonAbstractItemViewPrivate
{
    Q_DECLARE_PUBLIC(GLDTableView)
public:
    GLDTableViewPrivate() :
        m_allowCopy(false),
        m_allowPaste(false),
        m_allowRangeFilling(false),
        m_allowSelectCol(true),
        m_allowSelectRow(true),
        m_allowToResizeCellByDragGridLine(false),
        m_alwaysShowRowSelectedColor(false),
        m_bRangeMoving(false),
        m_cellFillEditField(true),
        m_bDrawTopAndLeftBorderLine(false),
        m_geometryRecursionBlock(false),
        m_bShowHorizontalGridLine(true),
        m_bIsInAdjustFitCols(false),
        m_inCommitData(false),
        m_bIsCustomStyle(false),
        m_isShowResizeInfoFrame(true),
        m_legalData(true),
        m_showEllipsisButton(false),
        m_showGrid(true),
        m_sortingEnabled(false),
        m_bShowVerticalGridLine(true),
        m_columnResizeTimerID(0),
        m_columnSectionAnchor(-1),
        m_currResizeWidth(0),
        m_nCurrentResizeCol(-1),
        m_nFixedColCount(0),
        m_nFixedRowCount(0),
        m_nFixedColWidth(0),
        m_nFixedRowHeight(0),
        m_gridLineWidth(1),
        m_nResizeCellStartPosition(0),
        m_nResizeCellEndPosition(0),
        m_rowResizeTimerID(0),
        m_rowSectionAnchor(-1),
        m_infoFrame(NULL),
        m_pResizeInfoLineFrame(NULL),
        m_bAllRowsResizeToContents(false),
        m_bCalcAllColumns(false),
        m_bAllColumnsResizeToContents(false),
        m_bCalcAllRows(false),
        m_horizontalHeader(NULL),
        m_verticalHeader(NULL),
        m_ellipsisButton(NULL),
        m_cornerWidget(NULL),
        m_visualCursor(QPoint()),
        m_gridStyle(Qt::SolidLine),
        m_borderLineColor(QColor(192,192,192)),
        m_gridLineColor(QColor(192,192,192)),
        m_oFrameLineColor(QColor(192,192,192)),
        m_selectBoundLineColor(QColor("#39a9d1")),
        m_selectBoundLineWidth(2),
        m_oNoFocusSelectedBoundLineColor(QColor(Qt::darkGray)),
        m_rangeFillingStyle(rfsVertical),
        m_bDrawBoundLine(false),
        m_prevState(GlodonAbstractItemView::FirstFocus),
        m_bEnterJump(true),
        m_bEnterJumpPro(false),
        m_editStyleDrawType(GlodonAbstractItemView::SdtNone),
        m_pCommentFrame(NULL),
        m_bCloseEditorOnFocusOut(false),
        m_bUseBlendColor(false),
        m_oSelectedCellBackgroundColor("#f9f9f9"),
        m_bUseComboBoxCompleter(true),
        m_bIsInReset(false),
        m_rangeFillHandlePositon(RightBottom)
    {
        m_bWrapItemText = true;
#ifndef QT_NO_DRAGANDDROP
        m_bDragDropOverwrite = true;
#endif
    }

    ~GLDTableViewPrivate();

    void init();

    void trimHiddenSelections(QItemSelectionRange *range) const;

    int sectionSpanEndLogical(const GlodonHeaderView *header, int logical, int span) const;
    int sectionSpanSize(const GlodonHeaderView *header, int logical, int span) const;
    bool spanContainsSection(const GlodonHeaderView *header, int logical, int spanLogical, int span) const;

    /*!
     *�������кϲ��񣬲�����������������Ϊ�ѻ���
     *@param[in]  area               ����TableView�Ļ�������
     *@param[in]  painter
     *@param[in]  option
     *@param[in]  drawn              ��¼�ѻ������������
     *@param[in]  firstVisualRow     ��һ���ɼ��е������к�
     *@param[in]  lastVisualRow      ���һ���ɼ��е������к�
     *@param[in]  firstVisualColumn  ��һ���ɼ��е������к�
     *@param[in]  lastVisualColumn   ���һ���ɼ��е������к�
     *@return ��
     */
    virtual void drawAndClipSpans(const QRegion &area, QPainter *painter,
                          const QStyleOptionViewItem &option, QBitArray *drawn,
                          int firstVisualRow, int lastVisualRow, int firstVisualColumn, int lastVisualColumn);

    /*!
     *���Ƹ���
     *@param[in]  painter
     *@param[in]  option
     *@param[in]  index    �����Ƹ��Ӷ�Ӧ��model�е�QModelIndex
     *@return ��
     */
    virtual void drawCell(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index);

    void setSpan(int row, int column, int rowSpan, int columnSpan);
    GSpanCollection::GSpan span(int row, int column) const;
    QRect visualSpanRect(const GSpanCollection::GSpan &span) const;
    QRect visualSpanRectIncludeBoundingLineWidth(const GSpanCollection::GSpan &span) const;

    QRect visualRectIncludeBoundingLineWidth(const QModelIndex &index) const;

    void spanTopRowLeftColumn(const GSpanCollection::GSpan &span, int &row, int &column) const;

    QRect viewportScrollArea(Qt::Orientation orientation);

    void _q_selectRow(int row);
    void _q_selectColumn(int column);
    void _q_selectRows(int left, int top, int right, int bottom);
    void _q_selectColumns(int left, int top, int right, int bottom);

    void selectRow(int row, bool anchor);
    void selectColumn(int column, bool anchor);
    bool selectColumns(int start, int end, bool anchor);
    bool selectRows(int start, int end, bool anchor);

    void _q_updateSpanInsertedRows(const QModelIndex &parent, int start, int end);
    void _q_updateSpanInsertedColumns(const QModelIndex &parent, int start, int end);
    void _q_updateSpanRemovedRows(const QModelIndex &parent, int start, int end);
    void _q_updateSpanRemovedColumns(const QModelIndex &parent, int start, int end);

    void drawTriangles(QRect rect, QPainter *painter);

public: // Inline
    inline bool isHidden(int row, int col) const
    {
        return m_verticalHeader->isSectionHidden(row)
               || m_horizontalHeader->isSectionHidden(col);
    }
    inline int visualRow(int logicalRow) const
    {
        return m_verticalHeader->visualIndex(logicalRow);
    }
    inline int visualColumn(int logicalCol) const
    {
        return m_horizontalHeader->visualIndex(logicalCol);
    }
    inline int logicalRow(int visualRow) const
    {
        return m_verticalHeader->logicalIndex(visualRow);
    }
    inline int logicalColumn(int visualCol) const
    {
        return m_horizontalHeader->logicalIndex(visualCol);
    }
    inline int accessibleTable2Index(const QModelIndex &index) const
    {
        return (index.row() + (m_horizontalHeader ? 1 : 0)) * (index.model()->columnCount() + (m_verticalHeader ? 1 : 0))
               + index.column() + (m_verticalHeader ? 1 : 0) + 1;
    }
    inline int rowSpan(int row, int column) const
    {
        return span(row, column).height();
    }
    inline int columnSpan(int row, int column) const
    {
        return span(row, column).width();
    }
    inline bool hasSpans() const
    {
        return !m_spans.spans.isEmpty();
    }
    inline int rowSpanHeight(int row, int span) const
    {
        return sectionSpanSize(m_verticalHeader, row, span);
    }
    inline int columnSpanWidth(int column, int span) const
    {
        return sectionSpanSize(m_horizontalHeader, column, span);
    }
    inline int rowSpanEndLogical(int row, int span) const
    {
        return sectionSpanEndLogical(m_verticalHeader, row, span);
    }
    inline int columnSpanEndLogical(int column, int span) const
    {
        return sectionSpanEndLogical(m_horizontalHeader, column, span);
    }
    inline bool isRowHidden(int row) const
    {
        return m_verticalHeader->isSectionHidden(row);
    }
    inline bool isColumnHidden(int column) const
    {
        return m_horizontalHeader->isSectionHidden(column);
    }
    inline bool isCellEnabled(int row, int column) const
    {
        return isIndexEnabled(m_model->index(row, column, m_root));
    }
    inline bool isCellEnabledAndSelectabled(int row, int column) const
    {
        return (isIndexEnabled(m_model->index(row, column, m_root)) && isIndexSelectable(m_model->index(row, column, m_root)));
    }
    inline bool isVisualRowHiddenOrDisabled(int row, int column) const
    {
        int nRow = logicalRow(row);
        int nCol = logicalColumn(column);

        return isRowHidden(nRow) || !isCellEnabled(nRow, nCol);
    }
    inline bool isVisualColumnHiddenOrDisabled(int row, int column) const
    {
        int nRow = logicalRow(row);
        int nCol = logicalColumn(column);

        return isColumnHidden(nCol) || !isCellEnabled(nRow, nCol);
    }
    inline bool isVisibleColumn(int column) const
    {
        int nCol = logicalColumn(column);

        return (hbar != NULL) ? m_horizontalHeader->isSectionVisible(nCol) : true;
    }
    inline bool isVisibleRow(int row)const
    {
        int nRow = logicalRow(row);

        return (vbar != NULL) ? m_verticalHeader->isSectionVisible(nRow) : true;
    }

public: // bool
    bool m_allowCopy;                   //�Ƿ�������
    bool m_allowPaste;                  //�Ƿ�����ճ��
    bool m_allowRangeFilling;           //�Ƿ������������
    bool m_allowSelectCol;              //�Ƿ�������ѡ
    bool m_allowSelectRow;              //�Ƿ�������ѡ
    bool m_allowToResizeCellByDragGridLine;               //�Ƿ�����ı��С
    bool m_alwaysShowRowSelectedColor;  //�Ƿ�������ʾ��ǰ�����������ѡ�񱳾�ɫ
    bool m_bRangeMoving;                //�Ƿ������ѡ����ק
    bool m_cellFillEditField;           //�Ƿ��������༭�ֶ�
    bool m_bDrawTopAndLeftBorderLine;               //�Ƿ�����ޱ�ͷʱ�����/�����
    bool m_geometryRecursionBlock;
    bool m_bShowHorizontalGridLine;                    //�Ƿ���ʾˮƽ����
    bool m_bIsInAdjustFitCols;             //�Ƿ��ڼ�������п��ʾ������ֹ���ó���һ�еĺ����п�󣬳���ѭ�����ã�ջ���
    bool m_inCommitData;                //��onCommitEditor�е������Ұ�Tabel����Enter��ʱ����QItemDelegate��EventFilter��,����ַ�������commit��closeEdit�ź����󣨰���һ�Σ�ʧȥ����һ�Σ����øñ�������
    bool m_bIsCustomStyle;               //�Ƿ����Զ���������GSFѡ�������ɫ����ȡ��̶��񱳾�ɫ����񱳾�ɫ
    bool m_isShowResizeInfoFrame;       //�Ƿ���ʾ�����и��п����Ϣ��
    bool m_legalData;                   //�Ƿ��ǺϷ����ݣ�details: ��commitDataʧ��ʱ��Ϊfalse��������closeEditor
    bool m_showEllipsisButton;          //�Ƿ���ʾ�����㰴ť��tableView�����½�
    bool m_showGrid;                    //�Ƿ���ʾ����
    bool m_sortingEnabled;              //�Ƿ�֧������
    bool m_bShowVerticalGridLine;                    //�Ƿ���ʾ��ֱ����

public: // int
    int m_columnResizeTimerID;
    int m_columnSectionAnchor;
    int m_currResizeWidth;
    int m_nCurrentResizeCol;
    int m_nFixedColCount;            //�̶�����
    int m_nFixedRowCount;            //�̶�����
    mutable int m_nFixedColWidth;           // �洢�ɱ༭�̶��п�ȣ������̶���֮����߿�����һ���ߵ��߿�
    mutable int m_nFixedRowHeight;          // �洢�ɱ༭�̶��и߶ȣ�ͬ��
    int m_gridLineWidth;            //���߿��
    int m_nResizeCellStartPosition;
    int m_nResizeCellEndPosition;
    int m_rowResizeTimerID;
    int m_rowSectionAnchor;

public: // pointer
    GInfoFrame *m_infoFrame;
    QFrame *m_pResizeInfoLineFrame;

    GIntList m_oFitColWidthCols;
    GIntList m_oSuitColWidthCols;  // ��ż����Զ��п��ʱ����Ҫ�ο����к�
    GIntList m_oSuitRowHeightAccordingCols; // ��ż����Զ��иߵ�ʱ����Ҫ�ο����к�

    bool m_bAllRowsResizeToContents;
    bool m_bCalcAllColumns;

    bool m_bAllColumnsResizeToContents;
    bool m_bCalcAllRows;

    GlodonHeaderView *m_horizontalHeader;
    GlodonHeaderView *m_verticalHeader;

    QPushButton *m_ellipsisButton;

    QWidget *m_cornerWidget;

public: // type
    GSpanCollection m_spans;

    QMap<QPersistentModelIndex, GCustomCommentFrame *> m_oCommentFrames;
    QPoint m_visualCursor;      // (Row,column) cell coordinates to track through span navigation.

    Qt::PenStyle m_gridStyle;

    QColor m_borderLineColor;    //������ɫ
    QColor m_gridLineColor;     //������ɫ
    QColor m_oFrameLineColor;   // �ڱ�ͷ���أ��ҹ���ģʽΪItemʱ�����Ƶ���������ϱ߿������߿��ߵ���ɫ

    QColor m_selectBoundLineColor;  //ѡ��ĵĵ�Ԫ�񣬻��ƵĿ�����ɫ
    int m_selectBoundLineWidth;     //ѡ��ĵĵ�Ԫ�񣬻��ƵĿ��߿��
    QColor m_oNoFocusSelectedBoundLineColor;                          // ʧȥ����ʱ��ѡ��ĵĵ�Ԫ�񣬻��ƵĿ�����ɫ

    QList<int> m_columnsToUpdate;
    QList<int> m_rowsToUpdate;

    RangeFillingStyle m_rangeFillingStyle;

    QHash<QModelIndex, QVariant> m_borderLines; // ���ڻ������ʱ�ı߿���ֵ
    bool m_bDrawBoundLine; // ���߷ֶλ���
    QRect m_oRangeFillHandleRect; // ����ѡ�����ʱ�����½Ǿ��εĴ�С

    QModelIndex m_oTopLeftSelectIndex; // �����span�����У����ƶ�֮��selectionModel����洢��ItemRangeΪ����������ô˻����ѡ��һ������ʱ��TopLeft
    QModelIndex m_oBottomRightSelectIndex; // �����ѡ��һ������ʱ��BottomRight
    GlodonAbstractItemView::EnterMovingState m_prevState;
    bool m_bEnterJump; //�س�����
    bool m_bEnterJumpPro; //�����س�������ٿ���������������ý����һ�������ڱ༭״̬ʱ�������һ���ܱ༭����ֱ�ӽ�����һ���ı༭״̬��
    GlodonAbstractItemView::EditStyleDrawType m_editStyleDrawType;

    GCommentFrame *m_pCommentFrame;
    bool m_bCloseEditorOnFocusOut;
    bool m_bUseBlendColor; //ʹ�û��ɫ
    QColor m_oSelectedCellBackgroundColor; //ѡ������ı�����ɫ
    bool m_bUseComboBoxCompleter;//�����Ƿ�ʹ��comboBox�Զ���ʾ����

    bool m_bIsInReset; // ��ֹ��ע����resetʱ����һ���ƶ�����ӣ���������ע�����GSPTableView��reset�ָ�rowHeight����ʱ�ٿ���ȥ��

    RangeFillHandlePositon m_rangeFillHandlePositon;

    void mergeOriginColsWidthAndAdjustColsWidth(GIntList &colWidths, const GIntList &originColsWidth, const GIntList &adjustColsWidth);
protected:
    virtual void doSelect(const QModelIndex& tl, const QModelIndex& br, QItemSelectionModel::SelectionFlags command, bool isRowSelect);
    virtual void itemDelegatePaint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index);

private:
    // duanb cuidc ע��С����
    void drawTriangles(QPainter *painter, const QStyleOptionViewItem &opt, const QModelIndex &index);

    /**
     * @brief ���ݴ������ʽ�͵�ǰ�������������µĻ�����ʽ
     * @param option ��ǰ��ʽ
     * @param index
     * @param opt  ����ʽ
     */
    void adjustStyleOption(QStyleOptionViewItem &opt, const QModelIndex &index);

    bool nothingToDraw();
    bool currentCellDrawn(GlodonTableViewPainterInfo &info, int nVisualCol, QBitArray &drawn, int nColumnCount, int nVisualRow);
    bool isCoverByFixedRow(int row, int rowYEndPos, bool addGridLineWidth);
    bool isCoverByFixedColumn(int column, int columnXEndPos, bool addGridLineWidth);
    void setOptionFeaturesAlternateProperty(bool bAlternateBase, bool balternate, QStyleOptionViewItem &option);
    QRect cellPainterRect(QRect srcRect, int visualRow, int visualCol);

    void calculateFixedRegion();
    void calculateFixedColumnWidth() const;
    void calculateFixedRowHeight() const;

    void setOptionSelectedState(QStyleOptionViewItem& opt, const QModelIndex &index);
    void setOptionMouseOverState(const QModelIndex &index, QStyleOptionViewItem& opt);
    void setOptionEnabledState(QStyleOptionViewItem& opt, const QModelIndex &index);
    void setOptionHasFocusState(const QModelIndex &index, QStyleOptionViewItem& opt);

    QItemSelection getItemSelectionAccordingToSelectState();
    void adjustSelectionBoundingRectAccordingToFixedColumn(const QRegion &bordingRegion, QRect &srcRect);
    void adjustSelectionBoundingRectAccordingToFixedRow(const QRegion &bordingRegion, QRect &srcRect);
    void drawNormalSelectionBoundingLine(QPainter &painter, QRect rect);
    void drawBorderWithFillHandle(QPainter &painter, QRect rect);

    QList<GSpanCollection::GSpan *> getVisibleSpansAccordingToIsSectionMove(int firstVisualRow, int firstVisualColumn, int lastVisualRow, int lastVisualColumn);
    void adjustOptionAlternateFeature(QStyleOptionViewItem &opt, bool bAlternateBase);

    bool isRangeFillingHandleSelected(const QPoint &p);
    bool isInMutiSelect() const;
    inline bool isEnterJump() { return m_bEnterJump && !m_bEnterJumpPro; }
    inline bool isEnterJumpPro() { return m_bEnterJump && m_bEnterJumpPro; }

    void drawComment(const QPersistentModelIndex &index);
    void hideCommentFrame();

    void setGridLineWidthToHorizontalHeader(int gridLineWidth);
    void setGridLineWidthToVertialHeader(int gridLineWidth);

    // �ع��Զ��и�
    int heightHintForIndex(const QModelIndex &index, int nHint, QStyleOptionViewItem &option) const;
    int calcSizeHintForRow(int row, const QList<int> &oNeedCalcSizeHintCols) const;
    int widthHintForIndex(const QModelIndex &index, int hint, const QStyleOptionViewItem &option) const;
    int widthHintForIndex(int visualRow, int column, int hint, const QStyleOptionViewItem &option) const;

    int sizeHintForColumn(int column, bool calcAllRows) const;

    void calcFixedColSuitWidth(bool &shouldResetCommentPosition);
    void calcNormalColSuitWidth(bool &shouldResetCommentPosition);

    void calcFixedRowSuitHeight(const QList<int> &oNeedCalcHeightCols, bool &shouldResetCommentPosition);
    void calcNormalRowSuitHeight(const QList<int> &oNeedCalcHeightCols, bool &shouldResetCommentPosition);

    int calcSuitWidth(int nCol, bool calcAllRows = false);
    int calcSuitHeight(const QList<int> &oNeedCalcHeightCols, int nLogicalRow);

    void adjustRectWidthByTreeColumn(const QModelIndex &index, QRect &rect) const;
    void adjustRectWidthBySpan(const QModelIndex &index, QRect &rect) const;

    QColor getPenColor();
    bool isNearHorizontalGridLine(QMouseEvent *event);
    bool isNearVerticalGridLine(QMouseEvent *event);

    // �ع������п�
    void doAdjustColWidths(int currentResizeCol);
    void adjustFitColWidths(GIntList &originColWidths);
    void applyAdjustFitColsWidth(const GIntList &originColsWidth, const GIntList &adjustColsWidth);
    GIntList getAdjustedColWidths(const GIntList &originColWidths, int currentResizeColWidth);

    /*!
     * \brief �����ǰ�������п�����Ǻ����п���У��͵���origineCols�е�ֵ
     * \param adjustedColWidths
     * \param currentResizeColIndexInFitCols
     * \param currentResizeCol
     * \param currentResizeColWidth
     * \param originColWidths
     */
    void adjustOriginColWidthWhenResizeColIsInFitCols(const GIntList &adjustedColWidths, int currentResizeColIndexInFitCols,
            int currentResizeColWidth, GIntList &originColWidths);
    void calcOldAdjustColsTotalWidth(const GIntList &oAdjustedColsWidth,
            int &nOldAdjustColsTotalWidth, int &nCurrentResizeColIndexInFitCols);
    void calcAdjustColsWidth(const int nAvailableAdjustWidth, const int nOldAdjustColsTotalWidth, GIntList &oAdjustedColsWidth,
            int &nNewAdjustColsTotalWidth);

    int getTotalColWidth(const GIntList &originColsWidth, int nColWidth);
    GIntList getOriginColWidthsFromView();

    int getMinTotalColWidth(const GIntList &originColWidths, const int nOriginTotalColWidth);
    int getDefaultColWidth(int col);

    bool isVisibleIndex(const QModelIndex &visualIndex);
    int defaultRowHeight(const QModelIndex &logicalIndex);

    bool isInTableView(QMouseEvent *event);
    QPoint calcResizeInfoLineFramePosition(Qt::Orientation direction);

    void fillSuitColWidthCols();
    void fillSuitRowHeightCols();
};
