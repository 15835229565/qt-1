#ifndef GLDIRREGULARFORM_H
#define GLDIRREGULARFORM_H

#include "GLDMask_Global.h"

#include <QWidget>

class QPushButton;
class GLDCustomButton;

namespace GlodonMask
{
    class GLDMASKBOXSHARED_EXPORT GLDIrregularForm : public QWidget
    {
        Q_OBJECT

    public:
        explicit GLDIrregularForm(QWidget *parent = 0);
        explicit GLDIrregularForm(const QString & irregularImgPath, const QString & btnImgPath, QWidget *parent = nullptr);

        ~GLDIrregularForm();

        /**
        * @brief ���ش����С
        */
        QSize sizeHint() const;

        /**
        * @brief ���ñ�־������
        */
        void setFlagAndAttribute();

        /**
        * @brief ����pixmap
        */
        void loadPixmap(const QString & pixmapPath);

        /**
        * @brief ����pixmap
        */
        void setPixmap(const QPixmap & pm);

        /**
        * @brief ���ð�ťλ��
        */
        void setBtnPos(QPushButton* pBtn, const int x, const int y);

    Q_SIGNALS:
        void irregularFormClicked();

    protected:
        virtual void paintEvent(QPaintEvent *event);

    private:
        GLDCustomButton* m_pCustomBtn;      // �Զ��尴ť
        QPixmap          m_irregularFormPm; // ��ʾ��Ϣpixmap
        int              m_xPosition;
        int              m_yPosition;
    };
}

#endif // GLDIRREGULARFORM_H
