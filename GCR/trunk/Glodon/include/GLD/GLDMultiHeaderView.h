/*!
 *@file glodonmultiheaderview.h
 *@brief {���ͱ�ͷ}
 *ͨ������Model�е�HeaderData���á�|���ָ�ӹ�ϵ
 *@author Gaosy
 *@date 2012.9.7
 *@remarks {remarks}
 *Copyright (c) 1998-2012 Glodon Corporation
 */

#ifndef GLDMULTIHEADERVIEW_H
#define GLDMULTIHEADERVIEW_H

#include "GLDHeaderView.h"
#include "GLDObjectList.h"

class GlodonMultiHeaderView;
class GlodonMultiHeaderViewPrivate;
class GHeaderSpanCollection;

/*!   
 *@enum: HeaderSpanRelation
 *@brief {����HeaderSpan֮���λ�ù�ϵ�����ڳ�ʼ����ͷ}
 *@author Gaosy 
 *@date 2012.9.10
 */
enum HeaderSpanRelation
{
    Contain,
    Overlapping,
    AdjacentUp,
    AdjacentDown,
    AdjacentLeft,
    AdjacentRight,
    AdjacentIrrelevant,//����,���Ǹ߶Ȼ��߿�Ȳ�һ��
    Irrelevant
};

/*!   
 *@class : HeaderSpan
 *@brief {��ͷ�ϲ��������¼��ǰ��ͷ����ʾ�����ݡ��Ƿ�ѡ�м���ͷ��Ĵ�С}
 *@author Gaosy 
 *@date 2012.9.10
 */
class GLDTABLEVIEWSHARED_EXPORT GLDHeaderSpan
{
public:
    GLDHeaderSpan()
        : m_top(-1), m_left(-1), m_bottom(-1), m_right(-1), m_section(-1), m_selected(false) {}

    GLDHeaderSpan(int row, int column, int rowCount, int columnCount, QString text, int section)
        : m_top(row), m_left(column), m_bottom(row + rowCount - 1),
          m_right(column + columnCount - 1), m_text(QString(text)),
          m_section(section), m_selected(false) {}

    inline int top() const { return m_top; }
    inline int left() const { return m_left; }
    inline int bottom() const { return m_bottom; }
    inline int right() const { return m_right; }
    inline int height() const { return m_bottom - m_top + 1; }
    inline int width() const { return m_right - m_left + 1; }

    inline void setTop(int top) { m_top = top; }
    inline void setLeft(int left) { m_left = left; }
    inline void setBottom(int bottom) { m_bottom = bottom; }
    inline void setRight(int right) { m_right = right; }

    inline QString text() const { return m_text; }
    inline void setText(QString text) { m_text = text; }
    inline int section() const { return m_section; }
    inline void setSection(int section) { m_section = section; }
    inline bool selected() const { return m_selected; }
    inline void setSelected(bool selected) { m_selected = selected; }

    /*!
     *�жϸñ�ͷ�ϲ�������һ���ϲ���֮���λ�ù�ϵ
     *@param[in]  span  ��һ����ͷ�ϲ���
     *@return HeaderSpanRelation
     */
    HeaderSpanRelation spanRelation(GLDHeaderSpan span);

private:
    int m_top;
    int m_left;
    int m_bottom;
    int m_right;
    QString m_text;
    int m_section;
    bool m_selected;
};

/*!   
 *@class: GHeaderSpanCollection
 *@brief {һ����ͷ�����б�ͷ�ϲ���ļ���}
 *@author Gaosy 
 *@date 2012.9.10
 */
class GLDTABLEVIEWSHARED_EXPORT GHeaderSpanCollection
{
public:
    GHeaderSpanCollection() {}

    ~GHeaderSpanCollection()
    {
    }

    /*!
     *���һ���ϲ��飬��Ҫ�ڳ�ʼ���ϲ���ͷ��ʱ�����
     *@param[in]  span  
     *@return ��
     */
    void addSpan(GLDHeaderSpan *span);

    /*!
     *ͨ�����кŻ�ȡ��λ�õĺϲ����ڼ����е��±�
     *@param[in]  rowIndex  �߼��кţ�model�е��кţ�
     *@param[in]  colIndex  �߼��кţ�model�е��кţ�
     *@return ��
     */
    int spanAt(int rowIndex, int colIndex) const;

public:
    //���б�ͷ�ϲ���ļ���
    GObjectList<GLDHeaderSpan *> spans;

private:
    void parseSpanInternal(int index, bool isInRecursion, int i);
    bool parseSpanRelationRecursively(GLDHeaderSpan *span, bool isInRecursion, int index);
};

/*!   
 *@class: GlodonMultiHeaderView
 *@brief {���ͱ�ͷ��ͨ������Model�е�HeaderData���á�|���ָ�ӹ�ϵ}
 *@author Gaosy 
 *@date 2012.9.10
 */
class GLDTABLEVIEWSHARED_EXPORT GlodonMultiHeaderView : public GlodonHeaderView
{
    Q_OBJECT

public:
    GlodonMultiHeaderView(Qt::Orientation orientation, QWidget *parent = 0);
    virtual ~GlodonMultiHeaderView();

    /*!
     *��������һ�У��У��Ŀ�ȣ��߶ȣ�
     *@param[in]  logicalIndex  �߼��кţ��кţ�
     *@param[in]  size          �µ��п��иߣ�
     *@return ��
     */
    void resizeSection(int logicalIndex, int size, bool update = true, bool isManual = false);

    /*!
     *Ϊ��ͷ�ṩ������Դ��ÿһ���ϲ�������ʾ������ͨ��model�е�headerData()��ȡ�����в��
     *���ݡ�|�����ָ��ӹ�ϵ���γ����νṹ��ͷ
     *                                          |_____a_____|
     *����:��һ��Ϊ��a|b�����ڶ���Ϊ��a|c����������Ч��Ϊ  |  b  |  c  |
     *  
     *@param[in]  model  �ṩ���ݵ�model
     *@return ��
     */
    void setModel(QAbstractItemModel *model);

    /*!
     *��ȡ��ǰ��ͷ�����У��У����������У��У�����1
     *@return int
     */
    int extraCount() const;

    /*!
     *��ȡˮƽ����ֱ����ͷ�ĸ߶ȣ���ȣ�
     *@return int
     */
    int drawWidth() const;

    /*!
     *ˢ�±�ͷ
     *@return ��
     @see �μ�GlodonHeaderView::updateGeometries()
     */
    void updateGeometries();

    /*!
     *GlodonMultiHeaderView�Ļ��Ʒ���
     *@param[in]  e  
     *@return ��
     */
    void paintEvent(QPaintEvent *e);

    /*!
     *��ʼ����ͷ�����ݹ̶��༭�У��У����ͷ�Ķ�Ӧ��ϵ�����Ϸ���
     *������ĳһ�����ϲ���Ĳ����Ӻϲ���Ϊ�̶��У��У��������ֲ���
     *�򷵻�false
     *@return bool
     */
    void initTitles();

    /*!
     *���ݸ���������㣬������Ӧ�ĺϲ������伯���е��±�
     *@param[in]  point  ����λ��
     *@return int
     */
    int headerSpanAt(QPoint point);

    /*!
     *���ݸ����ĺϲ����±꣬����������λ�ã�ʵ�ʻ��Ƶ�λ�ã�
     *@param[in]  index  �ϲ������伯���е��±�
     *@return HeaderSpan
     */
    GLDHeaderSpan visualSpan(int index);

    /*!
     *���ù̶��༭�У��У���������кϷ����ж�
     *������ĳһ�����ϲ���Ĳ����Ӻϲ���Ϊ�̶��У��У�
     *��һ���ֲ��ǣ��򷢳�Assert
     *@param[in]  fixedCount
     *@return ��
     */
    void setFixedCount(int fixedCount);

    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);

    /*!
     *���ݸ����ĺϲ����±꣬����������λ��
     *@param[in]  index  �ϲ������伯���е��±�
     *@return QRect
     */
    QRect headerSpanRect(int index);

    /*!
     *���ݸ����ĺϲ����±꣬ˢ�¸úϲ���
     *@param[in]  index  �ϲ������伯���е��±�
     *@return ��
     */
    void updateHeaderSpan(int index);

    /*!
     *ѡ�񣨷�ѡ���ϲ��飬���ݹ鴦���ϲ�����Ӻϲ����ѡ��״̬
     *@param[in]  index        �ϲ������伯���е��±�
     *@param[in]  select       true��ʾѡ�У�false��ʾ��ѡ��
     *@param[in]  checkParent  �Ƿ��޸ĸ��ϲ����ѡ��״̬  
     *@param[in]  checkChild   �Ƿ��޸��Ӻϲ����ѡ��״̬
     *@return ��
     */
    void selectHeaderSpan(int index, bool select, bool checkParent = true, bool checkChild = true);

    /*!
     *���ݸ�����ѡ�����򣬷��ظ�ѡ�����������
     *@param[in]  selection  ѡ������
     *@return QRegion
     */
    QRegion visualRegionForSelection(const QItemSelection &selection) const;

    /*!
     *����ѡ�е�����ͷ�ѡ��������±�ͷ��غϲ����ѡ��״̬
     *@param[in]  selected    ѡ�е�����
     *@param[in]  deselected  ��ѡ������  
     *@return ��
     */
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

    /*!
     *���ر�ͷ����
     *@return int
     */
    int rowCount() const;

    /*!
     *���ر�ͷ����
     *@return int
     */
    int colCount() const;
    /**
     * @brief ���¼��㵱ǰ��ʾ�еĶ��б�ͷ
     * @return
     */
    int resetSpan();
    /**
     * @brief ˢ��һ�У��У�������ͬ��dataSource�е����ݵ�headerData�У�
     * @param index
     * @return
     */
    void updateSpan(int index);

    /**
     * @brief �����л��кţ�����Ӧ��spanѡ��
     * @param index tableView���л���
     * @return
     */
    void setSpansSelected(int index, bool selected);

    /*!
     * \brief �������ⲿ���ú����ͷ�߶ȣ�˳��Ϊ��������
     * \param minHs�߶ȵļ���
     */
    void setMinimumHeights(QVector<int> &minHs);

public Q_SLOTS:
    /*!
     *���ù�����ƫ��
     *@param[in]  offset  
     *@return ��
     *@see �μ�GlodonHeaderView::setOffset(int offset)
     */
    void setOffset(int offset);

public:
    //Ϊ�˴ﵽˮƽ��ͷ���У���ֱ��ͷ���У���Ч�����ڲ���������GlodonHeaderView
    //��������setModel��resizeSection����ʵ��������ͬ��
    QVector<GlodonHeaderView *> headerList;

    //���кϲ���ļ���
    GHeaderSpanCollection *headerData;

    //��ǰѡ�еĺϲ����ڼ����е��±�
    int pressedHeaderSpan;

    //���ڻ�����ק����Ӱ��
    QLabel *headerSpanIndicator;

    //��ק����Ӱ������굱ǰλ�õ�ƫ��
    int headerSpanIndicatorOffset;

    //ˮƽ����ֱ����ͷ��ק����Ӱ���y����x����λ��
    int headerSpanIndicatorDrawPos;

    //����ק�ĺϲ����ڼ����е��±�
    int moveStartSpan;

Q_SIGNALS:
    void headerSpanPressed(int left, int top, int right, int bottom);

protected:
    void currentChanged(const QModelIndex &current, const QModelIndex &old);

protected Q_SLOTS:
    void updateSection(int logicalIndex);

private:
    /*!
     *��ʼ����ק����Ӱ��
     *@param[in]  position  ��ק����Ӱ�����ʼλ��
     *@return ��
     */
    void setupHeaderSpanIndicator(int position);

    /*!
     *������ק����Ӱ��
     *@param[in]  position  ��ק����Ӱ��Ҫ�ƶ�����λ��
     *@return ��
     */
    void updateHeaderSpanIndicator(int position);

    void setExtraCount(int count);

    /*!
     *ȡ�������п���и�
     *@param[in]  ��
     *@return �����п���и�
     */
    int lastDrawWidth();
    void paintSpanHeader(QPainter *painter, const QRect &rect, GLDHeaderSpan *span) const;
    bool checkLogicalTitles(int fixedCount);
    bool inTopHeaderRange(int topHeaderIndex, int index);
    bool checkCanMove(int targetLogicalIndex);
    void deselectedHeaderSpans();
    int parseSpan(int nFirstVisual, int nLastVisual, int nMaxCount);
    int maxCount();
    Q_DECLARE_PRIVATE(GlodonMultiHeaderView)

    /*!
     * \brief �ָ����´���ǰ���úõĸ߶�
     */
    void recoverMinimumHeights();

private:
    // �����洢���úõĸ߶�
    QVector<int> m_minimumHeights;
};

#endif // GLDMULTIHEADERVIEW_H
