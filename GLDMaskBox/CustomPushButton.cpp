#include "custompushbutton.h"

#include <QPainter>


CustomPushButton::CustomPushButton(QString imagePath, QWidget *parent)
    : QPushButton(parent)
    , m_imagePath(imagePath)
{
    setAttribute(Qt::WA_TranslucentBackground);//���ñ���͸��

    pic.load(m_imagePath);//����ͼ��

    resize(pic.size());
}

void CustomPushButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.drawPixmap(0, 0, pic);//����ͼ��
}
