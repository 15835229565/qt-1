#ifndef GLD_TABDOCKCONTAINER_H
#define GLD_TABDOCKCONTAINER_H
/************************************************************************
@author huy-a
@date 2014-08-28
@note

�ṩ����VS��ͣ�������ù�����+dockWidgetʵ��

ע�⣬���ͣ�����й�������ͣ���������ܻ������tab��dock ����֮����빤���������⡣


************************************************************************/
#include <QDockWidget>
#include <QTabBar>
#include <QToolBar>
#include <QToolButton>
#include <QPushButton>
#include <QString>
#include <QRect>
#include <QLabel>
#include <QHBoxLayout>
#include <QAction>
#include "GLDComboBox.h"

class GLDTabDockContainerWidget;
class GLDTabDockContainer;
class GLDTabDockContainerTitleWidget;
/**
 * @brief �ṩ��ƽbutton
 */
class GLDWIDGETSHARED_EXPORT GLDTabDockContainerWidgetAnchorButton : public QPushButton
{
    Q_OBJECT
    friend class GLDTabDockContainerWidget;
    friend class GLDTabDockContainerTitleWidget;
private:
    GLDTabDockContainerWidgetAnchorButton(QWidget *parent): QPushButton(parent)
    {
        setFlat(true);
    }
    virtual void enterEvent(QEvent *)
    {
        setFlat(false);
    }
    virtual void leaveEvent(QEvent *)
    {
        setFlat(true);
    }
};

/**
 * @brief The Title Widget
 */
class GLDWIDGETSHARED_EXPORT GLDTabDockContainerTitleWidget : public QWidget
{
    Q_OBJECT
    friend class GLDTabDockContainerWidget;
public:
    explicit GLDTabDockContainerTitleWidget(QWidget *parent);
    void setDockWidget(GLDTabDockContainerWidget *dockerWidget);
    GLDTabDockContainerWidgetAnchorButton *addAnchorButton();
    QToolBar* toolBar();
protected:
    virtual void mouseMoveEvent(QMouseEvent *event);
private:
    QLabel *m_title;
    QToolBar *m_userToolBar;
    QToolBar *m_toolBar;
    GLDTabDockContainerWidgetAnchorButton *m_anchorButton;
    QHBoxLayout *m_layout;
    GLDTabDockContainerWidget *m_dockerWidget;
    QAction *m_action;
};

/**
 * @brief The Dock widget
 */
class GLDWIDGETSHARED_EXPORT GLDTabDockContainerWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit GLDTabDockContainerWidget(const QString &title, QWidget *parent = 0);
    explicit GLDTabDockContainerWidget(QWidget *parent = 0);
signals:
    void anchorChanged(bool anchored);
public:

    /**
     * @brief ���úͻ������/��������ͼ��
     * @param anchoredIcon
     */
    void setAnchoredIcon(const QIcon &anchoredIcon);
    void setNotAnchoredIcon(const QIcon &notAnchoredIcon);

    QIcon anchoredIcon() const;
    QIcon notAnchoredIcon() const;

    /**
     * @brief ��ǰ�Ƿ�����
     * @return
     */
    bool isAnchored() const;

    /**
     * @brief ���úͻ������/����������ʾ
     * @param anchoredToolTip
     * @param notAnchoredToolTip
     */
    void setAnchorToolTip(const QString &anchoredToolTip, const QString &notAnchoredToolTip);
    void anchorToolTip(QString &anchoredToolTip, QString &notAnchoredToolTip) const;

    /**
     * @brief �����Ƿ��Զ������ͻ���������趨Ϊ�棬���ڸ���ʱ������ͼʹͣ�����ڱ��ֿͻ����ĸ߶�/��ȡ�
     *        ��������sizehint�����㸡�����ڴ�С
     * @param autoHeight
     */
    void setAutoFillHeight(bool autoHeight);
    bool isAutoFillHeight() const;

    /**
     * @brief ���ñ���
     * @param title
     */
    void setTitle(const QString &title);
    QString title() const;
    /**
     * @brief ���title���toolbar
     * @param title
     */
    QToolBar* titleToolBar();

    /**
     * @brief ��������ͣ��ʱ�䣬ms
     * @param interval
     */
    void setTimerInterval(int interval = 500);
    int timerInterval();


public slots:
    /**
     * @brief ��ê��״̬���ʱ dockWidget����
     */
    void hideWidget();

    /**
     * @brief ��ê��״̬���ʱ dockWidget��ʾ
     */
    void showWidget();
    void setAnchored(bool anchored);

    //��ͣ�ͻָ�����ͣ����ʱ��
    void pauseTimer();
    void resumeTimer();
protected:
    virtual void leaveEvent(QEvent *);
    virtual void enterEvent(QEvent *);
    void timerEvent(QTimerEvent *e);
protected:
    //��Ӧ�ſ�������ê����close��float����Ҫ�ˣ��߼�����
    void setFloatable(bool floatable);
    bool isFloatable() const;
    void setClosable(bool closable);
    bool isClosable() const;
private slots:
    void anchorButtonClicked();
    void leaveHide();
    void setLeaved(bool isLeaved);
signals:
    void setHideAndEntered(bool, bool);
private:
    void updateFloatAndCloseState();
private:
    //GLDTabDockContainerWidgetAnchorButton *m_anchorButton;
    GLDTabDockContainerTitleWidget *m_titleWidget;
    QIcon m_anchordIcon;
    QIcon m_notAnchoredIcon;
    bool m_currentAnchoredState;//default:anchored,true.
    bool m_floatable;//true;
    bool m_closable;//false;
    bool m_autoFillHeight;//true;
    QString m_anchoredToolTip;
    QString m_notAnchoredToolTip;
    int m_timerID;
    bool m_bisEntered;
    bool m_bisHide;
    bool m_bisFloating;//false
    int m_interval;
};

class GLDWIDGETSHARED_EXPORT GLDTabDockContainerTabBar : public QTabBar
{
    Q_OBJECT
public:
    explicit GLDTabDockContainerTabBar(QWidget *parent);
	Qt::Orientation textOrientation() const {return m_textOrientation;}
	void setTextOrientation(Qt::Orientation textOrientation){m_textOrientation = textOrientation;}
    void setTimerInterval(int interval = 500);
signals:
    void tabChanged(int currentTab, int preTab);
    void tabLeave();
    void setLeaved(bool isLeave);
public slots:
    void setHideAndEntered(bool isHide, bool isEntered);
protected:
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void leaveEvent(QEvent *);
    virtual void timerEvent(QTimerEvent *e);
    virtual void paintEvent(QPaintEvent *event);
private:
    int m_curIndex;//-1
	Qt::Orientation m_textOrientation;//Hor
    int m_preIndex;
    int m_timerID;
    bool m_bisHide;
    bool m_bisEntered;
    int m_interval;
};

class GLDWIDGETSHARED_EXPORT GLDTabDockContainerBar : public QWidget
{
    Q_OBJECT
    friend class GLDTabDockContainer;
public:
    explicit GLDTabDockContainerBar(QWidget *parent);
    //void setBar(GLDTabDockContainerInnerTabBar *bar);
public slots:
    void selectTab(int idx);
    void addDockWidget(GLDTabDockContainerWidget *widget);
    void removeDockWidget(GLDTabDockContainerWidget *widget);
private slots:
    void currentTabChanged(int cur, int pre);
private:
    QToolBar *m_dockToolBar;
    GLDTabDockContainerTabBar *m_tabBar;
    QList<int> m_tabIndexes;
    QList<GLDTabDockContainerWidget *> m_dockWidgets;
    int m_timerLong;
};

class GLDWIDGETSHARED_EXPORT GLDTabDockContainer : public QWidget
{
    Q_OBJECT
public:
    // attention! "dockarea" must only have only one area.
    explicit GLDTabDockContainer(Qt::DockWidgetArea dockArea, QMainWindow *mainWindow,QWidget *parent);
    // the GLDTabDockContianer will delete the widget,before destroy;
    //and will be the parent of the widget.
    void addTabDockContainerWidget(GLDTabDockContainerWidget *widget);
    void hideWidget();
    void showWidget();
    //��λ ms
    void setTimerInterval(int interval);


    // if the parent window is the main window,the fuction is not need.
    // if not,the function must be called before addTabDockContainerWidget function.
    void setMainWindow(QMainWindow *mainWindow);
	void setTabTextForceVertical(bool isTextVertical);
	bool isTabTextForceVertical() const;
private slots:
    void anchorChanged(bool anchored);
private:
    void updateAllWidget();
    Qt::DockWidgetArea m_dockArea;
    QMainWindow *m_mainWindow;
    GLDTabDockContainerBar *m_bar;
	bool m_textForceVertical;//false;
    int m_interval;
    QList<GLDTabDockContainerWidget *> m_dockWidgets;
};

#endif//GLD_TABDOCKCONTAINER_H
