/****
 * @file   : GLDShellComboBoxEx.h
 * @brief  : ����������GLDShellComboBox
 *           ��Ҫע��cpp�ļ��е�strShowComboBox��strComboBoxProp��strIsLineEdit
 *           ���������Ƿ�����ʾ��Ĭ��Ϊ������ʾ��ʹ��setEditToLineEdit�������Ը���
 *           ���������Ƿ���ʾ�༭��ͼ�꣬Ĭ��Ϊ����ʾ
 *           
 *           �����Զ���ͼ�꣬��QSS��ע���У��������ַ�����ͷ�������϶�Ӧͼ���·���������
 *           "QFileIconProviderComputer" 
 *           "QFileIconProviderDesktop" 
 *           "QFileIconProviderTrashcan" 
 *           "QFileIconProviderNetwork" 
 *           "QFileIconProviderDrive" 
 *           "QFileIconProviderFolder" 
 *           "QFileIconProviderFile";
 *           
 *           ͬ���ķ��������Զ����ļ��б��е�������ɫ����RootColor����Ӧ��һ���ڵ㣨���̣���
 *           "OthersColor"��Ӧʣ��Ľڵ�
 *
 * @date   : 2014-08-16
 * @author : chenyp-a
 * @remarks:
 ****/
#ifndef GLDSHELLCOMBOBOXNOLINEICON_H
#define GLDSHELLCOMBOBOXNOLINEICON_H

#include <QMap>
#include <QFileIconProvider>

#include "GLDShellWidgets.h"
#include "GLDTextEdit.h"
#include "GLDFileSystemModel.h"
#include "GLDWidget_Global.h"

class GLDShellTreeViewEx;
class GLDFileSystemModelEX;
class GLDShellComboBoxItemDelegate;
class GLDFileIconProvider;
class GLDShellComboBoxEx;

class GLDWIDGETSHARED_EXPORT GLDShellComboBoxItemDelegate : public QStyledItemDelegate
{ 
    Q_OBJECT
public:
    explicit GLDShellComboBoxItemDelegate(const QString &rootPath = QString(), QWidget *parent = 0);
   
public:
    QPixmap pixmap(const QModelIndex &index)const;
    void setTreeView(GLDShellTreeViewEx *treeView);
    void setFileSystemModel(GLDFileSystemModelEX *model);
    void setExpandedIndex(const QModelIndex &index);
    bool isParentExpandedRecently(const QModelIndex &index) const;
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

protected:
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
    
private:
    QModelIndex findLonelyExpanded(const QModelIndex &root);    
    QPixmap icon(const QModelIndex &index);

private slots:
    void doAfterExpanded(const QModelIndex &index);
    void doAfterCollapsed(const QModelIndex &index);

private:
    GLDShellTreeViewEx *m_treeView;
    GLDFileSystemModelEX *m_model;
    QModelIndex m_indexExpanded;
};

class GLDWIDGETSHARED_EXPORT GLDFileIconProvider : public QFileIconProvider
{ 
public:
    GLDFileIconProvider();
    virtual ~GLDFileIconProvider();

public:
    virtual QIcon icon(IconType type) const;
    virtual QIcon icon(const QFileInfo & info) const;    
    void loadIcon(QMap<QFileIconProvider::IconType, QString> mapURL);
    void loadSetting(const QString &setting);
    
private:
    QMap<QFileIconProvider::IconType, QIcon> m_map_icon;
};

class GLDWIDGETSHARED_EXPORT GLDFileSystemModelEX : public GLDFileSystemModel
{ 
    Q_OBJECT
public:
    explicit GLDFileSystemModelEX(bool includingFile = false, QObject *parent = 0);
    ~GLDFileSystemModelEX();
    
public:
    QVariant data(const QModelIndex &index, int role) const;    
    QIcon fileIcon(const QModelIndex &index) const;    
    QColor fileNameColor(const QModelIndex &index) const;    
    void setFontColor(const QString &setting);    
    inline void setDelegate(GLDShellComboBoxItemDelegate *delegate){ m_delegate = delegate; }

protected:
    GLDFileSystemModelEX(const QStringList &nameFilters, QDir::Filters filters,
              QDir::SortFlags sort, QObject *parent = 0);
    GLDFileSystemModelEX(GLDFileSystemModelPrivate &model, QObject *parent = 0);
    
private:
    QColor m_colorRoot;
    QColor m_colorOthers;
    GLDShellComboBoxItemDelegate *m_delegate;    
    GLDFileIconProvider *m_pIconProvider;

    Q_DECLARE_PRIVATE(GLDFileSystemModel)
};

/**
 * @brief 
 *
 * @class GLDShellComboBoxEx
 */
class GLDWIDGETSHARED_EXPORT GLDShellComboBoxEx : public GLDShellComboBox
{ 
    Q_OBJECT
public:
    explicit GLDShellComboBoxEx(const QString &rootPath = QString(), QWidget *parent = 0);
    
public:
    void init(const QString &rootPath);
    void setHasBorder(bool bHasBorder);
    void setEditProperty(bool bShow);
    void setFileModel(GLDCustomFileSystemModel *model);

    /*!
     * \brief setShellListView
     * \param ����������GLDShellListView
     *@warning ֻ�ܹ���һ��list
     */
    void setShellListView(GLDShellListView *list);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject *object, QEvent *event);
    void autoSetContainerHeight();
    void keyPressEvent(QKeyEvent *event);
    void updateEditFieldGeometry();

signals:
    void onHide();    
    void shouldShowPopup(bool &value);    
    void afterPopupShowed();//�źţ���������ʾ    
    void afterPopupHid();//�źţ�����������    
    void cursorPositionChanged();    
    void expanded(const QModelIndex &index);    
    void collapsed(const QModelIndex &index);

private slots:
    void onSignalOnHide();    
    void onShouldShowPopup(bool &value);    
    void doAfterEditCursorChanged();
    void doAfterExpanded(const QModelIndex &index);    
    void doAfterCollapsed(const QModelIndex &index);

private:
    void initConnection();
    void installEventFilters();
    void initShadow();
    void initFileModel(const QString &rootPath);
    void initTreeView(QModelIndex pathIndex);
    void initTreeViewIndentation();
    void initDelegate(GLDShellTreeViewEx *pTreeView);
    void initPopupFlags();
    
private:
    bool m_bIsShow; /** �������Ƿ���ʾ*/
    bool m_bIsLineEdit; /** �༭���Ƿ�Ϊ�б༭��*/
    bool m_bIsShowIcon;/** �Ƿ���ʾ�༭��ͼ��*/
    bool m_bIsDefaultIcon;/** �Ƿ�ʹ��Ĭ��ͼ��*/
    bool m_bIsDrag;
    bool m_bIsPopMove;
    int m_nCanSetCursor;
    bool m_bHasShadow;
    QString m_text;
    GLDShellComboBoxItemDelegate *m_delegate;
};

#endif // GLDSHELLCOMBOBOXNOLINEICON_H
