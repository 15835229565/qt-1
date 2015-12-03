/*!
 *@file glodonheaderview.h
 *@brief {��ͷ}
 *
 *@author Gaosy
 *@date 2012.9.7
 *@remarks {}
 *Copyright (c) 1998-2012 Glodon Corporation
 */

#ifndef GLDHEADERVIEW_H
#define GLDHEADERVIEW_H

#include <QBitArray>
#include <QApplication>
#include <QLabel>
#include "GLDAbstractItemView.h"

class GLDHeaderSpan;
class GLDTableView;
class GlodonTableView;
class GlodonHeaderViewPrivate;

/*!
 *@class: GlodonHeaderView
 *@brief {Ĭ�ϱ�ͷ����֧�ֵ��У���ͷ��ʾ���ݴ�model�е�headerData�л�ȡ}
 *@author Gaosy
 *@date 2012.9.10
 */
class GLDTABLEVIEWSHARED_EXPORT GlodonHeaderView : public GlodonAbstractItemView
{
    Q_OBJECT

    Q_PROPERTY(bool showSortIndicator READ isSortIndicatorShown WRITE setSortIndicatorShown)
    Q_PROPERTY(bool highlightSections READ highlightSections WRITE setHighlightSections)
    Q_PROPERTY(bool cascadingSectionResizes READ cascadingSectionResizes WRITE setCascadingSectionResizes)
    Q_PROPERTY(int defaultSectionSize READ defaultSectionSize WRITE setDefaultSectionSize)
    Q_PROPERTY(int minimumSectionSize READ minimumSectionSize WRITE setMinimumSectionSize)
    Q_PROPERTY(Qt::Alignment defaultAlignment READ defaultAlignment WRITE setDefaultAlignment)
    Q_ENUMS(ResizeMode)

public:
    /*!
     *@enum: ResizeModel
     *@brief {resize��ʽ}
     *@author Gaosy
     *@date 2012.9.11
     */
    enum ResizeMode
    {
        Interactive,
        Fixed
    };

    enum VisibleState
    {
        LUnvisibleRVisible = -1,
        LVisibleRUnvisible = 1,
        BothVisible = 2,
        BothUnvisible = 0
    };

    enum ResizeState
    {
        Press,
        Move,
        Finish
    };

public:
    /*!
     *GlodonHeaderView���췽��
     *@param[in]  orientation  ��ͷ����Qt::Horizontal��ʾˮƽ��Qt::Vertical��ʾ��ֱ
     *@param[in]  parent       ��widget
     *@return ��
     */
    explicit GlodonHeaderView(Qt::Orientation orientation, QWidget *parent = 0);
    virtual ~GlodonHeaderView();

    /*!
     *Ϊ��ͷ�ṩ������Դ
     *@param[in]  model
     *@return ��
     *@see �μ�GlodonAbstractItemView::setModel(QAbstractItemModel *model)
     */
    void setModel(QAbstractItemModel *model);

    /*!
     *���ر�ͷ�ķ���
     *@return Qt::Orientation
     */
    Qt::Orientation orientation() const;

    /*!
     *���ر�ͷ��ƫ��
     *@return int
     */
    virtual int offset() const;

    /*!
     *���ر�ͷ�ĳ���
     *@return int
     */
    virtual int length() const;

    /*!
     *����ˮƽ����ֱ����ͷ�ĸ߶ȣ���ȣ�
     *@return int
     */
    virtual int drawWidth() const;

    /*!
     *����ˮƽ����ֱ����ͷ���У��У���
     *@return int
     */
    int sectionCount() const;

    /*!
     *���ظ���sizeHint����ı�ͷ��С
     *@return QSize
     */
    QSize sizeHint() const;

    /**
     * @brief Qt5����ʵ��
     * @param v
     */
    void setVisible(bool v);

    /*!
     *����sizeHint��������У��У���ͷ�Ŀ�ȣ��߶ȣ�
     *@param[in]  logicalIndex  �߼��У��У���
     *@return int
     */
    int sectionSizeHint(int logicalIndex) const;

    /*!
     *���ݸ���������λ�ã����������У��У��ţ�������ʱ���У��У���
     *@param[in]  position  ˮƽ����ֱ����ͷ��x�ᣨy�ᣩ����
     *@return int
     */
    int visualIndexAt(int position) const;

    /*!
     *���ݸ���������λ�ã������߼��У��У��ţ���model�е��У��У���
     *@param[in]  position  ˮƽ����ֱ����ͷ��x�ᣨy�ᣩ����
     *@return int
     */
    int logicalIndexAt(int position) const;

    int logicalIndexAt(int x, int y) const
    {
        return orientation() == Qt::Horizontal ? logicalIndexAt(x) : logicalIndexAt(y);
    }

    int logicalIndexAt(const QPoint &pos) const
    {
        return logicalIndexAt(pos.x(), pos.y());
    }

    /*!
     *���ظ����У��У��Ŀ�ȣ��߶ȣ�
     *@param[in]  logicalIndex  �߼��У��У���
     *@return int
     */
    int sectionSize(int logicalIndex) const;
    /**
     * @brief ���ظ����У��У��Ŀ�ȣ��߶ȣ�
     * @param visualIndex ��ʾ�У��У���
     * @return
     */
    int visualSectionSize(int visualIndex)const;

    /*!
     *���ظ����У��У��ľ�����ʼλ��
     *@param[in]  logicalIndex  �߼��У��У���
     *@return int
     */
    int sectionPosition(int logicalIndex) const;

    /*!
     *���ظ����У��У��������ʼλ�ã���������ʼλ��
     *@param[in]  logicalIndex  �߼��У��У���
     *@return int
     */
    int sectionViewportPosition(int logicalIndex) const;

    /**
     * @brief ���ظ����У��У��������ʼλ�ã���������ʼλ��
     * @param visualIndex ��ʾ�У��У���
     * @return
     */
    int sectionVisualPosition(int visualIndex) const;

    /*!
     *��from�У��У��ƶ���to�У��У�λ��
     *@param[in]  from  ��ʼ�е������У��У���
     *@param[in]  to    Ŀ��������У��У���
     *@return ��
     */
    void moveSection(int from, int to);

    /*!
     *�������У��У���λ��
     *@param[in]  first   Ҫ�����������У��У���
     *@param[in]  second  ��һ��Ҫ�����������У��У���
     *@return ��
     */
    void swapSections(int first, int second);

    /*!
     *���������У��У����п��иߣ�
     *@param[in]  logicalIndex  �߼��У��У���
     *@param[in]  size          �µ��п��иߣ�
     *@return ��
     */
    virtual void resizeSection(int logicalIndex, int size, bool update = true, bool isManual = false);

    /**
     * @brief ����headerView��SectionSpan�Ĵ�����ʽ��Ĭ��Ϊfalse
     * @param value
     */
    void setSectionSpanSeparate(bool value);
    bool isSectionSpanSeparate();

    /*!
     *�жϸ����У��У��Ƿ�����(��ָcollapsed)
     *@param[in]  logicalIndex  �߼��У��У���
     *@return bool
     */
    bool isSectionHidden(int logicalIndex) const;

    /*!
     *�жϸ����У��У��Ƿ�ɼ��������ִ����Թ�����Ϊ������Ӵ��ڻ����Ӵ��⣩
     *@param[in]  logicalIndex  �߼��У��У���
     *@return int -1:��(��)�˲��ɼ�����(��)�˿ɼ���0�����ɼ���1:��(��)�˿ɼ�����(��)�˲��ɼ���2:˫�˿ɼ���3:Ԥ�����塣���VisibleState��ö��ֵ
     */
    inline bool isSectionVisible(const int &logicalIndex) const
    {
        return visibleState(logicalIndex) != BothUnvisible;
    }

    VisibleState visibleState(int logicalIndex) const;

    /*!
     *���أ���ʾ�������У��У�
     *@param[in]  logicalIndex  �߼��У��У���
     *@param[in]  hide          true��ʾ���أ�false��ʾ��ʾ
     *@return bool
     */
    void setSectionHidden(int logicalIndex, bool hide);

    /*!
     * \brief ������ʾ������section��ֻ����һ��recalcSectionStartPos
     * \param logicalIndexs
     * \param hide
     */
    void batchSetSectionHidden(QSet<int> logicalIndexs, bool hide);

    /*!
     *�������ص��У��У���
     *@return int
     */
    int hiddenSectionCount() const;

    /*!
     *�����У��У�
     *@param[in]  logicalIndex  �߼��У��У���
     *@return ��
     */
    void hideSection(int logicalIndex)
    {
        setSectionHidden(logicalIndex, true);
    }

    /*!
     *��ʾ�У��У�
     *@param[in]  logicalIndex  �߼��У��У���
     *@return ��
     */
    void showSection(int logicalIndex)
    {
        setSectionHidden(logicalIndex, false);
    }

    /*!
     *����ˮƽ����ֱ����ͷ���У��У���
     *@return int
     */
    virtual int count() const;

    /*!
     *���ظ����߼��У��У��������У��У��ţ������������ʱ���У��У���
     *@param[in]  logicalIndex  �߼��У��У���
     *@return int
     */
    int visualIndex(int logicalIndex) const;

    /*!
     *���ظ��������У��У����߼��У��У��ţ�����������model�ж�Ӧ���У��У���
     *@param[in]  visualIndex  �����У��У���
     *@return int
     */
    int logicalIndex(int visualIndex) const;

    void setMovable(bool movable);
    bool isMovable() const;

    void setClickable(bool clickable);
    bool isClickable() const;

    void setHighlightSections(bool highlight);
    bool highlightSections() const;

    /*!
     *���ù̶��񱳾�ɫ
     *@param[in]  index  �У��У���
     *@param[in]  value  ���ı���ɫ
     */
    void setFixedCellColor(const QColor &value, int index = -1);
    void inserFixedCellColor(const QColor &value, int index);
    void setFixedCellEvent(bool value);
    bool isFixedcellEvent() const;

    void setGridLineWidth(int value);
    void setGridLineColor(QColor value);
    void setResizeMode(ResizeMode mode);
    void setResizeMode(int logicalIndex, ResizeMode mode);
    ResizeMode resizeMode() const;
    ResizeMode resizeMode(int logicalIndex) const;

    void setSortIndicatorShown(bool show);
    bool isSortIndicatorShown() const;

    void setSortIndicator(int logicalIndex, Qt::SortOrder order);
    int sortIndicatorSection() const;
    void setSortIndicatorSection(int logicalIndex);
    Qt::SortOrder sortIndicatorOrder() const;
    void setSortIndicatorOrder(Qt::SortOrder order);

    bool cascadingSectionResizes() const;
    void setCascadingSectionResizes(bool enable);

    int defaultSectionSize() const;
    void setDefaultSectionSize(int size);

    int minimumSectionSize() const;
    void setMinimumSectionSize(int size);

    bool isTree() const;

    /*!
     *�����Ƿ���ʾ���νṹ��������ֱ��ͷ������
     *���ڻ���ʾ�����أ��ӽڵ㣬���Ի��������
     *ͬʱ���ᵼ��֮ǰ���õ��иߣ���Ч
     *@param[in]  showTree
     */
    void setIsTree(bool showTree);

    bool autoSectionData() const;

    /*!
     *�����Ƿ��Զ�����У��У���
     *@param[in]  autoData
     */
    void setAutoSectionData(bool autoData);

    int fixedCount() const;

    /*!
     *���ù̶��༭�У��У���
     *@param[in]  fixedCount
     */
    virtual void setFixedCount(int fixedCount);

    Qt::Alignment defaultAlignment() const;
    void setDefaultAlignment(Qt::Alignment alignment);

    /*!
     *���ñ�ͷ
     *@return ��
     */
    void doItemsLayout();

    /*!
     *�����Ƿ����У��У��ƶ���
     *@return bool
     */
    bool sectionsMoved() const;

    /*!
     * @brief ������ƶ�����Ϣ
     */
    void clearSectionMove();

    /*!
     *�����Ƿ����У��У�����
     *@return bool
     */
    bool sectionsHidden() const;

    /*!
     *����ָ�������sectionHandle
     *@return int
     */
    int getSectionHandleAt(int position);

    QModelIndex indexAt(const QPoint &p) const;
    bool isIndexHidden(const QModelIndex &index) const;
    bool isAllSectionHidden() const;

    void paintEvent(QPaintEvent *e);
    bool viewportEvent(QEvent *e);
    virtual void updateGeometries();
    void currentChanged(const QModelIndex &current, const QModelIndex &old);
    /**
     * @brief �����У��У����ߣ���ʱ����������λ��
     * @return
     */
    QPoint mousePosition();
    void setMousePosition(QPoint pos);

    void setResizeDelay(bool delay);

#ifndef QT_NO_DATASTREAM
    QByteArray saveState() const;
    bool restoreState(const QByteArray &state);
#endif

    /*!
     *���ñ�ͷ
     *@return ��
     *@see �μ�GlodonAbstractItemView::reset();
     */
    void reset();

    /*!
     *Ϊ����ģʽ���ñ�ͷ
     *@return ��
     *@see �μ�GlodonAbstractItemView::reset();
     */
    inline void resetForGroup()
    {
        initializeSections();
    }

    void resetAfterTreeBuild(const QVector<int> &showRows);

    /**
     * @brief ���ñ�ͷ����ʹsectionCountû�б仯
     */
    void resetSectionItems();

    /**
     * @brief �����������ӣ�����headerView�Ĵ�С
     */
    void zoomInSection(double factor);

    void setInZoomingSection(bool zooming);
    bool inZoomingSection() const;

    /**
     * @brief �����Ǳ�ͷ�ƶ��������Ƿ�д�뵽model��
     * @brief ��ʱ��Ҫ�ⲿ�ػ�canSectionMove�źŽ��д���
     */
    void setLogicalSectionMovable(bool isManual);
    bool isLogicalSectionMovable() const;

    /**
     * @brief �����Ƿ���ʾ�߿�
     * @return
     */
    bool drawBorder() const;
    void setDrawBorder(bool value);

    /**
     * @brief �����Ƿ�����˫���¼�
     * @return
     */
    bool allowDoubleClicked() const;
    void setAllowDoubleClicked(bool value);

    /**
     * @brief ѡ��ʱ�������Ƿ�Ӵ���ʾ
     * @return
     */
    bool boldWithSelected();
    void setBoldWithSelected(bool value);

    /**
    * @brief �����Ƿ���а�ɫ��Ӱ
    * @return
    */
    bool isFontShadow() const;
    void setFontShadow(bool fontShadow);

    QColor fontShadowColor() const;
    void setFontShadowColor(const QColor &clr);

    /**
     * @brief isHeaderLinearGradient �жϱ�ͷ�Ƿ���н���ɫ
     * @return
     */
    bool isHeaderLinearGradient() const;
    void setHeaderLinearGradient(bool value);

    /**
     * @brief ���������еļ�ͷ�Ƿ������ֵ��Ϸ�
     * @param bIsSortArrowOnTextUp
     */
    void setSortArrowOnTextTop(bool bIsSortArrowOnTextTop);

    void setLogicalIndexImage(QMultiHash<int, QString> logicalIndexHash, int spanTop);

    /*!
     * \brief ����reSizeSection������ֻ����������SectionItem�е�size�����ֻ����һ��recalcSectionStartPos
     * \param logicalIndexSizes keyΪsectionIndex��valueΪsize
     */
    void batchResizeSection(const QMap<int, int> &logicalIndexSizes);

public Q_SLOTS:
    virtual void setOffset(int offset);
    void setOffsetToSectionPosition(int visualSectionNumber);
    void setOffsetToLastSection();
    void headerDataChanged(Qt::Orientation orientation, int logicalFirst, int logicalLast);
    void setDrawWidth(int drawWidth);

Q_SIGNALS:
    void sectionMoved(int logicalIndex, int oldVisualIndex, int newVisualIndex);
    void sectionResized(int logicalIndex, int oldSize, int newSize, bool isManual = false);
    void sectionPressed(int logicalIndex);
    void sectionClicked(int logicalIndex);
    void sectionEntered(int logicalIndex);
    void sectionDoubleClicked(int logicalIndex);
    void sectionCountChanged(int oldCount, int newCount);
    void sectionHandleDoubleClicked(int logicalIndex);
    void sectionAutoResize(int logicalIndex, GlodonHeaderView::ResizeMode mode);

    void geometriesChanged();
    void sortIndicatorChanged(int logicalIndex, Qt::SortOrder order);
    void scrolled(int offset);
    void drawWidthChanged(int newWidth);
    void canSectionMove(int from, int to, bool &canMove);
    /**
     * @brief �����У��У���Сʱ�����ͺţ�֪ͨtableview������
     * @param mousePosition  ����λ��
     * @param direction  headview�ķ���
     * @param state  ��ǰ����ʲô״̬��mousepress,mousemove, mouserelease��
     */
    void sectionResizing(QPoint &mousePosition, Qt::Orientation direction, GlodonHeaderView::ResizeState state);

protected Q_SLOTS:
    void updateSection(int logicalIndex);
    void sectionsInserted(const QModelIndex &parent, int logicalFirst, int logicalLast);
    void sectionsAboutToBeRemoved(const QModelIndex &parent, int logicalFirst, int logicalLast);

protected:
    GlodonHeaderView(GlodonHeaderViewPrivate &dd, Qt::Orientation orientation, QWidget *parent = 0);

    void updateTargetSectionRecord(int pos);
    void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags flags);

    void scrollTo(const QModelIndex &index, ScrollHint hint);
    void scrollContentsBy(int dx, int dy);

    void rowsInserted(const QModelIndex &parent, int start, int end);

    /**
     * @brief ���������еı�ͷС����
     * @param painter
     * @param opt
     * @param widget
     */
    void paintSectionSortArrow(QPainter *painter, QStyleOptionHeader &opt, const QWidget *widget) const;

    /*!
     * @brief    ����Qt���ƺ������Ʊ�ͷsection����
     * @param    [i]painter
     * @param    [i]opt
     * @param    [i]widget
     * @return   void
     */
    void paintSectionOnQt(QPainter *painter, QStyleOptionHeader &opt, const QWidget *widget, bool bHighLight) const;
    void paintHighLightSection(QPainter *painter, QStyleOptionHeader &opt, const QRect &rect) const;
    void paintEmptySection(QPainter *painter, const QRect &rect);

    void mouseReleaseEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);

    inline bool isInValidLogicalIndex(const int &logicalIndex) const
    {
        return logicalIndex < 0 || logicalIndex >= count();
    }

    void initStyleOption(QStyleOptionHeader *option) const;
    void initializeSections(int start, int end);
    void initializeSections();
    void initialize();

    void fillFixedCell(QPainter *painter, QStyleOptionHeader &opt, QRect rect, int logicalIndex) const;
    void drawCellBorder(QPainter *painter, QStyleOptionHeader &opt) const;

    virtual void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;
    virtual void paintSection(int beginToHideIndex) const;

    virtual QSize sectionSizeFromContents(int logicalIndex) const;

    QRegion visualRegionForSelection(const QItemSelection &selection) const;

    QRect visualRect(const QModelIndex &index) const;
    QRect textRect(const QRect &rect) const;

    QModelIndex moveCursor(CursorAction, Qt::KeyboardModifiers);

    int verticalOffset() const;
    int horizontalOffset() const;

    bool event(QEvent *e);

    void drawImageInDesignatedLogicalIndex(QPainter *painter, QStyleOptionHeader &supopt) const;

private Q_SLOTS:
    void _q_sectionsRemoved(const QModelIndex &parent, int logicalFirst, int logicalLast);
    void _q_layoutAboutToBeChanged();

private:
    bool m_isSortArrowOnTextTop;

private:
    friend class GLDTableView;
    friend class GLDTableViewPrivate;
    Q_DECLARE_PRIVATE(GlodonHeaderView)
    Q_DISABLE_COPY(GlodonHeaderView)
};

struct GlodonCellAttr
{
public:
    Qt::Orientation orientation;
    QColor background;
};

class GLDTABLEVIEWSHARED_EXPORT GlodonHHeaderView : public GlodonHeaderView
{
    Q_OBJECT
public:
    explicit GlodonHHeaderView(QWidget *parent = 0);
    ~GlodonHHeaderView();

};

class GLDTABLEVIEWSHARED_EXPORT GlodonVHeaderView : public GlodonHeaderView
{
    Q_OBJECT
public:
    explicit GlodonVHeaderView(QWidget *parent = 0);
    ~GlodonVHeaderView();

};

class GLDTABLEVIEWSHARED_EXPORT GlodonHHeaderViewGraphicsEffect : public QGraphicsEffect
{
public:
    GlodonHHeaderViewGraphicsEffect(GlodonHeaderView *header)
        : QGraphicsEffect(header)
        , m_header(header)
        , m_clrStart("#A5AAB3")
        , m_clrMid("#A5AAB3")
        , m_clrEnd("#A5AAB3")
        , m_shadowHeight(3)
    {
        m_clrMid.setAlpha(40);
        m_clrEnd.setAlpha(20);
    }
    virtual void draw(QPainter *painter);

    virtual QRectF boundingRectFor(const QRectF &rect) const;

    void setStartColor(const QColor &color)
    {
        m_clrStart = color;
    }
    void setMidColor(const QColor &color)
    {
        m_clrMid = color;
    }
    void setEndColor(const QColor &color)
    {
        m_clrEnd = color;
    }

    void setShadowHeight(int height)
    {
        m_shadowHeight = height;
    }

private:
    GlodonHeaderView *m_header;
    QColor m_clrStart;
    QColor m_clrMid;
    QColor m_clrEnd;
    int    m_shadowHeight;
};

#endif // GLDHEADERVIEW_H
