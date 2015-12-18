#ifndef GLDMASKBOXMANGER_H
#define GLDMASKBOXMANGER_H

#include "GLDMaskBox.h"

namespace GlodonMask
{
    class GLDMASKBOXSHARED_EXPORT GLDMaskBoxManger : public QWidget
    {
    public:
        explicit GLDMaskBoxManger(QList<QWidget *> wgtList, const QString & iniPath, QWidget* parent = nullptr);

        virtual ~GLDMaskBoxManger();

        /**
         * @brief ��ȡ��index���ɰ�
         * @param index
         * @return
         */
        GLDMaskBox* get(const int index);

        /**
         * @brief �����ɰ����
         * @return
         */
        size_t size();

    private:

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
        * @brief ��ʼ����ʾ��Ϣ�б�
        * @return
        */
        void initTipInfo(const QString & iniPath);

        /**
        * @brief ����xml�ļ�
        * @return
        */
        void parseXML(const QString & iniPath);

        /**
        * @brief ����xml�ļ��е�һ���ڵ���
        * @return
        */
        GLDGuideInfoItem parseNodeItem(QDomElement &element);

        /**
        * @brief TipWidget����һ����ť����������Ĳ���
        * @return
        */
        void onNextBtnClicked();

        /**
         * @brief canShow
         * @return
         */
        bool canShow();

    private:
        QList<QWidget *>        m_wgtList;        // ��Ҫ�����ɰ��widget�б�
        QString                 m_iniPath;        // ��ʾ��Ϣ�����ļ�·��
        static int              m_step;           // �ڼ����ɰ�
        QList<GLDTipWidget*>    m_tipInfoList;    // ��ʾ��Ϣ�б�
        QList<GLDGuideInfo>     m_guideInfoList;  // ����Ϣ�б�
        QList<GLDMaskBox*>      m_maskBoxList;    // �ɰ��б�
        QList<GLDMaskBoxParam>  m_maskParamList;  // �ɰ�����б�
    };
}

#endif // GLDMASKBOXMANGER_H
