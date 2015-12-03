/*!
 *@file glodondefaultitemdelegate.h
 *@brief {Ĭ�ϱ༭��ʽ}
 *�ṩ��TableView��Ҫ��Ĭ�ϱ༭��ʽ������Ҫ��չ����һ�ɴӴ�����
 *@author Gaosy
 *@date 2012.9.7
 *@remarks {remarks}
 *Copyright (c) 1998-2012 Glodon Corporation
 */

#ifndef GLDDEFAULTITEMDELEGATE_H
#define GLDDEFAULTITEMDELEGATE_H

#include <QItemDelegate>
#include "GLDComboBox.h"
#include "GLDEnum.h"

#include "GLDDateTimeEdit.h"
#include "GLDMathUtils.h"
#include "GLDTableView_Global.h"

class QComboBox;
class GlodonAbstractItemView;
class GlodonAbstractItemViewPrivate;
class GLDTableView;
class GLDTableViewPrivate;
class GLDAbstractButtonEdit;
class GlodonDefaultItemDelegatePrivate;
class GLDWindowComboBoxEx;
class GLDLineWidthComboBoxEx;

/*!
 *@class: GlodonDefaultItemDelegate
 *@brief {GridĬ�ϱ༭��ʽ��������Ҫ��չ�༭��ʽ�ģ�����Ҫ����������}
 *@author Gaosy
 *@date 2012.9.10
 */
class GLDTABLEVIEWSHARED_EXPORT GlodonDefaultItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit GlodonDefaultItemDelegate(QObject *parent = 0);

public:
    // ��������Ҫ���ǵķ���
    virtual bool editable(const QModelIndex &index) const;
    virtual GEditStyle editStyle(const QModelIndex &index, bool &readOnly) const;
    virtual void initEllipsisButtonEdit(GLDAbstractButtonEdit *ellipsis, const QModelIndex &index) const;
    virtual void initComboBox(QComboBox *comboBox, const QModelIndex &index) const;
    virtual void initWindowComboBox(GLDWindowComboBoxEx *comboBox, const QModelIndex &index) const;
    virtual void initLineWidthComboBox(GLDLineWidthComboBoxEx *comboBox, const QModelIndex &index) const;
    virtual void initSpinBox(QAbstractSpinBox *spinBox, const QModelIndex &index);
    virtual void initDateTimeEdit(GLDDateTimeEdit *dateTimeEdit, const QModelIndex &index);

    virtual void itemViewSelected(QComboBox *comboBox, const QModelIndex &index, const QModelIndex &itemIndex) const;
public:
    /*!
     *@enum: GDataType
     *@brief {�������ͣ���ǰ��ΪHTML�������ṩ֧��}
     *@author Gaosy
     *@date 2012.9.10
     */
    enum GDataType
    {
        GTypeNormal,
        GTypeHTML,
        GRichText,
        GDiaSymbol,
        GMeterSymbol
    };

    /**
     * @brief ͼƬ��ʾ��ģʽ
     * @see QImage::scaled
     */
    enum GAspectRatioMode
    {
        IgnoreAspectRatio,  //���Գ���ȣ�ֻΪ������
        KeepAspectRatio,    //���ֱ�������(ͼƬ��ȫչʾǰ���¾����ܵ�����)
        KeepAspectRatioByExpanding,//���ֱ�������(ͼƬֻ����һ��ά�ȳ������ɵĳߴ�)
        KeepAspectPixel    //����ԭ��С
    };

    /*!
     *���ӵĻ���
     *@param[in]  painter
     *@param[in]  option
     *@param[in]  index
     *@return ��
     *@see �μ�QItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
     *                              const QModelIndex &index) const;
     */
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

    QSize sizeHint(
            const QStyleOptionViewItem &option, const QModelIndex &index) const;

    /*!
     *���ر༭��ʽ��Ҫ�Ŀؼ�
     *@param[in]  parent
     *@param[in]  option
     *@param[in]  index
     *@return QWidget*
     */
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    /*!
     *����༭״̬ʱ����ʼ���ؼ���ֵ
     *@param[in]  editor  ���ӱ༭��Ҫ�Ŀؼ�
     *@param[in]  index
     *@return ��
     */
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    /*!
     *�˳��༭״̬ʱ�����༭�ؼ��е�ֵ�ύ
     *@param[in]  editor  ���ӱ༭��Ҫ�Ŀؼ�
     *@param[in]  model   TableView��model
     *@param[in]  index
     *@return ��
     */
    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const;

    /*!
     *���ñ༭�ؼ���λ�ü�Geometry��Ϣ
     *@param[in]  editor  ���ӱ༭��Ҫ�Ŀؼ�
     *@param[in]  model   TableView��model
     *@param[in]  index
     *@return ��
     */
    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;

    virtual QVariant currentEditorData(const QModelIndex &index, QWidget *editor);

    QModelIndex dataIndex(const QModelIndex &index) const;
    QModelIndex treeIndex(const QModelIndex &index) const;

    static GEditStyle editStyleByVariantType(QVariant::Type vType);

    inline QWidget *curEditor()
    {
        return m_curEditor;
    }

    /**
     * ���ñ༭��ʽesDropDown�Ƿ�ѡ��ֵ�����˳��༭״̬: Ĭ��ֵtrue
     * @brief setComboBoxConvenient
     * @param convenient
     */
    inline bool isComboBoxConvenient() const
    {
        return m_comboBoxConvenient;
    }
    inline void setComboBoxConvenient(bool convenient)
    {
        m_comboBoxConvenient = convenient;
    }

    void setIsTextEllipse(bool value);
    inline bool isTextElided() const
    {
        return m_isTextEllipse;
    }
    /**
     * @brief �жϵ�ǰtableView�Ƿ��ڱ༭״̬
     * @return
     */
    bool isEditing();
    inline void setCurrTreeEditting(const QModelIndex &value)
    {
        m_currTreeEditing = value;
    }
    inline QModelIndex currTreeEditting()
    {
        return m_currTreeEditing;
    }    /*!
     *���Ƹ��ӱ���
     *@param[in]  painter
     *@param[in]  option
     *@param[in]  index
     *@return ��
     *@see �μ�QItemDelegate::drawBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
     */
    virtual void drawBackground(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    /*!
     * \brief �����ı�����ʱ�����з�ʽ
     * \param wrap
     */
    inline void setTextWrapMode(QTextOption::WrapMode wrap)
    {
        m_wrapMode = wrap;
    }
    inline QTextOption::WrapMode textWrapMode()
    {
        return m_wrapMode;
    }

protected:
    QRect textLayoutBounds(const QStyleOptionViewItem &option) const;
    bool isBoolCell(const QModelIndex &index) const;

    bool eventFilter(QObject *object, QEvent *event);

    template<typename T>
    bool commitIfCanElseSelectAll(QEvent *event, QWidget *editor, bool &state);

    bool commitDataAndCloseEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint = NoHint);

    /*!
     * \brief cursorMoveTextEndByEndKey,ʹ��Ctrl + End���������λ���ƶ������
     * \param editor
     */
    void cursorMoveTextEndByEndKey(QWidget *editor);
    /*!
     * \brief cursorMoveTextEnd�����ڽ��������editor���������һ��λ��
     * \param editor
     * \return
     */
    bool cursorMoveTextEnd(QWidget *editor);
    /*!
     * \brief cursorPosInsertANewLine
     * \param editor
     * \return true:move to a new line successful, false:cursor can`t movable control,or moving failed
     */
    bool cursorPosInsertANewLine(QWidget *editor);
    QStyleOptionViewItem setOptions(const QModelIndex &index,
                                    const QStyleOptionViewItem &option) const;
Q_SIGNALS:
    void onQueryImageAspectRatioMode(const QModelIndex &index, GlodonDefaultItemDelegate::GAspectRatioMode &ratioMode) const;
    void onQueryFloatOrDoubleViewFormat(const QModelIndex &index, QString &text) const;
    void onQueryIndexDataType(const QModelIndex &index, GlodonDefaultItemDelegate::GDataType &dataType) const;
    void onCommitDataAndCloseEditor();
    void commitData(QWidget *editor, bool &canCloseEditor);
    void closeEditor(QWidget *editor, bool &canCloseEditor, QAbstractItemDelegate::EndEditHint hint = NoHint);

protected:
    /**
     * ���ô����editor�е��ı���ȫѡ
     * @brief setTextAllSelected
     * @param editor
     */
    bool setTextAllSelected(QWidget *editor);
    /**
     * ʧȥ�����˳��༭״̬: Ĭ��ֵfalse
     * @brief hideEditOnExit
     * @return
     */
    inline bool closeEditorOnFocusOut() const
    {
        return m_bCloseEditorOnFocusOut;
    }
    inline void setCloseEditorOnFocusOut(bool value, bool ignoreActiveWindowFocusReason = false)
    {
        m_bCloseEditorOnFocusOut = value;
        m_bIgnoreActiveWindowFocusReason = ignoreActiveWindowFocusReason;
    }

    /*!
     * \brief �����Ƿ�ʹ��comboBox���Զ���ʾ���ܣ�Ĭ��Ϊʹ��
     * \return
     */
    inline bool useComboBoxCompleter() const
    {
        return m_bUseComboBoxCompleter;
    }
    inline void setUseComboBoxCompleter(bool value)
    {
        m_bUseComboBoxCompleter = value;
    }
    /**
     * ѡ�е�Ԫ��ʹ�û�ɫ
     * @brief useBlendColor
     * @return
     */
    inline bool useBlendColor() const
    {
        return m_bUseBlendColor;
    }
    inline void setUseBlendColor(bool value)
    {
        m_bUseBlendColor = value;
    }
    /**
     * ѡ�е�Ԫ��ı�����ɫ
     * @brief useBlendColor
     * @return
     */
    inline QColor selectedCellBackgroundColor() const
    {
        return m_oSelectedCellBackgroundColor;
    }
    inline void setSelectedCellBackgroundColor(QColor value)
    {
        m_oSelectedCellBackgroundColor = value;
    }
    /**
     * @brief �ж�tableview�Ƿ��ڻس�����״̬
     * @param value
     */
    inline bool isEnterJump() const
    {
        return m_enterJump;
    }
    inline void setIsEnterJump(bool value)
    {
        m_enterJump = value;
    }

    inline bool isEnterJumpPro() const
    {
        return m_enterJumpPro;
    }
    inline void setIsEnterJumpPro(bool value)
    {
        m_enterJumpPro = value;
    }
    /*!
     * \brief setIncludeLeading������ʾ����ʱ�Ƿ�����м��
     * \param value
     */
    inline bool isIncludeLeading() const
    {
        return m_includingLeading;
    }
    inline void setIncludeLeading(bool value)
    {
        m_includingLeading = value;
    }
    /*!
     *���Ƹ��ӽ���״̬
     *@param[in]  painter
     *@param[in]  option
     *@param[in]  rect
     *@return ��
     *@see �μ�QItemDelegate::drawFocus(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect) const
     */
    virtual void drawFocus(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect) const;

    inline void setCurEditor(QWidget *value)
    {
        m_curEditor = value;
    }

    void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option,
                     const QRect &rect, const QString &text, const QModelIndex &index) const;

private:
    void paintOther(QPainter *painter,
                    const QStyleOptionViewItem &option,
                    const QModelIndex &index) const;
    void paintDouble(QPainter *painter,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) const;
    void paintImg(QPainter *painter,
                  const QStyleOptionViewItem &option,
                  const QModelIndex &index) const;
    void paintBool(QPainter *painter,
                   const QStyleOptionViewItem &option,
                   const QModelIndex &index) const;
    void paintColor(QPainter *painter,
                    const QStyleOptionViewItem &option,
                    const QModelIndex &index) const;
    void paintGType(QPainter *painter,
                    const QStyleOptionViewItem &option,
                    const QModelIndex &index, GDataType type) const;

    bool setTreeViewModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    bool setDropDownWindowModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    bool setMonthCalendarModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index, QVariant::Type vType) const;

    QWidget *doCreateEditor(QWidget *parent,
                            const QStyleOptionViewItem &option,
                            const QModelIndex &index);

    void createLineEditEditor(QWidget *parent, bool bReadOnly);
    void createTreeViewEditor(QWidget *parent, QModelIndex &dIndex, bool bReadOnly);
    void createDropDownWindowEditor(QWidget *parent, QModelIndex &dIndex, bool bReadOnly, GEditStyle eEditStyle);
    void createMonthCalendarEditor(QWidget *parent, QModelIndex &dIndex, QVariant::Type vType);
    void createColorListEditor(QWidget *parent, QModelIndex &dIndex, bool bReadOnly);
    void createFontListEditor(QWidget *parent);
    void createLineWidthEditor(QModelIndex &dIndex, QWidget *parent);

    template<class T>
    void createEllipsisEditor(QWidget *parent, QModelIndex &dIndex, bool bReadOnly)
    {
        T *ellipsis = new T(parent);

        m_curEditor = ellipsis;

        initEllipsisButtonEdit(ellipsis, dIndex);
        ellipsis->setEditable(!bReadOnly);
        ellipsis->setHasBorder(false);
    }

    /**
     * @brief esSimple��esUpDown�����ֱ༭��ʽ�����Ķ���QSpinBox���ƿؼ�
     * @param parent
     * @param option
     * @param index
     * @param vType ��������
     * @param isUpDown �Ƿ����������ÿ�
     * @param numberRightAlign
     * @return
     */
    void createSpinBox(QWidget *parent,  const QModelIndex &index, const QStyleOptionViewItem &option,
                       QVariant::Type vType, bool bReadOnly, bool &numberRightAlign);


    void drawEditStyleDraw(QPainter *painter, QStyleOptionViewItem &option, QRect &rect) const;
    /**
     * @brief ��QItemDelegate�е�drawDisplayһ����ȥ���˴�style�л�ȡmargin����
     * @param painter
     * @param option
     * @param rect
     * @param text
     */
    void doDrawDisplay(
            QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect,
            const QString &text, const QModelIndex &index) const;
    /**
     * @brief ����role�����Խ��ߺͷ��Խ���
     * @param painter
     * @param rect
     * @param index
     */
    void drawDiagonal(QPainter *painter, const QRect &rect, const QModelIndex &index) const;

    /**
     * @brief ������ʾ�����иߣ�������ʾ�ı�������
     * @param textRect  ��ʾ����
     */
    int calculateLineCount(const QRect &textRect) const;

    /**
     * @brief text���������У������и߼�option����text����Ӧ��ʾ����
     * @param[out]  textLineCount   text��ʾ������
     * @param[in]   rectLineCount   ��ʾ�����ܹ���ʾ������
     * @param[in]   textRect        ��ʾ����
     * @param[in]   text            ��ʾ������ִ�
     * @param[in]   option          �����ĸ�ʽ(�Ƿ���ʾ...��)
     */
    QString elidedText(int &textLineCount, int rectLineCount, const QRect &textRect, const QString &text, const QStyleOptionViewItem &option) const;
    /**
     * @brief text���������У������и߼�option����text����Ӧ��ʾ����
     * @param[in] textRect  ��ʾ����
     * @param[in] text      ��ʾ������ִ�
     * @param[in] option    �����ĸ�ʽ(�Ƿ���ʾ...��)
     */
    QString elidedTextWithoutLineFeed(const QRect &textRect, const QString &text, const QStyleOptionViewItem &option) const;
    /**
     * @brief text�������У������и߼�option����text����Ӧ��ʾ����
     * @param[in] textRect  ��ʾ����
     * @param[in] text      ��ʾ������ִ�
     * @param[in] option    �����ĸ�ʽ(�Ƿ���ʾ...��)
     */
    QString elidedTextWithLineFeed(const QRect &textRect, const QString &text, const QStyleOptionViewItem &option) const;

    inline bool checkSetModelData() const
    {
        return m_checkSetModelData;
    }
    inline void setCheckSetModelData(bool value)
    {
        m_checkSetModelData = value;
    }
    /**
     * @brief ���ݸ�����������������Delegate��TableView������ʱ������
     * @param index
     * @param font
     * @param factor
     * @return
     */
    QFont zoomFont(QModelIndex index, QFont font, double factor) const;
    /**
     * @brief ��ComboBox����QCompleter
     * @param comboBox
     * @param index
     */
    void initComboBoxCompleter(QComboBox *comboBox, QModelIndex index);

    /*!
     * \brief ���ݱ༭��ʽ����ȡ��Ӧ�༭��ʽ��ռ����
     * \param index
     * \param rect
     * \return
     */
    QRect editStyleRect(QModelIndex index, QRect rect);
    bool isInSubControlRect(QModelIndex index, QPoint pos);
    void clickSubControl(QModelIndex index);

    void adjustDecorationAlignment(const QModelIndex &index, QStyleOptionViewItem &opt) const;

private:
    bool filterKeyPress(QWidget *editor, QEvent *event);
    bool filterReturnKeyPress(QWidget *editor, QKeyEvent *keyEvent);
    bool filterRightKeyPress(QWidget *editor, QKeyEvent *keyEvent);
    bool filterUpKeyPress(QWidget *editor, QKeyEvent *keyEvent);
    // �ع�filterKeyPress
    void dealWithEscapeKeyPress(QWidget *editor);
    bool dealWithTabKeyPress(QWidget *editor);
    bool dealWithBackTabPress(QWidget *editor);
    template<typename T>
    QVariant compareDataByType(QVariant oldData, T newData) const;
    QVariant compareDataByType(QVariant oldData, double newData) const;
    // �ع�EventFilter
    bool dealWithLoseFocus(QEvent *event, QWidget *pEditor);
    bool dealWithShortCutOverride(QEvent *event);

    // �ع��Զ��и�
    QRect calcRectByData(
            const QStyleOptionViewItem &option, const QModelIndex &index, int role) const;
    QRect textRectangle(
            const QRect &rect, const QFont &font, const QString &text) const;

    void innerDoLayout(
            const QStyleOptionViewItem &option, QRect *checkRect, QRect *pixmapRect, QRect *textRect,
            bool hint) const;
    void adjustRectByTextMargin(const QModelIndex &index, const QStyleOptionViewItem &opt, bool isIncludeMargin, QRect &rect) const;

private Q_SLOTS:
    void doComboBoxActivated(int index);

private:
    Q_DECLARE_PRIVATE(GlodonDefaultItemDelegate)

    mutable QModelIndex m_currTreeEditing;
    QWidget *m_curEditor;
    GlodonAbstractItemView *m_pTable;
    mutable int m_oComboBoxCurIndex;
    static Qt::Alignment s_originalDisplayAlignmentForCurrentItem; //���ڱ���displayAlignment
    double m_factor;//��������
    QEvent *m_closeEditEvent;//�����˳��༭״̬��event

    bool m_comboBoxConvenient;//combo����չ������
    bool m_bCloseEditorOnFocusOut;
    bool m_inCommitData;
    bool m_inSetModelData; //setModelDataʱ���ٵ���setEditorData��������ʼ�����
    bool m_checkSetModelData;//setModelData�Ƿ�ɹ�
    static bool s_digitCurrentItem;
    bool m_bUseBlendColor;
    bool m_includingLeading; //draw����ʱ�Ƿ����leading(�о�)
    bool m_enterJump;
    bool m_enterJumpPro;
    bool m_isTextEllipse;
    bool m_bRepeatCommit; //������ʧȥ�����˳��༭״̬��ͨ�����쳣�ķ�ʽУ�����ݲ��Ϸ�ʱ��������ظ��ύ����
    bool m_bCanHideEidtOnExit;
    bool m_bIgnoreActiveWindowFocusReason;
    bool m_bUseComboBoxCompleter;//�����Ƿ�ʹ��comboBox���Զ���ʾ����
    QTextOption::WrapMode m_wrapMode;

    QColor m_oSelectedCellBackgroundColor; //ѡ������ı�����ɫ
    mutable QVariant m_oDisplayData;

    friend class GlodonAbstractItemView;
    friend class GlodonAbstractItemViewPrivate;
    friend class GLDTableView;
    friend class GLDTableViewPrivate;
};

#endif // GLDDEFAULTITEMDELEGATE_H
