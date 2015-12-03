#ifndef GFontListEx_H
#define GFontListEx_H

#include <QFontComboBox>
#include <QAbstractItemDelegate>
#include "GLDWidget_Global.h"

class GLDFontListDelegate;

class GLDWIDGETSHARED_EXPORT GFontListEx : public QFontComboBox
{
    Q_OBJECT
public:
    explicit GFontListEx(QWidget *parent = 0);
    ~GFontListEx();

public:
    virtual void showPopup();
    void setHasBorder(bool bHasBorder = true);

protected:
    QColor m_highLightBackgroundColor;
    QColor m_highLightTextColor;

protected slots:
    void showFontFamily(QString family);

private:
    void setHightBackground(QColor color);
    void setHightText(QColor color);
    void setFontListItemDelegate(GLDFontListDelegate *delegate);
    void setHighLighColor(QColor background, QColor text);

private:
    GLDFontListDelegate *m_pFontDelegate;
};

class GLDWIDGETSHARED_EXPORT GLDFontListDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    explicit GLDFontListDelegate(QObject *parent = 0);

public:
    void setTTypeIconPath(const QString &path);  // ����TrueType��ͼ��·��
    void setBMapIconPath(const QString &path);  // ����Bitmapͼ���·��
    void setCMarkIconPath(const QString &path);  // ����ѡ��״̬ͼ���·��

    // �����Ƿ���ʾѡ��״̬ͼ���getter��setter
    bool isShowCheckMark();
    void setIsShowCheckMark(bool isShow = true);

    // �����Ƿ���ʾ��������ͼ���getter��setter
    bool isShowFontTypeImage();
    void setIsShowFontTypeImage(bool isShow = true);

    // ������ʾʱÿ�������Ӧ��Ч��ͼ
    void setEnglishCaption(const QString &caption);
    void setZhCaption(const QString &caption);

    QString defaultFont();  // ȡ��Ĭ������
    void setDefaultFont(QString family);  // ����Ĭ������

    QString selectedFamily() const;  // ȡ����Ͽ���ѡ�е�����
    void setSelectedFamily(const QString &family);  // ����combobox������ѡ�е�����

protected:
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;  // paint each list item
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const;

private:
    void paintFontTypeImage(QRect &rect, QString fontFamilyName,
                            QPainter *painter, const QStyleOptionViewItem &option) const;
    void paintCheckStatusIcon(QRect &rect, QPainter *painter) const;

private:
    QString m_sTTypeIconPath;  // True Typeͼ���·��
    QString m_sBMapIconPath;  // Bitmpa����ͼ���·��
    QString m_sCMarkIconPath;  // ѡ��״̬ͼ���·��
    QIcon m_trueTypeIcon;
    QIcon m_bitmapIcon;
    QIcon m_checkMark;
    bool m_bShowTypeImageFlag;

    QString m_sEnglishCaption;
    QString m_sZhCaption;
    QString m_sDefaultFont;

    QString m_sSelectedFamily;
    bool m_bShowCheckMark;
};
#endif // GFontListEx_H
