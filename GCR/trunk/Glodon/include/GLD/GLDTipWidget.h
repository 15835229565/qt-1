#ifndef GLDMASKWIDGET_H
#define GLDMASKWIDGET_H

#include "GLDMask_Global.h"

#include <QLabel>
#include <QDialog>
#include <functional>

namespace GlodonMask
{
    typedef std::function<void()> NEXTCLICKEDCALLBACK;

    struct GLDGuideInfoItem
    {
        GLDGuideInfoItem(int width = -1, int height = -1, int leftXPos = -1, int leftYPos = -1,
                         QString normalImage = "", QString hoverImage = "", QString pressedImage = "")
            : m_width(width)
            , m_height(height)
            , m_leftXPos(leftXPos)
            , m_leftYPos(leftYPos)
            , m_normalImage(normalImage)
            , m_hoverImage(hoverImage)
            , m_pressedImage(pressedImage)
        {

        }

        int m_width;               // ͼƬ���
        int m_height;              // ͼƬ�߶�
        int m_leftXPos;            // ���Ͻ�X����
        int m_leftYPos;            // ���Ͻ�Y����

        QString m_normalImage;     // ���������ͼƬ
        QString m_hoverImage;      // ��껮��ʱЧ��
        QString m_pressedImage;    // ��갴��ʱЧ��
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

    class GLDMASKBOXSHARED_EXPORT GLDTipWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit GLDTipWidget(const GLDGuideInfo & guideInfo, NEXTCLICKEDCALLBACK goCallBack = nullptr, QWidget * parent = 0);
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
        QString maskStyleSheet(const GLDGuideInfo &guideInfo);

        /**
         * @brief ��ȡ�رհ�ť��ʽ
         * @param guideInfo    ��ǰ�ɰ�ҳ��Ϣ
         * @return
         */
        QString closeStyleSheet(const GLDGuideInfo &guideInfo);

        /**
         * @brief ��ȡ��һ����ť��ʽ
         * @param guideInfo    ��ǰ�ɰ�ҳ��Ϣ
         * @return
         */
        QString nextStyleSheet(const GLDGuideInfo &guideInfo);

    signals:
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
        GLDMaskTitle*       m_pMaskTitle;          // �ɰ�ͼƬ
        QPushButton*        m_pNextButton;         // ��һ����ť
        QPushButton*        m_pCloseButton;        // �رհ�ť
        NEXTCLICKEDCALLBACK m_goCallBack;
    };
}

#endif // GLDMASKWIDGET_H
