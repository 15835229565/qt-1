#ifndef GLDNETSCAPESPLITTERHANDLE_H
#define GLDNETSCAPESPLITTERHANDLE_H

#include "GLDSplitterHandle.h"
#include "GLDWidget_Global.h"

const int c_InitialHidenLength = 12;
const int c_InitialHandleWidth = 10;
const int c_InitialButtonLength = 120;

const int c_TriangleToEndRate = 20;
const int c_TriangleBottomToBorderPixel = 2;

class GLDNetScapeSplitter;
class GLDNetScapeSplitterButton;

/*!
 * \brief The GLDNetScapeSplitterHandle class ��д��handle�࣬��Ҫ��������GLDNetScapeSplitter����ʹ�ã���Ϊ
 *GLDNetScapeSplitterButton������
 */
class GLDWIDGETSHARED_EXPORT GLDNetScapeSplitterHandle : public GLDSplitterHandle
{
    Q_OBJECT
public:
    explicit GLDNetScapeSplitterHandle(Qt::Orientation o, GLDSplitter *parent);

public:
    /*!
     * \brief setButtonLength ���ð�����GLDNetScapeSplitterButton�ĳ���ֵ(��ν���ȣ���ָ��ͨ��btn�ϳ�����һ�ߵĳߴ�)
     * \param val ����Ϊ��λ
     */
    void setButtonLength(int val)
    {
        m_buttonHeight = val;
        //TODO btn��ʾ���������Ҫ��Ȼ��Ч
    }

    int buttonLenght() const
    {
        return m_buttonHeight;
    }

    /*!
     * \brief setCollapseLength
     * \param val ����Ҫ�ɱ��������һ������ʱ����С�ߴ�,һ���,����һ����Ϊ���Ĭ��ֵ,���˴�����Ϊ0��ֵ,���ʾ������ȫ����(Ҳ��������)
     *
     */
    void setCollapseLength(int val)
    {
        int nPreVal = m_collapseLength;
        m_collapseLength = qMax(val, 0);
        Q_UNUSED(nPreVal);
        //TODO ���ǽ����Ѿ���ʾ����ô˽ӿڵ�����
    }
    int collapseLength() const
    {
        return m_collapseLength;
    }

    int dragMoveState() const
    {
        return m_dragMoveState;
    }

    inline bool getSplitterState()
    {
        return m_bExpanded;
    }

    inline GLDNetScapeSplitterButton *getButton()
    {
        return m_pButton;
    }

    void adjustButtonPos(int buttonHeight);

    virtual void initButton();

signals:
    void splitterStateSwitched(GLDNetScapeSplitterHandle *, int);

public slots:
    virtual void handlerButtonClick();
    virtual void onSplitterResized(QResizeEvent *e);
    virtual void onSplitterResized(int nSplitterLength);

protected:
    enum EnDragMoveState
    {
        initial = -1,
        pressed,
        moved,
        dragging
    };

protected:
    void setDragMoveState(int state)
    {
        m_dragMoveState = state;
    }

    void changeSplitterExpendLength(QResizeEvent *e);

    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    int curArrowDirection() const;
    int newArrowDirection() const;
    void adjustArrowDirection();


    void saveExpandLength(int expandLength) const;

protected:
    mutable int m_buttonHeight;
    mutable int m_collapseLength;
    mutable int m_expandedLength;

    GLDNetScapeSplitterButton *m_pButton;
    GLDNetScapeSplitter *m_pSplitter;

    int m_dragMoveState;
    bool m_bExpanded;

private:
    friend class GLDNetScapeSplitter;
    friend class GLDNetScapeSplitterButton;
    Q_DISABLE_COPY(GLDNetScapeSplitterHandle)
};

#endif // GLDNETSCAPESPLITTERHANDLE_H
