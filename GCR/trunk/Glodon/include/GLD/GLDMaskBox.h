#ifndef GLDMASKBOX_H
#define GLDMASKBOX_H

#include "GLDTipWidget.h"
#include "GLDMask_Global.h"
#include "GLDIrregularForm.h"

#include <QList>
#include <QSettings>
#include <QtXml/QDomElement>

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

    struct GLDMaskBoxParam
    {
    public:
        GLDMaskBoxParam()
            : m_maskWidget(nullptr)
            , m_pTipWgt(nullptr)
        {

        }

        GLDMaskBoxParam& operator=(GLDMaskBoxParam& param)
        {
            m_maskWidget = param.m_maskWidget;
            m_pTipWgt = param.m_pTipWgt;
            return *this;
        }

        QWidget*      m_maskWidget;      // ��Ҫ��ʾ�ɰ��widget
        GLDTipWidget* m_pTipWgt;         // ��ʾ��Ϣ����
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
            CreamColor      // 20, 20, 20
        };

    public:
        explicit GLDMaskBox(GLDMaskBoxParam& param, QWidget * parent = nullptr);
        explicit GLDMaskBox(QList<QWidget *> wgtList, const QString & iniPath, QWidget * parent = nullptr);

        virtual ~GLDMaskBox();

        /**
        * @brief ��ʼ���ɰ��б�
        * @param widget
        */
        void initMaskList();

        /**
        * @brief ��ʼ���ɰ�����б�
        * @param wgtList
        */
        void initMaskParamList(QList<QWidget*> wgtList);

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

        /**
         * @brief ��ȡ�ɰ����
         * @return
         */
        GLDMaskBoxParam getMaskBoxParam();

    private:
        /**
         * @brief ������ʾ��Ϣλ��
         * @return
         */
        CoordinateParam calcPosOfTipInfo();

    Q_SIGNALS:
        void customClicked();
        void nextBtnClicked();

    public slots:
        /**
         * @brief �ر��ɰ�
         */
        void slotClose();

    protected:
        virtual void paintEvent(QPaintEvent *event);
        virtual bool eventFilter(QObject *watched, QEvent *event);

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

    private:
        MASKCOLOR               m_maskColor;      // �ɰ汳��ɫ

        GLDMaskBoxParam         m_oMaskBoxParam;  // �ɰ����

        QWidget*                m_pClippedWgt;    // ��Ҫ��ʾ�ɰ��widget
        GLDTipWidget*           m_pTipWidget;     // ��ʾ��Ϣ����

        QColor                  m_arrowColor;     // ��ͷ��ɫ
        int                     m_arrowLineWidth; // ��ͷ������ϸ
        QString                 m_iniPath;        // ini�ļ�·��
        QString                 m_btnObjectName;  // �Զ��尴ť������
        QList<GLDTipWidget*>    m_tipInfoList;    // ��ʾ��Ϣ�б�
        QList<GLDGuideInfo>     m_guideInfoList;  // ����Ϣ�б�
        QList<GLDMaskBox*>      m_maskBoxList;    // �ɰ��б�
        QList<GLDMaskBoxParam>  m_maskParamList;  // �ɰ�����б�
        int                     m_step;
    };
}
#endif // GLDMASKBOX_H
