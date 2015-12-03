#ifndef GLDTABLEVIEWEXPORT_H
#define GLDTABLEVIEWEXPORT_H

#include <limits>
#include "GLDMap.h"
#include "GLDTableView.h"
#include "GLDDocView.h"
#include "libxl.h"

using namespace libxl;

enum ExportState {EXPORT_SUCCESS, EXPORT_NOTWRITING, EXPORT_ERRSAVE};

struct TableCellFormat
{
    TableCellFormat()
        : fontName(NULL), fontSize(0), fontIsBold(false),
          fontIsUnderline(false), fontIsStrikeOut(false),
          fontIsItalic(false), foregroundRed(0), foregroundGreen(0),
          foregroundBlue(0), textAlignment(0), backColorRed(0),
          backColorGreen(0), backColorBlue(0), diffFormat(NULL)
    {}
    //Qt::FontRole��Ӧ�ĸ�ʽ����
    QChar *fontName;
    int fontSize;
    bool fontIsBold;
    bool fontIsUnderline;
    bool fontIsStrikeOut;
    bool fontIsItalic;

    //Qt::ForegroundRole��Ӧ�ĸ�ʽ����
    int foregroundRed;
    int foregroundGreen;
    int foregroundBlue;

    //Qt::TextAlignmentRole��Ӧ�ĸ�ʽ����
    Qt::Alignment textAlignment;

    //Qt::BackgroundColorRole��Ӧ�ĸ�ʽ����
    int backColorRed;
    int backColorGreen;
    int backColorBlue;

    //��GlodonTableView���ɵ�Excel��Ӧ��Format����
    Format *diffFormat;
};

struct TableCellLocation
{
public:
    TableCellLocation(int row, int col)
        : xCoordinate(row), yCoordinate(col)
    {}
    inline bool operator==(const TableCellLocation &tableCell) const
    {
        return (tableCell.xCoordinate == xCoordinate) && (tableCell.yCoordinate == yCoordinate);
    }

private:
    int xCoordinate;
    int yCoordinate;
};

class GlodonTableViewToExcelPrivate;
class GLDTABLEVIEWSHARED_EXPORT GlodonTableViewToExcel
{
    Q_DECLARE_TR_FUNCTIONS(GlodonTableViewToExcel)

    struct GlodonExcelGroupStruct
    {
        int start;
        int end;
        bool visible;

        GlodonExcelGroupStruct()
        {
            start = -1;
            end = INT_MAX;
            visible = true;
        }
        GlodonExcelGroupStruct(const GlodonExcelGroupStruct &other)
        {
            operator=(other);
        }
        GlodonExcelGroupStruct &operator=(const GlodonExcelGroupStruct &other)
        {
            start = other.start;
            end = other.end;
            visible = other.visible;
            return *this;
        }
    };

public:
    GlodonTableViewToExcel();
    ~GlodonTableViewToExcel();
public:
    static ExportState execute(GlodonTableView *tableView,
                        const GString &fileName,
                        const GString &sheetName,
                        bool isCollapsed = false,
                        bool isToSingleSheet = false,
                        bool isOverWrite = true,
                        bool showPrompt = true);
public:
    ExportState save(const GString &fileName);
    void load(const GString &fileName = "");
    void setTableView(GlodonTableView *tableView);
    void doExport(const GString &sheetName);
    void setExportIcon(bool value);
    void setIsOverWrite(bool isOverWrite);
    void setIsToSingleSheet(bool isToSingleSheet);
    void setShowPrompt(bool value);
    void setGroupCollapsed(bool collapse);

private:
    void initExcel(const GString &sheetName);
    void initSheet();
    void transTitleData();
    void transCellDatas();
    void transTitleAllMergeCells();
    void transMergeCells();
    void transFootData();
    void writeCellValue(const GVariant &value, Format *format, int row, int col);
    void writeIcon(const QAbstractItemModel *model,  QModelIndex oIndex, Format *format, int row, int col);
    void writeCellIcon(int row, int col, const GVariant value, const Format *format);
    void writeCellSymbol(int row, int col);
    void groupRows();
    int recursiveGroupRowsParent(int parentIndex, GMap<int, GlodonExcelGroupStruct> *groups);
    GlodonExcelGroupStruct getLastParentGroup(const GlodonExcelGroupStruct &group, GMap<int, GlodonExcelGroupStruct> *groups);
    void setFomatIndentSize(Format *format, int pixMaSize);
    libxl::Format *getFormat(const QAbstractItemModel *model, int row, int col);
    libxl::Format *addDiffFormat(const QAbstractItemModel *model, int row, int col);
    bool hasMatchedFormat(const QAbstractItemModel *model, int row, int col);
    libxl::Format *getTitleFormat(const QAbstractItemModel *model, int section, Qt::Orientation orientation);
    libxl::Format *addDiffTitleFormat(const QAbstractItemModel *model, int section, Qt::Orientation orientation);
    bool hasMatchedTitleFormat(const QAbstractItemModel *model, int section, Qt::Orientation orientation);
    void initBorderFormat();

private:
    GlodonTableViewToExcelPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(GlodonTableViewToExcel);
};

/**
 * @brief ����ҳ����е����ݵ�����Excel
 * @warning ����ֻ֧�ֵ�����ͬһ��sheet
 */
class GLDDocViewToExcelPrivate;
class GLDTABLEVIEWSHARED_EXPORT GLDDocViewToExcel
{
    Q_DECLARE_TR_FUNCTIONS(GLDDocViewToExcel)
public:
    GLDDocViewToExcel();
    ~GLDDocViewToExcel();

public:
    static bool execute(GLDDocView *docView,
                        const GString &fileName,
                        const GString &sheetName,
                        bool isToSingleSheet = false,
                        bool isOverWrite = true,
                        bool showPrompt = true);

public:
    void setDocView(GLDDocView *docView);
    ExportState exportToExcel(bool isToSingleSheet = false,
                              bool isOverWrite = true,
                              bool showPrompt = true);

public:
    /**
     * @brief ���ÿ�ʼ������Excel��ҳ��
     * @param startExportPage
     */
    void setStartExportPage(int startExportPage);

    /**
     * @brief ���ý���������Excel��ҳ��
     * @param entExportPage
     * @warning ������setDocView��������
     */
    void setEndExportPage(int endExportPage);

    /**
     * @brief ���ü��ص��ļ���
     * @param fileName
     */
    void setLoadFileName(QString fileName);

    /**
     * @brief ���ñ�����ļ���
     * @param fileName
     */
    void setSaveFileName(QString fileName);

    /**
     * @brief ���õ�������ҳǩ������
     * @param sheetName
     */
    void setSheetName(QString sheetName);

private:
    GLDDocViewToExcelPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(GLDDocViewToExcel);
};

#endif // GLDTABLEVIEWEXPORT_H
