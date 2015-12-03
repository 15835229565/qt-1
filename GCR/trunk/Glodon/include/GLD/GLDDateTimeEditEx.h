#ifndef GLDDateTimeEditEx_H
#define GLDDateTimeEditEx_H

#include "GLDDateTimeEdit.h"
#include "GLDCalendarWidget.h"

#include <QAction>
#include <QComboBox>
#include <QHBoxLayout>
#include <QHoverEvent>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QSpacerItem>
#include <QSpinBox>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWheelEvent>
#include "GLDWidget_Global.h"


/**
 * @brief The GLDDateTimeEditEx class ������
 */
class GLDWIDGETSHARED_EXPORT GLDDateTimeEditEx : public GLDDateTimeEdit
{
    Q_OBJECT
public:
    enum ButtonTypes { None, ComboBoxArrow, Ellipsis };

    explicit GLDDateTimeEditEx(const QDateTime &dt = QDateTime::currentDateTime(), QWidget *parent = 0);
    ~ GLDDateTimeEditEx();

public:

    /**
     * @brief plainText ���ر༭�������
     * @return
     */
    QString plainText();

    bool calendarPopup() const;

    /**
     * @brief setCalendarPopup �����Ƿ��е�����
     * @param enable
     */
    void setCalendarPopup(bool enable);

    /**
     * @brief setHasBorder �����Ƿ��б���
     * @param bValue
     */
    void setHasBorder(const bool bValue);

    /**
     * @brief ��ȡQSS�ļ�·��
     * @param path
     */
    virtual const QString qssFilePath(const QString &path);

    /**
     * @brief ���ڲ��ܰ�����ĸ��Ϣ��ʾ
     * @param ��
     */
    virtual void excludeLetterMessageBox();

    /**
     * @brief �������뷽ʽ������Ϣ��ʾ
     * @param ��
     */
    virtual void errorDateMessageBox();

    /**
     * @brief ѡ�������С����С������Ϣ��ʾ
     * @param ��
     */
    virtual void dateLessThanSysDateMessageBox();

    /**
     * @brief ѡ������ڴ������������Ϣ��ʾ
     * @param ��
     */
    virtual void dateLargerThanSysDateMessageBox();

    void updateValue();

    /** �������ڵ���ʾ��ʽ
     *  yyyy:������  MM:�����·�  dd:������
     *  hh:����ʱ mm:����� ss:������
     *  ��ʽһ��Ϊ: yyyy-MM-dd hh:mm:ss
     * @brief displayFormat
     * @return
     */
    QString displayFormat() const;

    /** ��������ı仯����Ҫ������ʾ��ʽ��ʱ������ĸ�ʽ������(���ϸ�����, ���ִ�Сд)
     *  yyyy:������  MM:�����·�  dd:������
     *  hh:����ʱ mm:����� ss:������
     *  ��ʽһ��Ϊ: yyyy-MM-dd hh:mm:ss
     * @brief setDisplayFormat
     * @param format
     */
    void setDisplayFormat(const QString &format);

    /**
     * @brief setCalendarPopupOffset �����������������ƫ����
     * @param xOffset
     * @param yOffset
     */
    void setCalendarPopupOffset(int xOffset = 0, int yOffset = 0);

signals:
    void inputInvalid(bool bIsInputInvalid);

protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

    QDateTime dateTimeFromText(const QString &text) const;
    QString textFromDateTime(const QDateTime &dt) const;
    QValidator::State validate(QString &input, int &pos) const;
    void focusOutEvent(QFocusEvent *event);

private:
    /**
     * @brief initCalendarPopup
     */
    void initCalendarPopup();

    /**
     * @brief positionCalendarPopup ��λ�������λ�ã��ر�������Ļ����ʱ������λ�ö�λ
     */
    void positionCalendarPopup();

    /**
     * @brief showPopUp ��ʾ����������
     */
    void showPopUp();

    /**
     * @brief hidePopUp ��������������
     */
    void hidePopUp();

    QStyle::SubControl newHoverControl(const QPoint &pos);
    /**
     * @brief parseText ���ò�ȫ�ķ�ʽ�����û�����Ĳ����������ڸ�ʽ���в�ȫ����, ֻ����0����
     *                  ��2014-1-2 3:4:5����Ϊ2014-01-02 03:04:05
     * @param input �û�����
     * @return  ����ȫ�����ڸ�ʽ
     */
    QString parseText(const QString &input);

    QString formatDate(const QString &input);

Q_SIGNALS:
    void onshowPopup(bool &value);

private slots:
    /**
     * @brief GLDDateTimeEditEx::selectDate ��ʾ����������
     * @param date
     */
    void selectDate(const QDate &date);
    void selectDateTime(const QDateTime &dateTime);

private:
    bool m_isCalendarPopup; // �Ƿ��е�����
    bool m_hasBorder;
    bool m_curKeyIsEnter; // �ж��Ƿ���Key_Enter��Key_Return��
    // m_justKeyPressed �� m_keyPressing�������Ʊ༭��ɾ����ĵ�һ�κ�֮�������
    bool m_justKeyPressed;
    bool m_keyPressing;
    QString m_curStr; // ���浱ǰ����
    mutable QString m_lastStrForDatetime;
    int m_curPos; //���浱ǰ�����position
    GLDCalendarWidget *m_calendarWidget;
    ButtonTypes m_buttonType;
    QDateTime m_dateTime;
    int m_xOffset;
    int m_yOffset;
};

#endif // GLDDateTimeEditEx_H
