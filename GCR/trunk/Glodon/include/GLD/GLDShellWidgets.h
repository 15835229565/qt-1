#ifndef GLDSHELLTREEVIEW_H
#define GLDSHELLTREEVIEW_H

#include <QListView>
#include <QTreeView>
#include <QHeaderView>
#include "GLDWidget_Global.h"
#include "GLDListView.h"
#include "GLDWindowComboBox.h"
#include "GLDAbstractItemView.h"

class QDirModel;
class GLDShellComboBox;
class GLDShellListView;
class QFileSystemModel;
class GLDCustomFileSystemModel;

class GLDWIDGETSHARED_EXPORT GLDDirFilter
{
public:
    enum DirName{
        RelativeName = 0,
        AbsoluteName = 1
    };

    enum ISDIR{
        ISFOLDER = 0,
        ISFILE = 1,
        NOITEMSELECTED = 2
    };

    enum SLASHTYPE{
        FORWORDSLASH = 0,   //��б��( slash '/' )
        BACKSLASH = 1       //��б��( backslash '\')
    };

    //��Ҫ��ΪTree�ͣ��ݿ��Ÿ�������GLDShellTreeViewʹ��
    enum TreeRootPolicyFlag{
        ROOTVISIBLESINGLETON = 0x01, //��ʾ��ǰ����Ϊroot�Ķ�Ӧ���ļ�/Ŀ¼���ڵ���һ��Ŀ¼����������ʾ��Ŀ¼���ֵ�Ŀ¼
        HIDE = 0x02,                 //Qt��Ĭ����Ϊ������һ�е���Ϊ����
        ROOTWITHCURRENT = 0x04,      //root����current������һ�е���Ϊ����
        ROOTSTEADY = 0x08            //root������current,��setRootIndexӰ��
    };
    Q_DECLARE_FLAGS(TreeRootPolicy, TreeRootPolicyFlag)

    virtual void setNameFilters(const QStringList &filters) = 0;
    virtual QStringList nameFilters() const = 0;
    virtual QString filePathByType(const QModelIndex &currentIndex, DirName dirType) const;
    virtual ISDIR getTheIndexDirType(const QModelIndex &index, const GLDCustomFileSystemModel *pModel) const;
protected:
    virtual void doSetNameFilters(QAbstractItemModel *model, const QStringList &filters);
    virtual QStringList doNameFilters(QAbstractItemModel *model) const;
};

class GLDWIDGETSHARED_EXPORT GLDShellTreeView : public QTreeView, public GLDDirFilter
{
    Q_OBJECT
public:
    explicit GLDShellTreeView(QWidget *parent = 0);
    ~GLDShellTreeView();

    void setModel(QAbstractItemModel *model);

    /*!
     * \brief setNameFilters ����Ҫ��ʾ���ļ���׺�б����������Զ����˵�
     * \param filters ������������"*.exe"���ַ���,�����������Ƶ�������
     *@warning ������setModel��model����Ϊ������QFielSystemModel�������͵�ʵ������ʱ���˷�������Ч����Ϊ����δ����ġ�
     *@see GLDShellComboBox::setNameFilters(const QStringList &filters)
     */
    void setNameFilters(const QStringList &filters);

    /*!
     * \brief nameFilters ��õ�ǰ���ļ����˺�׺�б�
     * \return
     *@see GLDShellComboBox::nameFilters()
     */
    QStringList nameFilters() const;

    /*!
     * \brief currentPath
     * \param dirType: RelativeName:���·����һ��ָ�ļ��������ļ�������������·����AbsoluteName:����·����,����·��
     * \return ·����,���û��ѡ�У��򷵻ص�ǰ�ĸ����·��
     */
    QString currentPath(DirName dirType = AbsoluteName, SLASHTYPE xieGang = BACKSLASH) const;
    /*!
     * \brief isCurrentPathDir
     * \return ISFOLDER:��ǰѡ�е����ļ��С�ISFILE:��ǰѡ�е����ļ���NOITEMSELECTED:��ǰδѡ����
     */
    ISDIR isCurrentPathDir() const;

    /*!
     * \brief setRootWithCombo ��tree��shellcomboBox����ʱ�������Ծ���root�Ƿ����combo������ѡ�е�����仯
     * \param withCombo
     */
    void setRootWithCombo(bool withCombo) { m_bTreeRootWithCombo = withCombo; }

    bool rootWithCombo() const { return m_bTreeRootWithCombo; }

    /*!
     * \brief setSingleRoot ����delphi�汾�ĵ�һ�ĸ������ʽ����ʾ��ʽ
     * \param singleRoot
     */
    void setSingleRoot(bool singleRoot);
    bool singleRoot() const;

    void setRootIndex(const QModelIndex &index);
    void setRootPath(const QString &path);

    inline bool neverChangeRoot() { return m_neverChangeRoot; }
    inline void setNeverChangeRoot(bool value) { m_neverChangeRoot = value; }

    void doItemsLayout();

    /*!
     * \brief ���õ�ǰtree�Ľ��㣬�ɴ�������
     * \param index
     */
    void setCurrentIndexPro(const QModelIndex &index);

signals:
    void itemJustBeSelected(const QModelIndex &index);
    void itemJustBeDoubleClicked(const QModelIndex &index);
    void currentItemJustChanged(const QModelIndex &current, const QModelIndex &previous);

public slots:
    void adjustColumnWidth(const QModelIndex &);

protected slots:
    void upToParentDir(const QModelIndex &parentDirIndex);
    void slotExpand(QModelIndex index);
    void slotCollapse(QModelIndex index);
    void setCurrentIndex(const QModelIndex &index);
    void shellTreeOwnScrollTo();
protected:
    void mousePressEvent(QMouseEvent *event);
    void currentChanged(const QModelIndex &current, const QModelIndex &previous);
    void showEvent(QShowEvent *e);

    explicit GLDShellTreeView(bool popup, GLDShellComboBox *combo);
    virtual void setAssociatedItemView(QAbstractItemView *view);
    bool isAssociatedAComboBox() const { return NULL != m_comboBox; }

    QString getIndexFileName(QModelIndex pressedIndex);
private:
    void makePreBuddiesVisible();
    void hideBuddiesAndInsertList(const QModelIndex &visibleChild, const QModelIndex &par, int buddyCount);
    void makesureBuddyContainerExist();
    void makeRootParentAsRootAndHideBuddies();

    void setTreeRootMode(TreeRootPolicy rootPolicy = TreeRootPolicy(5));
    inline TreeRootPolicy treeRootMode() { return m_treeRootPolicy; }
private:
    DirName m_getPathType;
    GLDShellComboBox *m_comboBox;
    int m_iFirstShow;
    TreeRootPolicy m_treeRootPolicy;
    bool m_bTreeRootWithCombo;       //��ʱ�����������Թ���
    bool m_bSelfClicked;
    bool m_bComboClickeSignal;
//    QDirModel *m_pDirModel;
    GLDCustomFileSystemModel *m_pDirModel;//m_pFileModel;
    QList<QModelIndex> *m_pHiddenBuddies;   //for VISIBLESINGLETON ״̬
    QList<QVariant> *m_pHiddenBuddys;       //for VISIBLESINGLETON ״̬
    QModelIndex m_preRoot;                  //for VISIBLESINGLETON ״̬
    bool m_bSingleRoot;
    bool m_bUsingVariant;
    bool m_neverChangeRoot; //ʼ�ղ��ı���ڵ�
private:
    Q_DISABLE_COPY(GLDShellTreeView)
    friend class GLDShellComboBox;
    typedef QTreeView inherit;
};

class GLDWIDGETSHARED_EXPORT GLDShellComboBox : public GLDWindowComboBox, public GLDDirFilter
{
Q_OBJECT
public:
    explicit GLDShellComboBox(const QString &rootPath = QString(), QWidget *parent = 0);
    virtual ~GLDShellComboBox();

public:
    /*!
     * \brief setShellListView
     * \param ����������GLDShellListView
     *@warning ֻ�ܹ���һ��list
     */
    virtual void setShellListView(GLDShellListView *list);

    /*!
     * \brief setShellTreeView
     * \param ����������GLDShellTreeView
     *@warning ֻ�ܹ���һ��tree
     */
    void setShellTreeView(GLDShellTreeView *tree);

    /*!
     * \brief setCustomPath �����û�Ŀ¼����ָ�����ļ���·����Ҳ�ɲ����ã�Ĭ������������
     * \param rootPath
     *@note !! 2014.1.23 ֱ��ת����setCurrentPath
     */
    void setCustomPath(const QString &rootPath);

    /*!
     * \brief setCurrentPath ���õ�ǰ�û�Ŀ¼����ָ����ǰҪ��λ�����ļ���·��
     * \param currentPath
     *@warning currentPath��Ҫ��setCustomPath���õ�rootPath�¡������벻Ҫ����setCustomPath
     *@see �μ�GLDShellComboBox::setCustomPath(QString rootPath)
     */
    void setCurrentPath(const QString &currentPath);

    /*!
     * \brief setCurrentFile ���õ�ǰ�û��ļ�����ָ����ǰҪѡ�е��ļ������ҹ�����tree��λ�����ļ������ļ��С��ļ�����ѡ��״̬
     * \param currentFilePath ��Ҫ����·��
     *@note ֱ�ӵ���setCurrentFile()���벻Ҫ��setCurrentPath()���ú��ٵ���setCurrentFile()��
     */
    void setCurrentFile(const QString &currentFilePath);

    /*!
     * \brief setNameFilters    �����ļ���׺������
     * \param filters
     *@warning ������List��Tree����ʹ�ô˹���,ֻ��˴�����һ�Ρ�
     *@see GLDShellListView::setNameFilters(const QStringList &filters)
     */
    void setNameFilters(const QStringList &filters);    
    QStringList nameFilters() const;

    /*!
     * \brief setDirNameType ����combo�ı༭���е��ļ����Ƿ��վ���·����ʾ
     * \param type
     */
    void setDirNameType(DirName type);
    DirName dirNameType() const;

    /*!
     * \brief getPathInEdit ��ȡEdit����ʾ��·��������·�����Ķ�����Ϊ��Ч�ģ��򷵻�����tree�ж�Ӧ����Ч·��
     * \param type ָ��Ҫ��õ�·�������͡� xieGang ָ��Ҫ��õ�·���е�б������
     * \return
     */
    QString getCurrentPath(DirName type = AbsoluteName, SLASHTYPE xieGang = BACKSLASH) const;

    /*!
     * \brief getIndexFilePath
     * \param index ָ����QModelIndex���뵱ǰcombo������tree��listȡ�õ�QModelIndex���ɡ���ֻҪ��ͬһ��GLDFileSystemModel�µ�
     * modelindex����
     * \param xieGang
     * \return
     */
    QString getIndexFilePath(const QModelIndex &index, SLASHTYPE xieGang = BACKSLASH) const;

    QString text() const { return getCurrentPath(); }

    void setFileModel(GLDCustomFileSystemModel *model);

    /*!
     * \brief ȡ�����ʱ����root������
     * \param view�ⲿ�󶨵Ŀؼ�
     * \return
     */
    void disconnectClick(QAbstractItemView *view);
protected slots:
    void synToComboAndTree(QModelIndex clickedIndex);
    void synToComboAndList(QModelIndex clickedIndex);

protected:
    virtual void doAfterResize();
    QIcon itemIcon(const QModelIndex &index, const QAbstractItemModel *model);
    void setEditTextByIndex(QModelIndex curIndex);

    void expandTreeTo(QModelIndex path);
    void locateListTo(QModelIndex path);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);

public:
    void setChildrenRootIndex(QModelIndex path);
    void init(const QString &rootPath);

    //popup�е�tree
    GLDShellTreeView *m_popupShellTree;
    //���������������Ŀؼ�
    GLDShellListView *m_shellListView;
    GLDShellTreeView *m_shellTreeView;
    GLDCustomFileSystemModel *m_pFileModel;
    bool m_showFullPath;
    bool m_currentPathSetted;

private:
    Q_DISABLE_COPY(GLDShellComboBox)
    friend class GLDShellTreeView;
};

class GLDWIDGETSHARED_EXPORT GLDShellHeaderView : public QHeaderView
{
    Q_OBJECT
public:
    explicit GLDShellHeaderView(QWidget *parent = 0);
    ~GLDShellHeaderView();
    void setSection0AutoResize();
    void setSectionsHiddenExcept0();

private:
    Q_DISABLE_COPY(GLDShellHeaderView)
};

/*!
 *@brief The GLDShellListView class
 *@note :ʹ�û����slot��Ϊѡ����˫�����źţ��������Լ��Ĳ�
 */
class GLDWIDGETSHARED_EXPORT GLDShellListView : public GLDListView, public GLDDirFilter
{
    Q_OBJECT
public:
    explicit GLDShellListView(QWidget *parent = 0);
    ~GLDShellListView(){freeAndNil(commentFrame);}

    /*!
     * \brief setCustomPath
     * \param rootPath ָ������·��
     */
    virtual void setCustomPath(QString rootPath);

    /*!
     * \brief currentPath
     * \param dirType: RelativeName:���·����һ��ָ�ļ��������ļ�������������·����AbsoluteName:����·����,����·��
     * \return ·����,���û��ѡ�У��򷵻ص�ǰ�ĸ����·��
     */
    QString currentPath(DirName dirType = AbsoluteName, SLASHTYPE defType = BACKSLASH) const;

    /*!
     * \brief isCurrentPathDir
     * \return ISFOLDER:��ǰѡ�е����ļ��С�ISFILE:��ǰѡ�е����ļ���NOITEMSELECTED:��ǰδѡ����
     */
    ISDIR isCurrentPathDir() const;

    /*!
     * \brief upToParentIndex
     * \return ���ϲ��ƶ�,�������Ƿ�ɹ�
     */
    bool upToParentDir();

    /*!
     * \brief setHintBeShown �����Ƿ���ʾ��ʾС��Ĭ����ʾ
     * \param show
     */
    void setHintBeShown(bool show){m_bShowHint = show;}

    bool hintBeShown() const{return m_bShowHint;}

    /*!
     * \brief setHintExistTime ������ʾС����Զ���ʧʱ�䣬��λ:�롣Ĭ��2��
     * \param seconds
     */
    void setHintExistTime(int seconds){m_hintExistSeconds = qMax(1, seconds);}

    int hintExistTime() const{return m_hintExistSeconds;}

    /*!
     * \brief setOpenFileWhileDoubleClicked �����Ƿ���˫���ļ�ʱ�򿪡�Ĭ�Ϲر�
     * \param openFile
     */
    void setOpenFileWhileDoubleClicked(bool openFile){m_bOpenFileWhileDblClk = openFile;}

    bool openFileWhileDoubleClicked() const{return m_bOpenFileWhileDblClk;}

    /*!
     * \brief setNameFilters ����Ҫ��ʾ���ļ���׺�б�
     * \param filters ������������"*.exe"���ַ���
     *@warning ������setModel��model����Ϊ������QFielSystemModel�������͵�ʵ������ʱ���˷�������Ч����Ϊ����δ����ġ�
     */
    void setNameFilters(const QStringList &filters);

    /*!
     * \brief nameFilters ��õ�ǰ���ļ����˺�׺�б�
     * \return
     */
    QStringList nameFilters() const;

    /*!
     * \brief ���õ�ǰ·��,Ϊ�գ�����ת�����ڵ� add by hanll-a
     * \return
     */
    void setCurrentPath(const QString &path);

signals:
    void upToDir(const QModelIndex &parentDirIndex);
    void rootIndexChanged(const QModelIndex &rootIndex);

public slots:
    void setRootIndex(const QModelIndex &index);
    void showHint(const QModelIndex &index);
    void mouseDoubleClickSlot(const QModelIndex &index);

protected:
    void mousePressEvent(QMouseEvent *event);
    void drawComment(const QPersistentModelIndex &index);
    bool adjustChildWidgetPos(QWidget *child);

protected:
    GCommentFrame *commentFrame;
    int m_hintExistSeconds;
    bool m_bShowHint;
    bool m_bFirstShow;
    bool m_bOpenFileWhileDblClk;

private:
    Q_DISABLE_COPY(GLDShellListView)
    void init();
    friend class GLDShellComboBox;
};

#endif // GLDSHELLTREEVIEW_H
