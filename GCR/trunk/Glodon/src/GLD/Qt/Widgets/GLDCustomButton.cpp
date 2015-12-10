#include "GLDCustomButton.h"

#include <QPainter>

namespace GlodonMask
{
    GLDCustomButton::GLDCustomButton(QWidget *parent)
        : QPushButton(parent)
        , m_pixmap("")
    {

    }

    GLDCustomButton::GLDCustomButton(const QString &iconPath, QWidget* parent)
        : QPushButton(parent)
        , m_pixmap("")
    {
        if (iconPath != "")
        {
            QPixmap btnPixmap;
            btnPixmap.load(iconPath);
            setPixmap(btnPixmap);
        }
    }

    void GLDCustomButton::setPixmap(const QPixmap& pm)
    {
        m_pixmap = pm;
        update();
    }

    QSize GLDCustomButton::sizeHint() const
    {
        if (!m_pixmap.isNull())
        {
            return m_pixmap.size();
        }

        return QPushButton::sizeHint();
    }

    void GLDCustomButton::paintEvent(QPaintEvent* e)
    {
        Q_UNUSED(e);

        QPainter p(this);

        if (!m_pixmap.isNull())
        {
            p.drawPixmap(0, 0, m_pixmap);
        }
    }

}

