#include "GLDColorList.h"
#include <QStringList>
#include <QPixmap>
#include <QColorDialog>
#include <QStylePainter>
#include <QResizeEvent>

static const int c_GlobalColorCount = 20; //Qt�Դ�GlobalColorö�ٵĸ���

GColorList::GColorList(QWidget *parent) :
    QComboBox(parent), m_newSize(QSize()), m_userColor(QColor(Qt::white)),
    m_isInInit(true), m_currentIndex(0)
{
    m_newSize = size() - QSize(ITEM_RIGHT_OFFSET, 0);
    initColorList();
    connect(this, SIGNAL(currentIndexChanged(int)), this, SLOT(moreColorClicked(int)));
}

int GColorList::findColor(QColor color)
{
    for (int i = 0; i < count() - 1; i++)
    {
        if (itemData(i).value<QColor>() == color)
        {
            return i;
        }
    }
    return -1;
}

int GColorList::addColor(QColor color)
{
    int nIndex = findColor(color);
    if (nIndex == -1)
    {
        nIndex = count() - 3;

        insertItem(nIndex, colorToIcon(color), "", color);
        m_addColors.push_back(color);
        return nIndex + 1;
    }
    else
    {
        return nIndex;
    }
}

int GColorList::setUserColor(QColor color)
{
    int nIndex = findColor(color);
    if (nIndex == -1)
    {
        nIndex = count() - 2;
        setItemIcon(nIndex, colorToIcon(color));
        setItemData(nIndex, color);
    }
    m_userColor = color;
    setCurrentIndex(nIndex);
    return nIndex;
}

QColor GColorList::userColor()
{
    return m_userColor;
}

QColor GColorList::currentColor()
{
    int nIndex = currentIndex();
    return qvariant_cast<QColor>(itemData(nIndex));
}

void GColorList::selectColor(QColor color)
{
    int nIndex = findColor(color);
    if (nIndex == -1)
    {
        setUserColor(color);
    }
    else
    {
        setCurrentIndex(nIndex);
    }
}

void GColorList::setCurrentIndex(int index)
{
    m_currentIndex = index;
    QComboBox::setCurrentIndex(index);
    emit colorIndexChange(index);
}

void GColorList::resizeEvent(QResizeEvent *e)
{
    if (e->oldSize() != e->size())
    {
        m_newSize = e->size() - QSize(ITEM_RIGHT_OFFSET, 0);
        initColorList();
    }
}

void GColorList::moreColorClicked(int index)
{
    if (!m_isInInit)
    {
        if (index == count() - 1)
        {
            QColor originalColor = qvariant_cast<QColor>(itemData(m_currentIndex));
            if (!originalColor.isValid())
                originalColor = Qt::black;
            QColor color = QColorDialog::getColor(originalColor, this);
			if (color.isValid())	//��ֹ�����Ѿ�ѡ��ĳ����ɫ��ѡ��more...��Ȼ��Esc��������ڵ�����
				setUserColor(color);
			else if (0 <= m_currentIndex && m_currentIndex < index)
				setCurrentIndex(m_currentIndex);
        }
        else if (index != m_currentIndex)
        {
            m_currentIndex = index;
            emit colorIndexChange(index);
        }
    }
}

QIcon GColorList::colorToIcon(QColor color)
{
    QPixmap pix(m_newSize);
    pix.fill(Qt::white);

    QPainter painter(&pix);

    painter.drawRect(2, 3, pix.width() - 15, pix.height() - 8);
    painter.fillRect(QRect(3, 4, pix.width() - 16, pix.height() - 9), QColor(color));
    return QIcon(pix);
}

void GColorList::initColorList()
{
    m_isInInit = true;
    clear();
    setIconSize(m_newSize);
    //����GlobalColorö�٣�������Ӧ��QColor�����뵽QComBox��, ȡ����ɫΪö�ٵ�������ʼ�������ڶ���
    for (int i = 0; i < c_GlobalColorCount - 3; i++)
    {
        QColor color = QColor(Qt::GlobalColor(i + 2));//Ϊ�˱�֤comboBox��index��ö����ɫ���Ӧ������+2

        addItem(colorToIcon(color), NULL, color);
    }

    for (int i = 0; i < m_addColors.count(); ++i)
    {
        QColor color = QColor(m_addColors.at(i));
        addItem(colorToIcon(color), NULL, color);
    }
    //����û��Զ�����ɫ��Ĭ��Ϊ��ɫ
    addItem(colorToIcon(m_userColor), NULL, m_userColor);

    //��Ӹ���ѡ��
    QPixmap pix(m_newSize);
    pix.fill(Qt::white);

    QPainter painter(&pix);
    painter.drawText(QRect(3, 4, pix.width() - 16, pix.height() - 9), tr("more..."));//TRANS_STRING("����..."));

    addItem(QIcon(pix), NULL);
    m_isInInit = false;
    setCurrentIndex(m_currentIndex);
}

