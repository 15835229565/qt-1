/*!
 *@file GLDCommentFrame.h
 *@brief ������һ�������ƶ�comment��
 *@author liul
 *@date 2014.4.24
 *@remarks {remarks}
 *Copyright (c) 1998-2014 Glodon Corporation
 */

#ifndef GLDCUSTOMCOMMENTFRAME_H
#define GLDCUSTOMCOMMENTFRAME_H

#include <QDialog>
#include <QWidget>
#include <QPoint>
#include <QModelIndex>
#include <QString>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QLabel>
#include <QGraphicsDropShadowEffect>

#include "GLDTextEdit.h"
#include "GLDTableView_Global.h"

#define GLD_PI 3.14159265358979

class GLDTABLEVIEWSHARED_EXPORT GCustomCommentFrame : public QFrame
{
    Q_OBJECT
public:
    explicit GCustomCommentFrame(QWidget* parent = NULL, QPoint pt = QPoint(0, 0));
    ~GCustomCommentFrame();
    enum GCustomCommentFrameState
    {
        m_EnMoving = 0,
        m_EnUP,
        m_EnDown,
        m_EnLeft,
        m_EnRiht,
        m_EnLeftUp,
        m_EnbottomLeft,
        m_EnRightUp,
        m_EnRightDown,
        m_EnNormal
    };
    const static int c_AdjustWith = 6;

public:
    inline QModelIndex curIndex() { return m_curIndex; }
    inline void setCurIndex(const QModelIndex &index) { m_curIndex = index; }

    void setFramePosition(QPoint point);

    void resetBordrect();

    // ����겻�����ϵ���¼���ʱ�򣬻�ȡ�����༭״̬����Ҫ������༭״̬����Ϊfalse
    inline void setEllopseHide() {  m_isShowEllopse = false; }

    inline bool isShowCommentPersistent() { return m_isShowCommentPersistent; }
    inline QPoint topLeft(){ return m_topLeft; }

Q_SIGNALS:
    void textChanged(const QString &str);

    // ��ע��ʧȥ����ʱ�ᴥ���źţ��ⲿдֵ��ʱ��
    void editFocusOut();

public Q_SLOTS:
    void hide();
    void show(bool isPersistent = false);
    void move(int x, int y);
    void move(const QPoint &);
    void move(QModelIndex index);
    void moveTo(QPoint point);
    void setCommentText(const QString &str);
    QString commentText();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    bool eventFilter(QObject *obj, QEvent *event);
    void showEvent(QShowEvent *);
    void resizeEvent(QResizeEvent *);

private:
    void onMouseMoveEvent(QMouseEvent *e);
    void initPlaintEdit();
    void setInitStyle();
    void setCommentFrameSize();
    void setCommentFrameMask();
    void setEditTextPos();
    void resetBorderRect();
    // TODO: ��������ĿҲ��ҪһЩ�Ƕ�ת���ȣ�����ת�Ƕȣ���������������ȵ�ʱ����Ҫ��ź�������������ȥ��
    double cacultAngle();
    inline double radianToAngle(const double Degree){ return (Degree*180/GLD_PI);}
    double getDistance(const QPoint border, const QPoint pos);

    void inMoveRange(QPoint pos);
    // TODO:����Ժ���ҪƵ����һЩ������֮����жϹ�ϵ�Ļ�����Ҫ����Щ�ŵ�һ������������ȥ
    bool containPosPoint(const QPoint pos, const QPoint border);
    bool containPos(const QPoint pos, const QRect subBorderRect);

    void repainLineAndArrow(QPainter *painter);
    void repainArrow(QPainter *painter);
    void repainArrowMoving(QPainter *painter);
    void repainAdjustRect(QPainter *painter);

    inline QPoint adjustRectLeftPoint();
    inline QPoint adjustRectRightPoint();
    inline QPoint adjustRectUpPoint();
    inline QPoint adjustRectBottomPoint();

    bool isPosInFrame(QPoint pos);
    void resetFramePosition();

private:
    QWidget *m_parent;        // ��ŵ�commet������
    const int m_nMarginWidth; // �߿�ͱ༭��֮��Ĵ�С
    int m_nWidth;       // �༭��Ŀ��
    int m_nHeight;      // �༭��ĸ߶�
    int m_nDefaultWidth;       // �༭��Ŀ��
    int m_nDefaultHeight;      // �༭��ĸ߶�
    QModelIndex m_curIndex;
    bool m_isShowEllopse;       // �༭���Ƿ�ѡ��
    bool m_starDraw;            // ��濪ʼ

    //�����ƶ���Ҫ
//    QPoint m_windowPos;
    QPoint m_mousePos;
 //   QPoint m_dPos;
    GCustomCommentFrameState m_state;

    // �ÿؼ����ӿؼ��������ĸ�����ͷ����ͷ���༭��ľ��룬�༭���ƶ���ͼ�Ρ�
    GLDPlainTextEdit *m_plainTextEdit;   // �༭��
    QPoint m_topLeft;                     // ��ͷ�Ķ���λ��
    QPoint m_bottomRight;                 // ��ͷ�ļ�βλ�ã��;��α༭�������λ��
    QRect m_borderRect;
    double m_angle;
    QVector<QPoint> m_arrowPoints;
    bool m_isShowCommentPersistent;
};

QPoint GCustomCommentFrame::adjustRectLeftPoint()
{
    return QPoint(m_borderRect.left() - 10, (m_borderRect.top() + m_borderRect.bottom()) / 2);
}

QPoint GCustomCommentFrame::adjustRectRightPoint()
{
    return QPoint(m_borderRect.right(), (m_borderRect.top() + m_borderRect.bottom()) / 2);
}

QPoint GCustomCommentFrame::adjustRectUpPoint()
{
    return QPoint((m_borderRect.left() + m_borderRect.right()) / 2, m_borderRect.top() - 10);
}

QPoint GCustomCommentFrame::adjustRectBottomPoint()
{
    return QPoint((m_borderRect.left() + m_borderRect.right()) / 2, m_borderRect.bottom());
}

#endif // GLDCOMMENTFRAME_H
