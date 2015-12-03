/*!
 *@file gcolorlist.h
 *@brief {��ɫ����ѡ���}
 *
 *@author Gaosy
 *@date 2012.9.19
 *@remarks 
 *Copyright (c) 1998-2012 Glodon Corporation
 */

#ifndef GLDCOLORLIST_H
#define GLDCOLORLIST_H

#include <QComboBox>
#include <QColor>
#include "GLDWidget_Global.h"

#define ITEM_RIGHT_OFFSET 16

/*!   
 *@class: GColorList
 *@brief {��ɫ����ѡ���}
 *@author Gaosy 
 *@date 2012.9.19
 */
class GLDWIDGETSHARED_EXPORT GColorList : public QComboBox
{
    Q_OBJECT
public:
    explicit GColorList(QWidget *parent = 0);

    void setUserDefaultColor(bool value);
    bool userDefaultColor();
    
    /*!
     *���ݸ�����ɫ���������Ƿ�����ɫ�б���
     *�����򷵻������б��е�λ�ã����򷵻�-1
     *@param[in]  color  ��Ҫ���ҵ���ɫ
     *@return int
     */
    int findColor(QColor color);

    /*!
     *��������ɫ��ӵ���ɫ�б��У��������ɫ�Ѵ���
     *������������б��е��±꣬�����ظ����
     *����������Ӹ���ɫ���б���ĩβ���������±�
     *@param[in]  color  ��Ҫ��ӵ��б��е���ɫ
     *@return int
     */
    int addColor(QColor color);

    /**
     * @brief ������ĵ����ڶ���Ϊ�û��Զ������ɫ
     * @param color
     * @return
     */
    int setUserColor(QColor color);
    QColor userColor();

    /*!
     *������ɫ�б�ǰѡ�е���ɫ
     *@return QColor
     */
    QColor currentColor();

    /**
     * @brief ���õ�ǰ��ɫѡ������ɫ
     * @param color
     */
    void selectColor(QColor color);

    void setCurrentIndex(int index);

signals:
    /**
     * @brief ��ǰ��ɫ�ı�ʱ�Żᷢ�����źţ����������࣬ѡ�����Զ�����ɫ����ᷢ��ѡ����ɫ��Ӧ��index
     * @param index
     */
    void colorIndexChange(int index);

protected:
    void resizeEvent(QResizeEvent *e);

private slots:
    void moreColorClicked(int index);

private:
    QIcon colorToIcon(QColor color);
    void initColorList();

private:
    QSize m_newSize;
    QColor m_userColor;
    bool m_isInInit;
    int m_currentIndex;
    QVector<QColor> m_addColors;
};

#endif // GLDCOLORLIST_H
