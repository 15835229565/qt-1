/****
 * @file   : GLD360MainWindow.h
 * @brief  : 360���������
 *
 * @date   : 2014-04-02
 * @author : duanb
 * @remarks:
 ****/
#ifndef GLD360MAINWINDOW_H
#define GLD360MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QToolButton>

#include "GLDStrUtils.h"
#include "GLDObjectList.h"

class QLabel;
class QHBoxLayout;
class QSignalMapper;

class GLDWIDGETSHARED_EXPORT GLD360PushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit GLD360PushButton(QWidget *parent = 0);
    ~GLD360PushButton();
    void loadPixmap(const QString &picName);
protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
private:
    //ö�ٰ�ť�ļ���״̬
    enum ButtonStatus {NORMAL, ENTER, PRESS, NOSTATUS};
    ButtonStatus m_status;
    QPixmap m_pixmap;
    int m_btnWidth; //��ť���
    int m_btnHeight; //��ť�߶�
    bool m_mousePress; //��ť����Ƿ���
};

class GLDWIDGETSHARED_EXPORT GLD360ToolButton : public QToolButton
{
    Q_OBJECT
public:
    explicit GLD360ToolButton(const GString &text, const GString &picName, QWidget *parent = 0);
    ~GLD360ToolButton();
    void setMousePress(bool mousePress);
protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void painterInfo(int topColor, int middleColor, int bottomColor);
public:
    bool m_mouseOver;    // ����Ƿ��ƹ�
    bool m_mousePress;    // ����Ƿ���
};

// ������
class GLDWIDGETSHARED_EXPORT GLD360WindowTile : public QWidget
{
    Q_OBJECT
public:
    explicit GLD360WindowTile(QWidget *parent = 0);
    virtual ~GLD360WindowTile();
signals:
    void showSkin();
    void showMin();
    void showMax();
    void showMainMenu();
    void closeWidget();
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
private:
    bool m_isMove;
    QPoint m_pressPoint;//��갴��ȥ�ĵ�

    QLabel *m_versionTitle; //����
    GLD360PushButton *m_skinButton; //����
    GLD360PushButton *m_mainMenuButton; //���˵�
    GLD360PushButton *m_minButton; //��С��
    GLD360PushButton *m_maxButton; //���
    GLD360PushButton *m_closeButton; //�ر�
};

// ������
class GLDWIDGETSHARED_EXPORT GLD360MainToolBar : public QWidget
{
    Q_OBJECT
public:
    explicit GLD360MainToolBar(QWidget *parent = 0);
    virtual ~GLD360MainToolBar();
public:
    void add360Action(const GString &text, const GString &picName);
    void setLogo(const GString &picName);
    void setCurrentPage(const QString &currentPage);
public slots:
signals:
    void showMax();
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
private slots:
    void turnPage(const QString &currentPage);
private:
    bool m_isMove;
    QPoint m_pressPoint; // ��갴��ȥ�ĵ�
    GLDVector<GLD360ToolButton *> m_buttonList;
    QSignalMapper *m_signalMapper;
    QHBoxLayout *m_buttonLayout;
    QLabel *m_logoLabel;
};

// ������
class GLDWIDGETSHARED_EXPORT GLD360MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GLD360MainWindow(QWidget *parent = 0);
    virtual ~GLD360MainWindow();
public:
    void init();
    bool isCloseWhenMinimized() const;
    void setIsCloseWhenMinimized(bool isCloseWhenMinimized);
    void setSkinName(const QString &skinName);
    bool allowMax() const;
    void setAllowMax(bool allowMax);

    GLD360MainToolBar *mainToolBar() const;
    void setMainToolBar(GLD360MainToolBar *mainToolBar);

    GLD360WindowTile *titleWidget() const;
    void setTitleWidget(GLD360WindowTile *titleWidget);

public slots:
    void showWidget();
protected:
    virtual void initialize();
signals:
    void showSkin();
protected:
    void paintEvent(QPaintEvent *);
private slots:
    void showMax();
    void showMainMenu();
    void changeSkin(const QString &skinName);
private:
    QRect m_location;
    GLD360WindowTile *m_titleWidget; //������
    GLD360MainToolBar *m_mainToolBar; // ������
    // todo �����滹û������
    GObjectList<QWidget*> m_contentWidgetList; //����������
    QHBoxLayout *m_mainLayOut;
    QString m_skinName;//�����ڱ���ͼƬ������
    // todo
    QMenu *m_mainMenu; //���˵�
    bool m_isCloseWhenMinimized;
    bool m_allowMax;
};

#endif // GLD360MAINWINDOW_H

