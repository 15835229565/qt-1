#ifndef GColorListEx_H
#define GColorListEx_H

#include <QColor>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QList>
#include <QListWidget>
#include <QPushButton>
#include "GLDWidget_Global.h"

typedef QList<QColor> GLDColorList;

/**
  * GLDColorBlock
 */
class GLDWIDGETSHARED_EXPORT GLDColorBlock : public QPushButton
{
    Q_OBJECT
public:
    explicit GLDColorBlock(const QColor &color, const QColor &edgeColor, QWidget *parent = 0);
    ~GLDColorBlock(){}

    void updateColor(const QColor &color, const QColor &edgeColor);
    inline QColor color() const
    {
        return m_color;
    }

    inline QColor edgeColor() const
    {
        return m_edgeColor;
    }

private:
    void drawColorBlock();

signals:
    void colorValue(const QColor &color, const QColor &edgeColor);
    void colorBlock(GLDColorBlock *currentBlock);
    void commitSelectedColor(const QColor &color, const QColor &edgeColor);

public slots:
    void onClick();

private:
    QColor m_color;
    QColor m_edgeColor;
};

/**
  * GLDColorTableTitle
 */
class GLDWIDGETSHARED_EXPORT GLDColorTableTitle : public QPushButton
{
    Q_OBJECT
public:
    explicit  GLDColorTableTitle(QWidget *parent = 0);
    ~GLDColorTableTitle(){}
};

/**
  * GLDColorRow
 */
class GLDWIDGETSHARED_EXPORT GLDColorRow : public QWidget
{
    Q_OBJECT
public:
    explicit GLDColorRow(const QList<QColor> &colors, const QList<QColor> &edgeColors, QWidget *parent = 0);
    ~GLDColorRow(){}

public:
    void setBackgroundColor(QColor &color);
    void updateColorBlocks(QList<QColor> &colors, QList<QColor> &edgeColors, int updateColorCount);
    GLDColorBlock* initBlock();
    GLDColorBlock* findColorBlock(const QColor color);
    int findColorBlockIndex(const QColor color);

private:
    void initColorBlocks(const QList<QColor> &colors, const QList<QColor> &edgeColors);
    void initColorBlocksLayout();

signals:
    void currentSelectedColor(const QColor &color, const QColor &edgeColor);
    void currentSelectedBlock(GLDColorBlock *block);
    void commitSelectedColor(const QColor &color, const QColor &edgeColor);

private:
    QList<GLDColorBlock *> m_colorBlocks;
};

/**
  * GLDColorTable
*/
class GLDWIDGETSHARED_EXPORT GLDColorTable : public QWidget
{
    Q_OBJECT
public:
    explicit GLDColorTable(const QList<QColor> &firstRowColors, const QList<QColor> &firstRowEdgeColors, QWidget *parent);
    ~GLDColorTable();

    void addTitle(const QString &title);
    void appendColorRow(const QList<QColor> &colors, const QList<QColor> &edgeColor);
    void updateColorRow(int row, QList<QColor> &blockColors,
                        QList<QColor> &blockEdgeColors, int updateColorCount);
    void initTableLayout();
    void setBackgroundColor(QColor &color);
    GLDColorBlock* initBlock();
    GLDColorBlock* findColorBlock(const QColor &color);
    int findColorBlockIndex(const QColor &color, const QColor &edgeColor);

signals:
    void currentSelectedColor(const QColor &color, const QColor &edgeColor);
    void currentSelectedBlock(GLDColorBlock *block);
    void findColor(const QColor &color);
    void commitSelectedColor(const QColor &color, const QColor &edgeColor);

protected:
    void mouseReleaseEvent(QMouseEvent *e);

private:
    void initTitleLayout(QVBoxLayout *layout);
    void initColorRows(QVBoxLayout *layout);

private:
    GLDColorTableTitle *m_title;
    QList<GLDColorRow *> m_colorRows;
    QColor m_BackColor;
};

/**
  * GColorListEx
*/
class GLDWIDGETSHARED_EXPORT GColorListEx : public QComboBox
{
    Q_OBJECT
public:
    // isLoadRecentColor���������Ƿ�������ʱ�ļ��Ա�������شӸ�����ɫ��ѡ�����ɫ
    explicit GColorListEx(QWidget *parent = 0, QColor color = QColor("#000000"),
                          bool isLoadRecentColor = false);
    ~GColorListEx();

public:
    void setHasBorder(bool bHasBorder);
    void loadColorFile(const QString &fileName = ":/inis/GColorListEx.ini");

    /**
     * @brief ���ݸ�����ɫ,�������Ƿ�����ɫ�б���
     *        �����򷵻������б��е�λ��,���򷵻�-1
     * @param color  ��Ҫ���ҵ���ɫ
     * @return
     */
    GLDColorBlock *findColorBlock(const QColor &color);

    /**
     * @brief ������ɫ�б�ǰѡ�е���ɫ
     * @return
     */
    QColor currentColor() const;

    void setCurrentColor(const QColor color);

    /**
     * @brief isLoadRecentColor �Ƿ�������ʱ�ļ��Լ��غͱ�������Ӹ�����ɫ��ѡ�����ɫ
     * @return
     */
    bool isLoadRecentColor() const;
    /**
     * @brief setIsLoadRecentColor �����Ƿ�������ʱ�ļ��Լ��غͱ�������Ӹ�����ɫ��ѡ�����ɫ
     * @param isLoadRecentColor
     */
    void setIsLoadRecentColor(const bool isLoadRecentColor);

    /**
     * @brief ��ɫ���Ƿ���ʾToolTip
     * @return
     */
    bool isShowRGBColor() const;

    /**
     * @brief ������ɫ���Ƿ���ʾToolTip
     * @param isShowColorRGB
     */
    void setIsShowRGBColor(const bool isShowColorRGB = false);

    /**
     * @brief �ؼ�����༭״̬���Ƿ���ʾ��ʾ����ɫ���RGBֵ
     * @return
     */
    bool isShowRGBStr() const;

    /**
     * @brief ���ÿؼ�����༭״̬���Ƿ���ʾ��ʾ����ɫ���RGBֵ
     * @param isShowRGBStr
     */
    void setIsShowRGBStr(bool isShowRGBStr);

    /**
     * @brief iconUrlInEdit ���ñ༭�������icon, iconUrlΪicon������·��
     *                      ����icon�������Ƶģ�����Ϊ����16*16 pixel��icon
     *                      �е�ͼ��Ϊ14*10 pixel������ˮƽ���д�ֱ���ϣ��Ա�֤��������
     * @return
     */
    QString iconUrlInEdit() const;
    void setIconUrlInEdit(const QString iconUrl);

signals:
    void currentSelectedColor(const QColor &color, const QColor &edgeColor);
    /**
     * @brief ��ǰ��ɫ�ı�ʱ�Żᷢ�����źţ����������࣬ѡ�����Զ�����ɫ����ᷢ��ѡ����ɫ��Ӧ��index
     * @param index
     */
    void colorIndexChange(const QColor &color);
    void findColor(const QColor &color, const GLDColorBlock *block);
    void colorBlockClicked(int);

private slots:
    void drawColor(const QColor &color, const QColor &edgeColor);
    void moreColor();
    void currentSelectedBlock(GLDColorBlock *block);
    void commitSelectedColor(const QColor &color, const QColor &edgeColor);

private:
    QColor getColor(const QString sVal);
    void addGrayColorTable();
    void addMoreButton();
    void addStandardColorTable();
    void addRecentColorTable();
    QColor getEdgeColor(const QColor &color);
    void updateRecentColorTable();
    void addTable(GLDColorTable *table, int tableWid, int tableHeight);
    void addThemeColorTable();
    void initColorComboBox();
    void initPopUpWidget();
    void addRecentColorList();
    void loadDefaultConfigColorVal();
    void loadSelectedMoreColor();
    void saveSelectedMoreColor();
    void removeRecentColorConfFile();
    void updateCurrentColor();

private:
    GLDColorList m_blockColors;               // ��ɫ���ڲ���ɫ
    GLDColorList m_edgeColors;                // ��ɫ��߿���ɫ
    QListWidget *m_comboBoxWidget;
    QColor m_curColor;
    QColor m_userColor;
    GLDColorBlock *m_currentBlock;
    GLDColorBlock *m_originalBlock;
    int m_recentUseColorCount;
    GLDColorList m_recentUseColor;
    GLDColorList m_recentUseEdgeColor;
    GLDColorTable *m_recentColorTable;
    QList<GLDColorTable *> m_colorTableList;
    bool m_isLoadRecentColor;                 // �����Ƿ�������ʱ�ļ��Ա�������شӸ�����ɫ��ѡ�����ɫ
    bool m_isShowRGBColor;                    // �����Ƿ���ʾRGB��ÿ����ɫbutton��
    bool m_isShowRGBStr;                      // ���Ƹ������Ƿ���ʾ��ʾ��ɫ���RGB�ַ���
    QString m_iconUrlInEdit;                  // ��ű༭����icon��Url
};

#endif // GColorListEx_H
