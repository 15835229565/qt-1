/****
 * @file   : GLDLineWidthComboBoxEx.h
 * @brief  : ��д���������ѡ���
 *             1.֧�ָ���ѡ��ť�����Ҹ�������������������
 *             2.�����û������Ҫ�󣬽����ظ�Ϊ����������ʾ��ǰ��
 *             3.QSS�����˽���,ÿ���ؼ�������property���ԣ�Ҫ�޸Ŀ�����qss�ж�λ���޸����ԡ�
 *
 * @date   : 2014-08-18
 * @author : lijl-c
 * @remarks: ʵ��˼·��QComboBox�м���2��QListWidget.�������Ƕ��QListWidget
 *                    ÿ����1��QLabel��QPushButton
 ****/

#ifndef GLDLINEWIDTHCOMBOBOXEX_H
#define GLDLINEWIDTHCOMBOBOXEX_H

#include <QMainWindow>
#include <QComboBox>
#include <QLabel>
#include <QListWidgetItem>
#include <QPushButton>
#include <QHBoxLayout>
#include "GLDWidget_Global.h"

class GLDWIDGETSHARED_EXPORT GLDLineWidthButton : public QPushButton
{
    Q_OBJECT
public:
    explicit GLDLineWidthButton(qreal lineWeight, QWidget *parent = 0);
    ~GLDLineWidthButton(){}

protected:
    void resizeEvent(QResizeEvent *e);

private:
    /**
     * @brief drawLineWidth ��ÿһ�е��߿�
     * @param lineWeight
     * @param lineLength
     */
    void drawLineWidth(qreal lineWeight, int lineLength);

private:
    qreal m_lineWeigth;
};

/**
 * @brief The GLDLineWidthRow class �߿��������е�һ��
 */
class GLDWIDGETSHARED_EXPORT GLDLineWidthRow : public QWidget
{
    Q_OBJECT
public:
    explicit GLDLineWidthRow(QWidget *parent = 0, int rowIndex = 0);
    ~GLDLineWidthRow(){}

public:
    /**
     * @brief initRowLabel ��ʼ��ÿ�е�label
     * @param rowIndex
     */
    void initRowLabel(int rowIndex);

    /**
     * @brief initRowButton ��ʼ��ÿ�е��߿�Button
     * @param rowIndex
     */
    void initRowButton(int rowIndex);

signals:
    void mapped(int index);

private:
    QLabel *m_label;
    GLDLineWidthButton *m_lineWidthBtn;
    QHBoxLayout *m_rowLayout;
    int m_rowIndex;
};

class GLDWIDGETSHARED_EXPORT GLDLineWidthComboBoxEx : public QComboBox
{
    Q_OBJECT
public:
    explicit GLDLineWidthComboBoxEx(QWidget *parent = 0);
    ~GLDLineWidthComboBoxEx();

    inline int minLineCount() { return m_minLineCount; }
    inline void setMinLineCount(int minLineCount) { m_minLineCount = minLineCount; }

    inline int maxLineCount() { return m_maxLineCount; }
    inline void setMaxLineCount(int maxLineCount) { m_maxLineCount = maxLineCount; }

    inline int currentIndex() {return m_curIndex;}
    inline void setCurrentIndex(const int index){ m_curIndex = index;}

    inline double curLineWidth() { return m_curLineWidth; }
    inline void setCurLineWidth(const double curLineWidth) { m_curLineWidth = curLineWidth; }

    inline int lineWidthPopupHight() { return m_lineWidthPopupHight; }
    inline void setLineWidthPopupHight(int height) { m_lineWidthPopupHight = height; }

    void setHasBorder(bool hasBorder = false);

private:
    /**
     * @brief ��ʼ���ؼ�ģ��,���ƿؼ�
     *
     * @fn initModel
     */
    void initPopUp();

    /**
     * @brief initLineWidthPart ��ʼ���������ϰ벿��, ���� ��ֵlabels���߿�buttons����
     */
    void initLineWidth();

    /**
     * @brief initMoreLinesPart ��ʼ���������°벿��, ������ɫButton
     */
    void initMoreLinesButton();

    /**
     * @brief createLineWidthRow ����һ��
     * @param index
     * @return
     */
    QWidget* createLineWidthRow(int index);

    /**
     * @brief Ϊ�߿���������ݣ������ÿһ�е�����
     *
     * @fn createLineWidthRowItem
     * @return QListWidget
     */
    void createLineWidthRowItem(QListWidget *pLineWidthItem);

    void createMoreLinesItem(QListWidget *pMoreItem);

signals:
    void itemClicked(int index);

private slots:
    void onClicked(int index);
    void onClicked();

private:
    int m_minLineCount; /**< TODO ��С��������*/
    int m_maxLineCount; /**< TODO �����������*/
    int m_lineWidthPopupHight; /**< TODO ������߶�*/
    bool m_hasBorder;     //�Ƿ���Ҫ�߿�
    QListWidget *m_popupListWidgets;
    int m_curIndex;
    double m_curLineWidth;
};

#endif // GLDLINEWIDTHCOMBOBOXEX_H
