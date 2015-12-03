#ifndef GLDWINDOWCOMBOBOX_H
#define GLDWINDOWCOMBOBOX_H

#include <QDesktopWidget>
#include <QBoxLayout>
#include <QSizeGrip>
#include <QPointer>
#include <QLineEdit>
#include <QStyle>
#include <QAbstractSpinBox>
#include <QDialog>
#include "GLDWAbstractspinbox.h"

class QStyleOptionSpinBox;
class GLDWindowComboBox;
class GLDComboBoxPopup;

class GLDWIDGETSHARED_EXPORT GLDWindowComboBox : public GLDWAbstractSpinBox
{
    Q_OBJECT
    Q_PROPERTY(bool hasSelectedText READ hasSelectedText)
public:
    enum ButtonTypes { None, ComboBoxArrow, Ellipsis };

    explicit GLDWindowComboBox(QWidget *parent = 0);
    ~GLDWindowComboBox();

    //���������������
    QWidget *popupWidget() const;
    virtual void setPopupWidget(QWidget *popup);

    //��������������ⲿ�ؼ�
    inline GLDComboBoxPopup *comboBoxPopup() { return m_pComboxPopup; }

    bool isEditable() const;
    void setEditable(bool editable);

    QString editText() const;
    void setEditText(const QString &text);

    inline GLDPlainTextEdit *getLineEdit() { return lineEdit(); }

    //�����Ƿ���ʾ��������
    bool framePopup() const;
    void setFramePopup(bool enable);

    inline bool hidePopupOnEdit() const { return m_hidePopupOnEdit; }
    inline void setHidePopupOnEdit(const bool value) { m_hidePopupOnEdit = value; }

    inline bool showPopupOnEnter() const { return m_showPopupOnEnter; }
    inline void setShowPopupOnEnter(const bool value) { m_showPopupOnEnter = value; }

    inline bool hideEditOnExit() const { return m_hideEditOnExit; }
    inline void setHideEditOnExit(bool value) { m_hideEditOnExit = value;}

    /**
     * @brief ����������ʾ��ʱ��, Ĭ��Ϊ150����, ʱ��ԽС, ��ʾԽ��
     *        ��Ҫ���ô�ʱ��, ����setPopupWidget֮������
     * @param time
     */
    void setPopupScrollTime(int time);
    int popupScrollTime();

    void setResizeEnable(bool value);
    void setPopupSize(QSize value);
    void setPopupHeight(int value);

    void hidePopup(); //ֻ���أ����رգ�������editor����

    void setButtonTypes(ButtonTypes type);
    ButtonTypes buttonType();

    bool hasSelectedText();

    inline void setAnimationPopup(bool animateEnabled = true) { m_animationPopup = animateEnabled; }
    inline bool animationPopup() const { return m_animationPopup; }
public:
    void showPopup();
    void closePopup();

Q_SIGNALS:
    void onManualColsePopup();
    void keyPressType(Qt::Key key, bool &handled);
    void onHide();
    void shouldShowPopup(bool &value);

    void selectionChanged();
    void cursorPositionChanged();

public slots:
    void cut();
    void copy();
    void paste();
    void deleteSelectedText();

private Q_SLOTS:
    void doPopupHide();
    void doSelectionChanged();
    void doCursorPositionChanged();

protected:
    void init();
    QStyle::SubControl newHoverControl(const QPoint &pos);
    virtual void updateEditFieldGeometry();
    void updateArrow(QStyle::StateFlag state);
    void syncPopupWidget();
    void initComboBoxPopup(QWidget *cw = 0);

protected:
    void keyPressEvent(QKeyEvent *event);
    void focusInEvent(QFocusEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    void initStyleOption(QStyleOptionSpinBox *option) const;

    bool eventFilter(QObject *object, QEvent *event);
    void resizeEvent(QResizeEvent *event);
    void moveEvent(QMoveEvent *);

    void setPopupFixedWidth(int width);

protected:
    ButtonTypes m_buttonType; //edit�еİ�ť��ʽ

private:
    GLDComboBoxPopup *m_pComboxPopup;
    bool m_hasHadFocus;
    bool m_framePopuped;
    bool m_hidePopupOnEdit; //�����������editʱ������������
    bool m_showPopupOnEnter; //����༭��ʱֱ�ӵ�������
    bool m_hideEditOnExit; //ʧȥ�����˳��༭
    QStyle::StateFlag m_arrowState;
    bool m_editorNeedFocus;//����༭�򲢵�������ʱ���ý�����editor��    
    bool m_animationPopup;
#ifdef QT_KEYPAD_NAVIGATION
    bool focusOnButton;
#endif
    friend class GLDComboBoxPopup;
};

class GLDWIDGETSHARED_EXPORT GLDComboBoxPopup : public QDialog
{
    Q_OBJECT
public:
    explicit GLDComboBoxPopup(QWidget *parent = 0, QWidget *cw = 0);
    QWidget *popupWidget() const { return const_cast<GLDComboBoxPopup*>(this)->verifyPopupInstance(); }

    void setpopupWidget(QWidget *cw);
    void setSizeGripEnabled(bool enabled);
    void setPopupSize(QSize value);
    void setPopupHeight(int value);
    int popuHeight();
    inline void setAtBottom(bool value) { m_isAtBottom = value; }
    QSize sizeHint() const;
    inline void setScrollTime(int time) { m_scrollTime = time; }
    inline int scrollTime() { return m_scrollTime; }
    inline void setAnimationPopup(bool animateEnabled = true) { m_animationPopup = animateEnabled; }
    inline bool animationPopup() const { return m_animationPopup; }

Q_SIGNALS:
    void onHide();
    void shouldShowPopup(bool &value);
public Q_SLOTS:
    void setEditorFocus();
    void show();
    int exec();
protected:
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    void resizeEvent(QResizeEvent *e);
    bool event(QEvent *e);
    bool eventFilter(QObject *object, QEvent *event);
    void positionFramePopup();
private:
    QWidget *verifyPopupInstance();
    void setEdgeCursor();
    void alignResizer(const QRect &rect);
    void initPopupSize();
private:
    QPointer<QWidget> m_popupWidget;
    QPoint m_curPos;
    QSizeGrip *m_resizer;
    bool m_sizeGripEnabled;
    //��ʱ���ã�m_popupWidgetû������eventFilter
    bool m_cursorChanged;
    bool m_canDrag;
    bool m_isAtBottom; //resizer�Ƿ�λ������
    QSize m_popupSize;
    int m_scrollTime; //ComboBoxPopup������������Ҫ��ʱ��,0Ϊû�й���Ч��
    bool m_animationPopup;
    friend class GLDWindowComboBox;
};

#endif // GLDWINDOWCOMBOBOX_H
