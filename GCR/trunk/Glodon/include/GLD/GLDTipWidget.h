#ifndef GLDMASKWIDGET_H
#define GLDMASKWIDGET_H

#include "GLDString.h"
#include "GLDMask_Global.h"

#include <QLabel>
#include <QDialog>

#include <functional>

namespace GlodonMask
{
    typedef std::function<void()> NEXTCALLBACK;

    struct GLDGuideInfoItem
    {
        GLDGuideInfoItem(int width = -1, int height = -1, int leftXPos = -1, int leftYPos = -1,
                         GString normalImage = "", GString hoverImage = "", GString pressedImage = "")
            : m_width(width)
            , m_height(height)
            , m_leftXPos(leftXPos)
            , m_leftYPos(leftYPos)
            , m_normalImage(normalImage)
            , m_hoverImage(hoverImage)
            , m_pressedImage(pressedImage)
        {

        }

        int m_width;               // �ɰ�ͼ�ı���
        int m_height;              // �ɰ�ͼ�ı���
        int m_leftXPos;            // ���Ͻ�X����
        int m_leftYPos;            // ���Ͻ�Y����

        GString m_normalImage;     // ���������ͼƬ
        GString m_hoverImage;      // ��껮��ʱЧ��
        GString m_pressedImage;    // ��갴��ʱЧ��
    };

    struct GLDGuideInfo
    {
        GLDGuideInfo()
        {

        }

        GLDGuideInfo(GLDGuideInfoItem maskWidgetItem, GLDGuideInfoItem nextButtonItem,
                     GLDGuideInfoItem closeButtonItem)
            : m_maskWidgetItem(maskWidgetItem)
            , m_nextButtonItem(nextButtonItem)
            , m_closeButtonItem(closeButtonItem)
        {

        }

        GLDGuideInfoItem m_maskWidgetItem;    // �ɰ�
        GLDGuideInfoItem m_nextButtonItem;    // ��һ��
        GLDGuideInfoItem m_closeButtonItem;   // �ر�
    };

    class GLDMaskTitle : public QLabel
    {
        Q_OBJECT

    public:
        explicit GLDMaskTitle(QWidget *parent = 0);
        ~GLDMaskTitle();
    };


    typedef QList<GLDGuideInfo> GLDGuideInfoList;

    class GLDMASKSHARED_EXPORT GLDTipWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit GLDTipWidget(QWidget *parent = 0);
        explicit GLDTipWidget(const GLDGuideInfo & guideInfo, NEXTCALLBACK goCallBack = nullptr, QWidget * parent = 0);
        ~GLDTipWidget();

        /**
         * @brief ��ʼ���ɰ�������
         */
        void initMaskTitle();

        /**
         * @brief ��ʼ����һ����ť
         */
        void initNextButton();

        /**
         * @brief ��ʼ���رհ�ť
         */
        void initCloseButton();

        /**
         * @brief ��ȡ��һ����ť
         * @return
         */
        QPushButton* nextBtn();

    private:
        /**
         * @brief ���õ�ǰ�ɰ�ҳ��
         */
        void setCurrentGuidePage();

        /**
         * @brief �����ɰ���ʽ
         * @param guideInfo    ��ǰ�ɰ�ҳ��Ϣ
         */
        void setMaskWidgetStyle(const GLDGuideInfo &guideInfo);

        /**
         * @brief ���ùرհ�ť��ʽ
         * @param guideInfo    ��ǰ�ɰ�ҳ��Ϣ
         */
        void setCloseButtonStyle(const GLDGuideInfo &guideInfo);

        /**
         * @brief ������һ����ť��ʽ
         * @param guideInfo    ��ǰ�ɰ�ҳ��Ϣ
         */
        void setNextButtonStyle(const GLDGuideInfo &guideInfo);

        /**
         * @brief ��ȡ�ɰ���ʽ
         * @param guideInfo    ��ǰ�ɰ�ҳ��Ϣ
         * @return
         */
        GString maskStyleSheet(const GLDGuideInfo &guideInfo);

        /**
         * @brief ��ȡ�رհ�ť��ʽ
         * @param guideInfo    ��ǰ�ɰ�ҳ��Ϣ
         * @return
         */
        GString closeStyleSheet(const GLDGuideInfo &guideInfo);

        /**
         * @brief ��ȡ��һ����ť��ʽ
         * @param guideInfo    ��ǰ�ɰ�ҳ��Ϣ
         * @return
         */
        GString nextStyleSheet(const GLDGuideInfo &guideInfo);

    signals:
        void currentBtnClicked(/*int step*/);
        void tipWidgetClicked();

    private slots:
        /**
         * @brief �ر��ɰ����
         */
        void closeMaskWidget();

        /**
         * @brief ��һ����ť�����
         */
        void nextButtonClicked();

    private:
        int                 m_step;                // ��ǰ����
        GLDMaskTitle*       m_pMaskTitle;          // �ɰ�ͼƬ
        QPushButton*        m_pNextButton;         // ��һ����ť
        QPushButton*        m_pCloseButton;        // �رհ�ť
        NEXTCALLBACK        m_goCallBack;
    };
}

#endif // GLDMASKWIDGET_H
