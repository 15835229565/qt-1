#ifndef GLDMASKBOX_H
#define GLDMASKBOX_H

#include "GLDMask_Global.h"
#include "GLDIrregularForm.h"
#include <windows.h>

#include <QSettings>

class QPushButton;

namespace GlodonMask
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

        QString  m_strTipPath;      // ��ʾ��Ϣ·��
        QString  m_strBtnPath;      // ��ť·��
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
        static GLDMaskBox* createMaskFor(QWidget* widget,
            QPushButton *btn = nullptr,
            const QString & tipInfoPath = "",
            const QString & btnInfoPath = "",
            const QString & iniPath = "");

        /**
         * @brief �����ɰ汳��ɫ
         * @param maskColor
         */
        void setMaskColor(MASKCOLOR maskColor);

        /**
         * @brief ���ü�ͷ��ɫ
         * @param color
         */
        void setArrowColor(const QColor& color);

        /**
         * @brief ���ü�ͷ������ϸ
         * @param lineWidth
         */
        void setArrowLineWidth(const int lineWidth);

        /**
         * @brief ��ȡini�ļ�
         * @param filePath
         */
        void openIniFile(const QString& filePath);

        /**
        * @brief ��ȡini�ļ������ж��Ƿ���ʾ�ɰ�
        * @return
        */
        bool canShow();

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
        GLDMaskBox(GLDMaskBoxParam& param, const QString & iniPath,
            QPushButton *btn = nullptr, QWidget * parent = nullptr);
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
         * @brief ����ָ�����Ͻǵļ�ͷ
         * @param startPoint    ���
         * @param endPoint      �յ�
         * @param painter
         */
        void drawLeftTopArrow(QPoint &startPoint, QPoint &endPoint, QPainter &painter);

        /**
         * @brief ����ָ�����½ǵļ�ͷ
         * @param startPoint    ���
         * @param endPoint      �յ�
         * @param painter
         */
        void drawLeftBottomArrow(QPoint &startPoint, QPoint &endPoint, QPainter &painter);

        /**
         * @brief ����ָ�����Ͻǵļ�ͷ
         * @param startPoint    ���
         * @param endPoint      �յ�
         * @param painter
         */
        void drawTopRightArrow(QPoint &startPoint, QPoint &endPoint, QPainter &painter);

        /**
         * @brief ����ָ�����½ǵļ�ͷ
         * @param startPoint    ���
         * @param endPoint      �յ�
         * @param painter
         */
        void drawRightBottomArrow(QPoint &startPoint, QPoint &endPoint, QPainter &painter);

        /**
         * @brief ��ȡwidget�Ķ��������ڵľ��
         * @param pWidget
         */
        HWND getHandle(QWidget *pWidget);

    private:
        static GLDMaskBox*    m_pMaskBox;       // �ɰ�widget

        GLDMaskBox::MASKCOLOR m_maskColor;      // �ɰ汳��ɫ

        GLDMaskBoxParam       m_oMaskBoxParam;  // �ɰ����

        QWidget*              m_pClippedWgt;    // ��Ҫ��ʾ�ɰ��widget
        QSettings*            m_pSettings;      // ini�ļ�����
        GLDIrregularForm*     m_pTipBox;        // ��ʾ��Ϣ

        bool                  m_bShowMask;      // �Ƿ���ʾ�ɰ�

        QColor                m_arrowColor;     // ��ͷ��ɫ
        int                   m_arrowLineWidth; // ��ͷ������ϸ
        QString               m_iniPath;        // ini�ļ�·��
        QString               m_btnObjectName;  // �Զ��尴ť������
    };
}
#endif // GLDMASKBOX_H
