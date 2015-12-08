#ifndef GLDMASK_H
#define GLDMASK_H

#include "GLDMask_Global.h"
#include "GLDIrregularForm.h"

#include <QSettings>

class QPushButton;

namespace GLDCBB
{
    static QWidget* topParentWidget(QWidget* pWgt)
    {
        if (!pWgt)
        {
            return nullptr;
        }

        QWidget* widget = nullptr;

        for (widget = pWgt; widget != nullptr; widget = widget->parentWidget())
        {
            if (widget->isWindow())
            {
                break;
            }
        }

        return widget;
    }
}

struct CoordinateParam
{
public:
    enum Quadrant
    {
        Zero,
        First,
        Second,
        Third,
        Fourth
    };

    CoordinateParam()
        : m_point(-1, -1)
        , m_quadrant(Zero)
    {

    }

    QPoint                     m_point;
    CoordinateParam::Quadrant  m_quadrant;
};

class GLDMaskBoxParam
{
public:
    GLDMaskBoxParam()
        : m_strTipPath("")
        , m_strBtnPath("")
        , m_maskWidget(nullptr)
    {

    }

    GLDMaskBoxParam& operator=(GLDMaskBoxParam& param)
    {
        m_strTipPath = param.m_strTipPath;
        m_strBtnPath = param.m_strBtnPath;
        m_maskWidget = param.m_maskWidget;
        return *this;
    }

    QString  m_strTipPath;      // ��ʾ��Ϣ
    QString  m_strBtnPath;      // ��ť
    QWidget* m_maskWidget;      // ��Ҫ��ʾ�ɰ��widget
};

class GLDMASKSHARED_EXPORT GLDMaskBox : public QWidget
{
    Q_OBJECT

public:
    enum MASKCOLOR
    {
        GrayColor,      // 128, 128, 128
        GlassColor,     // 201, 120, 12
        CalaeattaColor, // 252, 239, 232
        CreamColor      // 233, 241, 246
    };

public:
    static GLDMaskBox* createMaskFor(QWidget* widget, QPushButton *btn = nullptr, const QString & tipInfoPath = "", const QString & btnInfoPath = "", const QString & iniPath = "");

    /**
     * @brief �����ɰ���ɫ
     * @param maskColor
     */
    void setMaskColor(MASKCOLOR maskColor);

    /**
     * @brief ���ü�ͷ��ɫ
     * @param color
     */
    void setArrowColor(const QColor& color);

    /**
     * @brief ���ü�ͷ���߿��
     * @param lineWidth
     */
    void setArrowLineWidth(const int lineWidth);

    /**
     * @brief ��ȡini�ļ������ж��Ƿ���Ҫ��ʾ�ɰ�
     * @param filePath
     */
    void openIniFile(const QString& filePath);

    bool isShown(const QString & iniPath);

private:
    void setMaskShow();
    bool getMaskShow(const QString& prefix, const QString& key);

    QString getValue(const QString& prefix, const QString& key);
    void setValue(const QString& prefix, const QString& key);

    /**
     * @brief ������ʾ��Ϣλ��
     * @return
     */
    CoordinateParam calcPosOfTipInfo();

private:
    GLDMaskBox(QWidget *parent = nullptr);
    GLDMaskBox(GLDMaskBoxParam& param, QWidget * parent = nullptr);
    GLDMaskBox(GLDMaskBoxParam& param, QPushButton *btn = nullptr, QWidget * parent = nullptr);
    virtual ~GLDMaskBox();

Q_SIGNALS:
    void customClicked();

public slots:
    /**
     * @brief �ر��ɰ�
     */
    void slotClose();

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);

private:
    /**
     * @brief �����ɰ�
     * @param painter
     */
    void drawMask(QPainter & painter);

    /**
     * @brief ����ָ�����Ͻǵļ�ͷ,������������
     * @param ownerPoint    ���
     * @param endPoint      �յ�
     * @param painter
     */
    void drawLeftTopArrow(QPoint &startPoint, QPoint &endPoint, QPainter &painter);

    /**
     * @brief ����ָ�����½ǵļ�ͷ,������������
     * @param ownerPoint    ���
     * @param endPoint      �յ�
     * @param painter
     */
    void drawLeftBottomArrow(QPoint &startPoint, QPoint &endPoint, QPainter &painter);

    /**
     * @brief ����ָ�����Ͻǵļ�ͷ,������������
     * @param ownerPoint    ���
     * @param endPoint      �յ�
     * @param painter
     */
    void drawTopRightArrow(QPoint &startPoint, QPoint &endPoint, QPainter &painter);

    /**
     * @brief ����ָ�����µļ�ͷ,������������
     * @param ownerPoint    ���
     * @param endPoint      �յ�
     * @param painter
     */
    void drawRightBottomArrow(QPoint &startPoint, QPoint &endPoint, QPainter &painter);

private:
    static GLDMaskBox*    m_pMaskBox;

    GLDMaskBox::MASKCOLOR m_maskColor;

    GLDMaskBoxParam       m_oMaskBoxParam;

    QWidget*              m_pClippedWgt;
    QSettings*            m_pSettings;
    GLDIrregularForm*     m_pTipBox;

    bool                  m_bShowMask;

    QColor                m_arrowColor;
    int                   m_arrowLineWidth;
};

#endif // GLDMASK_H
