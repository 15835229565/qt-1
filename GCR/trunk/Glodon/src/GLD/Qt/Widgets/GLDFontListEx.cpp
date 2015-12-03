#include <QAbstractItemView>
#include <QPainter>
#include <QFile>
#include <QPalette>
#include <QEvent>
#include <QApplication>
#include <QWindow>
#include <QDialog>
#include <QLineEdit>

#include "GLDShadow.h"
#include "GLDStrings.h"
#include "GLDFileUtils.h"
#include "GLDFontListEx.h"
#include "GLDScrollStyle.h"

const int c_PointSize               =   10;
const int c_itemHeight              =   25;
const int c_nListViewMinWidth       =   350;

const int c_highLightLeftPadding    =   8;  // ����ѡ������ڱ߾�
const int c_highLightRightPadding   =   9;  // ����ѡ������ڱ߾�
const int c_spaceWidth              =   5;  // ÿ����ʾԪ�ؼ�ľ���
const int c_contentLeftPadding      =   12; // ����������������������ڱ߾�
const int c_contentRightPadding     =   10; // ��������������������ڱ߾�
const int c_checkMarkLeftPadding    =   2;  // �Ժ������ѡ�����߾�

const QString c_sFontListQssFile = ":/qsses/GLDFontListEx.qss";

GFontListEx::GFontListEx(QWidget *parent) :
    QFontComboBox(parent),
    m_highLightBackgroundColor(QColor(219, 243, 252)),
    m_highLightTextColor(QColor(0, 0, 0))
{
    setObjectName("GLDFontListEx");
    setHasBorder(true);
    this->setStyleSheet(loadQssFile(c_sFontListQssFile));
    setStyle(new GLDScrollStyle(this));

    // �Ƴ���Ӱ
    GLDShadow *pShadow = new GLDShadow(this);
    pShadow->removeShadow();

    m_pFontDelegate = new GLDFontListDelegate(this);
    setItemDelegate(m_pFontDelegate);

    connect(this, SIGNAL(currentTextChanged(QString)), SLOT(showFontFamily(QString)));
}

GFontListEx::~GFontListEx()
{
}

void GFontListEx::showPopup()
{
    if (lineEdit() != NULL)
    {
        lineEdit()->selectAll();
        lineEdit()->setFocus();
    }

    if (QFrame* popupViewContainer = dynamic_cast<QFrame*>(view()->parentWidget()))
    {
        setHighLighColor(m_highLightBackgroundColor, m_highLightTextColor);
        QRect parentRect = view()->parentWidget()->geometry();
        popupViewContainer->setMinimumWidth(c_nListViewMinWidth);
        popupViewContainer->resize(c_nListViewMinWidth, parentRect.height());
        view()->resize(c_nListViewMinWidth, parentRect.height());
    }
    QFontComboBox::showPopup();
}

void GFontListEx::setHightBackground(QColor color)
{
    m_highLightBackgroundColor = color;
}

void GFontListEx::setHightText(QColor color)
{
    m_highLightTextColor = color;
}

void GFontListEx::setFontListItemDelegate(GLDFontListDelegate *delegate)
{
    m_pFontDelegate = delegate;
    QFontComboBox::setItemDelegate(delegate);
}

void GFontListEx::setHasBorder(bool bHasBorder)
{
    if (bHasBorder)
    {
       setProperty("GFontListEx", "hasborder");
    }
    else
    {
        setProperty("GFontListEx", "noborder");
    }

    this->setStyleSheet(loadQssFile(c_sFontListQssFile));
}

void GFontListEx::showFontFamily(QString family)
{
    m_pFontDelegate->setSelectedFamily(family);  // tbd
}

void GFontListEx::setHighLighColor( QColor background, QColor text)
{
    QPalette palette = view()->palette();
    palette.setColor(QPalette::Highlight, background);
    palette.setColor(QPalette::HighlightedText, text);
    view()->setPalette(palette);
}

GLDFontListDelegate::GLDFontListDelegate(QObject *parent):
    QAbstractItemDelegate(parent),
    m_sTTypeIconPath(QLatin1String(":/icons/GLDFontListEx-true_type.png")),
    m_sBMapIconPath(QLatin1String(":/qt-project.org/styles/commonstyle/images/fontbitmap-16.png")),
    m_trueTypeIcon(m_sTTypeIconPath),
    m_sCMarkIconPath(QLatin1String(":/icons/GLDFontListEx-check_mark.png")),
    m_bitmapIcon(m_sBMapIconPath),
    m_checkMark(m_sCMarkIconPath),
    m_sEnglishCaption(getGLDi18nStr(g_rsFontEffect)),
    m_sZhCaption(getGLDi18nStr(g_rsEffect)),
    m_sDefaultFont(getGLDi18nStr(g_rsSimsun)),
    m_sSelectedFamily(m_sDefaultFont),
    m_bShowCheckMark(true)
{
}

bool isZh(QString str)
{
    bool bZh = str.contains(QRegExp("[\\x4e00-\\x9fa5]+"));  // ������ʽ�ж��Ƿ��������
    return bZh;
}

void GLDFontListDelegate::paintFontTypeImage(QRect &rect, QString fontFamilyName,
                                             QPainter *painter, const QStyleOptionViewItem &option) const
{
    const QIcon *oIcon = &m_bitmapIcon;
    if (QFontDatabase().isSmoothlyScalable(fontFamilyName))
    {
        oIcon = &m_trueTypeIcon;
    }
    QSize actualSize = oIcon->actualSize(rect.size());
    if (m_bShowCheckMark && fontFamilyName == selectedFamily())
    {
        rect.setLeft(rect.left() + c_contentLeftPadding);  // �����������
    }
    else
    {
        rect.setLeft(rect.left() + c_contentLeftPadding);  // �����������
    }

    rect.setRight(rect.right() - c_contentRightPadding);  // �����������
    oIcon->paint(painter, rect, Qt::AlignLeft | Qt::AlignVCenter);  // Ϊ������ϱ�ʶ
    if (option.direction == Qt::RightToLeft)
    {
        rect.setRight(rect.right() - actualSize.width());
    }
    else
    {
        rect.setLeft(rect.left() + actualSize.width());
    }
}

void GLDFontListDelegate::paintCheckStatusIcon(QRect &rect, QPainter *painter) const
{
    const QIcon *pIcon = &m_checkMark;
    rect.setLeft(rect.left() + c_checkMarkLeftPadding);
    pIcon->paint(painter, rect, Qt::AlignLeft | Qt::AlignVCenter);
}

void GLDFontListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                                const QModelIndex &index) const
{
    // �õ���Ҫ��������ѡ��ͼ�� + ������ͼ�� + ������ + Ч��
    QRect drawRect = option.rect;
    drawRect.setLeft(drawRect.left() + c_highLightLeftPadding);
    drawRect.setRight(drawRect.right() - c_highLightRightPadding);

    // ����painter
    if (option.state & QStyle::State_Selected)
    {
        painter->save();
        painter->setBrush(option.palette.highlight());
        painter->setPen(Qt::NoPen);
        painter->drawRect(drawRect);
        painter->setPen(QPen(option.palette.highlightedText(), 0));
        painter->restore();
    }

    QString sCurFamily = selectedFamily();
    QString sFontFamilyName = index.data(Qt::DisplayRole).toString();
    // ����ѡ�е�����ǰ��ĶԺ�ͼ��
    if ((m_bShowCheckMark) && (sCurFamily == sFontFamilyName))
    {
        paintCheckStatusIcon(drawRect, painter);  // ��ѡ������ǰ���Сͼ�꣨��δʵ�֣�
    }
    // ���������ͣ����������ͼ��
    if (m_bShowTypeImageFlag)
    {
        paintFontTypeImage(drawRect, sFontFamilyName, painter, option);
    }

    QFont curFont(option.font);
    curFont.setPointSize(c_PointSize);
    curFont.setFamily(m_sDefaultFont);

    QFontMetricsF fontMetrics(curFont);
    QRectF curFontRect = fontMetrics.tightBoundingRect(sFontFamilyName);

    // �������family��
    drawRect.setLeft(drawRect.left() + 2 * c_spaceWidth);
    painter->setFont(curFont);
    painter->drawText(drawRect.left(),
                      drawRect.y() + (drawRect.height() + curFontRect.height()) / 2.0,
                      sFontFamilyName);

    // ���������ʾЧ��
    QString sEffectTxt;
    if (isZh(sFontFamilyName))
    {
        sEffectTxt = m_sEnglishCaption;
    }
    else
    {
        sEffectTxt = m_sZhCaption;
    }

    QFont curFontStyle = curFont;
    curFontStyle.setFamily(sFontFamilyName);
    QFontMetricsF styledFontMetrics(curFontStyle);
    QRectF styledFontRect = styledFontMetrics.tightBoundingRect(sEffectTxt);

    int nTextWidth = styledFontRect.width();
    drawRect.setRight(drawRect.right() - c_spaceWidth);
    painter->setFont(curFontStyle);
    painter->drawText(drawRect.right() - nTextWidth,
                      drawRect.y() + (drawRect.height() + styledFontRect.height()) / 2.0,
                      sEffectTxt );

    // ���û�б�ѡ�У���λ��ʽ
    if (option.state & QStyle::State_Selected)
    {
        painter->restore();
    }
}

QSize GLDFontListDelegate::sizeHint(const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    QString sFontFamily = index.data(Qt::DisplayRole).toString();
    QFont font(option.font);
    font.setPointSize(QFontInfo(font).pointSize() * 3 / 2);
    QFontMetrics fontMetrics(font);

    return QSize(fontMetrics.width(sFontFamily), c_itemHeight);
}

void GLDFontListDelegate::setTTypeIconPath(const QString &path)
{
    m_sTTypeIconPath = path;
}

void GLDFontListDelegate::setBMapIconPath(const QString &path)
{
    m_sBMapIconPath = path;
}

void GLDFontListDelegate::setCMarkIconPath(const QString &path)
{
    m_sCMarkIconPath = path;
}

bool GLDFontListDelegate::isShowCheckMark()
{
    return m_bShowCheckMark;
}

void GLDFontListDelegate::setIsShowCheckMark(bool isShow)
{
    m_bShowCheckMark = isShow;
}

bool GLDFontListDelegate::isShowFontTypeImage()
{
    return m_bShowTypeImageFlag;
}

void GLDFontListDelegate::setIsShowFontTypeImage(bool isShow)
{
    m_bShowTypeImageFlag = isShow;
}

void GLDFontListDelegate::setEnglishCaption(const QString &caption)
{
    m_sEnglishCaption = caption;
}

void GLDFontListDelegate::setZhCaption(const QString &caption)
{
    m_sZhCaption = caption;
}

QString GLDFontListDelegate::defaultFont()
{
    return m_sDefaultFont;
}

void GLDFontListDelegate::setDefaultFont(QString family)
{
    m_sDefaultFont = family;
}

QString GLDFontListDelegate::selectedFamily() const
{
    return m_sSelectedFamily;
}

void GLDFontListDelegate::setSelectedFamily(const QString &family)
{
    m_sSelectedFamily = family;
}
