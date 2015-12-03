#ifndef GLDNETSCAPESPLITTER_H
#define GLDNETSCAPESPLITTER_H

#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QStyleOption>
#include <QPixmapCache>

#include "GLDSplitter.h"
#include "GLDGlobal.h"
#include "GLDNetScapeSplitterHandle.h"

enum ArrowDirection
{
    leftToRight,
    rightToleft,
    TopToBottom,
    bottomToTop,
    inValidDirection
};

class GLDWIDGETSHARED_EXPORT GLDNestScapSplitterTripleHelper
{
public:
    GLDNestScapSplitterTripleHelper(QPoint &mid, int radius, int direction) :
        m_midPoint(mid), m_radius(radius), m_direction(direction) {}

public:
    QPoint vertexA() const;//���ֶ���
    QPoint vertexB() const;//ֱ�ǵ�
    QPoint vertexC() const;//���ֶ���

private:
    QPoint m_midPoint;
    double m_radius;
    int m_direction;
};

/*!
 * \brief The GLDNetScapeSplitterButton class �����������ǵ�button�������͵����Ϣ��splitter
 */
class GLDWIDGETSHARED_EXPORT GLDNetScapeSplitterButton : public QPushButton
{
    Q_OBJECT
public:
    explicit GLDNetScapeSplitterButton(Qt::Orientation o, QWidget *parent) :
        QPushButton(parent),
        m_arrowDirection(o == Qt::Horizontal ? leftToRight : TopToBottom),
        m_qssFileName(),
        m_orientation(o) {}

public:
    void setArrowDirection(int direction)
    {
        m_arrowDirection = direction;
        setButtonNameByArrowDirection();
        loadStyleSheet(m_qssFileName);
    }
    void setQssFileName(const QString &fileName)
    {
        m_qssFileName = fileName;
    }
    void setButtonNameByArrowDirection();
    void setButtonObjectName()
    {
        setButtonNameByArrowDirection();
    }

    virtual void loadStyleSheet(const QString &fileName)
    {
        G_UNUSED(fileName);
    }

protected:
    bool hitButton(const QPoint &pos) const;
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *e);
protected:
    /*!
     * \brief m_arrowDirection 0:left,1:right,2:top,3:bottom
     */
    int m_arrowDirection;

private:
    QString m_qssFileName;
    Qt::Orientation m_orientation;
private:
    friend class GLDNetScapeSplitterHandle;
};

/*!
 * \brief The GLDNetScapeSplitter ͨ�������setHandleWidth���÷ָ������
 * \note �ֽ�֧������child,Ҳ����˵���childʱ�Ĳ���ص�index��Ϊ����QSplitter���������δ�����
 */
class GLDWIDGETSHARED_EXPORT GLDNetScapeSplitter : public GLDSplitter
{
    Q_OBJECT
public:
    enum SplitterAlign
    {
        alLeftBottom,       //����/������(����splitter��orientation��ϳ�һ���ض��ķ���)
        alRightTop          //����/������(����splitter��orientation��ϳ�һ���ض��ķ���)
    };

public:
    explicit GLDNetScapeSplitter(QWidget *parent = 0);
    explicit GLDNetScapeSplitter(Qt::Orientation original, QWidget *parent = 0);
    explicit GLDNetScapeSplitter(bool initCollapse, QWidget *parent = 0);
    explicit GLDNetScapeSplitter(Qt::Orientation original, bool initCollapse, QWidget *parent = 0);

public:
    inline SplitterAlign alignment() const
    {
        return m_align;
    }

    inline void setAlignment(SplitterAlign align)
    {
        m_align = align;
        //TODO
    }

    int indexOffsetForCollapse()
    {
        return m_align == alLeftBottom ? 0 : 1;
    }

    /*!
     * \brief hiddenLength ����ʱ�Ŀ��
     */
    inline int hiddenLength() const
    {
        return m_minHideLength;
    }

    /*!
     * \brief hiddenLength ����ʱ�Ŀ��
     * \note ������ʾ����õļ��輴��Ч����ʱ��TODO״̬
     */
    inline void setHiddenLength(int value)
    {
        m_minHideLength = value;
    }

    /*!
     * \brief setCompletlyCollpased ����ͨ��Qt::Orientation��SplitterAlignȷ���������һ���ڳ�ʼ��ʱ�Ǳ���ȫ����
     * ���ң�ͨ�����buttonҲ���ڸ�����չ���������ȫ���������л���(���������ȵ�����)
     * \param collpased
     * \warning ��Ҫ��setHiddenLengthͬʱ���ã����ر����Է�0�Ĳ������������δ�����
     * \note ����һ������δ��ʾǰ���ò���Ч�ķ���
     * \deprecated
     */
    void setCompletlyCollpased()
    {
        //    if (!m_bInitShow) return;
        //    m_bInitCollapse = true;
    }

    /*!
     * \brief setCompletlyCollpasedEnabled ����ȷ������һ�ߵ���ȫ���ء���Ϊ��ǰ��չ��״̬���Լ���ǰ�Ǵ��������ȵ�����״̬��
     * �����л�Ϊ������Ϊ0������״̬�����Ὣ��������Ϊ0�������Ѵ��ڿ��Ϊ0������״̬���򲻻����κζ�����
     * \note �����Ƿ������ȫ������Ϊfalse��������ʱ�Ŀ�Ƚ���Ϊ֮ǰ���õ�����ʱ���(����������Ĭ��)����Ϊtrue��������ʱ�Ŀ�Ƚ���Ϊ0
     */
    void setCollpaseCompletable(bool enabled = true);

    /*!
     * \brief setCollpaseSideStretchFactor ����ͨ��Qt::Orientation��SplitterAlignȷ���������һ�ߵĳ�ʼ�� չ���ߴ磬����ͨ��
     *�϶�handle�󣬵��button�������ص��ַ��ı� չ���ߴ磬Ҳ����˵�˷���ֻ�ڳ�ʼʱ��Ч��������֤move handle��� չ���ߴ�
     * \param rate �����ص���һ�ߵ� չ���ߴ� �����spliter�Ŀ�ȵı��ʣ���������(0, 1)֮�䣬����ʵ�ʵĳߴ�������1���أ��������
     *Ĭ��ֵ
     * \retval true:���óɹ� false:����ʧ��
     * \warning �벻Ҫ��ͼ���û���� setStretchFactor()���� �����δ�����
     * \note ����һ������δ��ʾǰ���ò���Ч�ķ���
     */
    bool setCollpaseSideStretchFactor(double rate);

    /*!
     * \brief setExpandSize
     * \param size
     * \see setCollpaseSideStretchFactor()
     * \warning sizeӦ��������ģ���������Ϊ��ֵ�������δ����ġ�
     * \note ����һ������δ��ʾǰ���ò���Ч�ķ���
     */
    void setExpandSize(int size)
    {
        //    if (!m_bInitShow) return false;
        m_nWantedExpandSize = size;
        m_dWantedExpandFactor = -1;
    }

    /*!
     * \brief setLastExpandedSizeWantedEnable
     * \param enabled true:���һ��չ���Ŀ��Ϊ����ʱ�����ť���չ�����
     *                false:ͨ��setExpandSize��setCollpaseSideStretchFactor�����õ�չ������ǵ����ť��չ�����
     */
    void setLastExpandedSizeWantedEnable(bool enabled = true)
    {
        m_bUsingLastExpandSize = enabled;
    }

    /*!
     * \brief ���ڿ����Ƿ�չ��
     * \param show չ��
     */
    void doTrigger(bool show);

Q_SIGNALS:
    /*!
     * \brief resizeSignal ������resize�¼��з���Щ�źţ�ʹ��handle�е�button�õ�֪ͨ����������Ӧ����button��λ��
     * \param e
     */
    void resizeSignal(QResizeEvent *e);
    void resizeSignal(int length);

protected:
    void showEvent(QShowEvent *e)
    {
        GLDSplitter::showEvent(e);

        onShowEvent();
    }
    void onShowEvent();
    void resizeEvent(QResizeEvent *e)
    {
        emit resizeSignal(e);
        GLDSplitter::resizeEvent(e);
    }
    virtual GLDSplitterHandle *createHandle();
    void initSignalSlot(GLDNetScapeSplitterHandle *handle);
    inline bool isUsingLastExpandSize() const
    {
        return m_bUsingLastExpandSize;
    }

private Q_SLOTS:
    void changeHandleLength(GLDNetScapeSplitterHandle *handle, int handleLengthe);
    void emitHandlerMoved(int length, int index);

private:
    void init();
    int getHandleIndexOffset();
    void showSplitterHandle(GLDNetScapeSplitterHandle *splitterHandle);
    void updateSplitterExpendLength(GLDNetScapeSplitterHandle *splitterHandle);
    void updateSplitterSizes();
    void onFirstTimeShowEvent();

protected:
    int m_minHideLength;
    GLDNetScapeSplitterHandle *m_handle;

private:
    SplitterAlign m_align;
    bool m_bFirstTimeShow;
    bool m_bInitCollapse;
    bool m_bCollapseCompletable;
    bool m_bUsingLastExpandSize;
    int m_nWantedExpandSize;
    double m_dWantedExpandFactor;
private:
    friend class GLDNetScapeSplitterHandle;
    Q_DISABLE_COPY(GLDNetScapeSplitter)
};

#endif // GLDNETSCAPESPLITTER_H
