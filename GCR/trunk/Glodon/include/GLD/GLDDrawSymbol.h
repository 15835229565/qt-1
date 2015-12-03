#ifndef GLDDRAWSYMBOL_H
#define GLDDRAWSYMBOL_H
#include <QString>
#include <QRect>
#include <QPainter>
#include "GLDString.h"
#include "GLDObjectList.h"
#include "GLDStrUtils.h"
#include "GLDTableView_Global.h"

struct GlodonDiameterSymbolRec
{
    GString symbol;
    GString resourceName;
};

struct GlodonSymbolPos
{
    int pos;
    int symbolPosIndex;
};

const  GString c_MeterSymbol        = "m";

const  GString c_SquareSymbol       = "2";
const  GString c_CubeSymbol         = "3";

const  GString c_SquareReplace      = TRANS_STRING("�p");//�������ַ���Ϊ���滻m2,m3����ʶ�ã����÷���
const  GString c_CubeReplace        = TRANS_STRING("�q");
const  GString c_SharpReplace       = "#";

const  GString c_SuperSymbol        = "3";
const  double c_SuperScale          = 0.5;
const  double c_SharpScale          = 0.7;

#ifndef _FONTSYMBOL_
    #ifdef __APPLE__
    const GlodonDiameterSymbolRec c_DiameterSymbols [] =
    {
          {TRANS_STRING("��16"), "SDIABFE"},
          {TRANS_STRING("��15"), "SDIAEEE"},
          {TRANS_STRING("��13"), "SDIABE"},
          {TRANS_STRING("��14"), "SDIACE"},
          {TRANS_STRING("��17"), "SDIACFE"},
          {TRANS_STRING("��18"), "SDIAEFE"},
          {TRANS_STRING("��A"), "SDIAA"},
          {TRANS_STRING("��B"), "SDIAB"},
          {TRANS_STRING("��2"), "SDIABF"},
          {TRANS_STRING("��C"), "SDIAC"},
          {TRANS_STRING("��3"), "SDIACF"},
          {TRANS_STRING("��D"), "SDIAD"},
          {TRANS_STRING("��E"), "SDIAE"},
          {TRANS_STRING("��5"), "SDIAEF"},
          {TRANS_STRING("��G"), "SDIAG"},
          {TRANS_STRING("��L"), "SDIAL"},
          {TRANS_STRING("��N"), "SDIAN"},
          {TRANS_STRING("��Y"), "SDIAY"}
    };
    #else
    const GlodonDiameterSymbolRec c_DiameterSymbols [] =
    {
          {GString::fromLocal8Bit("��16"), "SDIABFE"},
          {GString::fromLocal8Bit("��15"), "SDIAEEE"},
          {GString::fromLocal8Bit("��13"), "SDIABE"},
          {GString::fromLocal8Bit("��14"), "SDIACE"},
          {GString::fromLocal8Bit("��17"), "SDIACFE"},
          {GString::fromLocal8Bit("��18"), "SDIAEFE"},
          {GString::fromLocal8Bit("��A"), "SDIAA"},
          {GString::fromLocal8Bit("��B"), "SDIAB"},
          {GString::fromLocal8Bit("��2"), "SDIABF"},
          {GString::fromLocal8Bit("��C"), "SDIAC"},
          {GString::fromLocal8Bit("��3"), "SDIACF"},
          {GString::fromLocal8Bit("��D"), "SDIAD"},
          {GString::fromLocal8Bit("��E"), "SDIAE"},
          {GString::fromLocal8Bit("��5"), "SDIAEF"},
          {GString::fromLocal8Bit("��G"), "SDIAG"},
          {GString::fromLocal8Bit("��L"), "SDIAL"},
          {GString::fromLocal8Bit("��N"), "SDIAN"},
          {GString::fromLocal8Bit("��Y"), "SDIAY"}
    };
    #endif
#else
    #ifdef __APPLE__
    const GlodonDiameterSymbolRec c_DiameterSymbols [] =
    {
          {TRANS_STRING("��16"), TRANS_STRING("��")},
          {TRANS_STRING("��15"), TRANS_STRING("��")},
          {TRANS_STRING("��13"), TRANS_STRING("��")},
          {TRANS_STRING("��14"), TRANS_STRING("��")},
          {TRANS_STRING("��17"), TRANS_STRING("��")},
          {TRANS_STRING("��18"), TRANS_STRING("��")},
          {TRANS_STRING("��A"), TRANS_STRING("��")},
          {TRANS_STRING("��B"), TRANS_STRING("��")},
          {TRANS_STRING("��2"), TRANS_STRING("��")},
          {TRANS_STRING("��C"), TRANS_STRING("��")},
          {TRANS_STRING("��3"), TRANS_STRING("��")},
          {TRANS_STRING("��D"), TRANS_STRING("��")},
          {TRANS_STRING("��E"), TRANS_STRING("��")},
          {TRANS_STRING("��5"), TRANS_STRING("��")},
          {TRANS_STRING("��G"), TRANS_STRING("��")},
          {TRANS_STRING("��L"), TRANS_STRING("��")},
          {TRANS_STRING("��N"), TRANS_STRING("��")},
          {TRANS_STRING("��Y"), TRANS_STRING("��")}
    };
    #else
    const GlodonDiameterSymbolRec c_DiameterSymbols [] =
    {
          {GString::fromLocal8Bit("��16"), GString::fromLocal8Bit("��")},
          {GString::fromLocal8Bit("��15"), GString::fromLocal8Bit("��")},
          {GString::fromLocal8Bit("��13"), GString::fromLocal8Bit("��")},
          {GString::fromLocal8Bit("��14"), GString::fromLocal8Bit("��")},
          {GString::fromLocal8Bit("��17"), GString::fromLocal8Bit("��")},
          {GString::fromLocal8Bit("��18"), GString::fromLocal8Bit("��")},
          {GString::fromLocal8Bit("��A"), GString::fromLocal8Bit("��")},
          {GString::fromLocal8Bit("��B"), GString::fromLocal8Bit("��")},
          {GString::fromLocal8Bit("��2"), GString::fromLocal8Bit("��")},
          {GString::fromLocal8Bit("��C"), GString::fromLocal8Bit("��")},
          {GString::fromLocal8Bit("��3"), GString::fromLocal8Bit("��")},
          {GString::fromLocal8Bit("��D"), GString::fromLocal8Bit("��")},
          {GString::fromLocal8Bit("��E"), GString::fromLocal8Bit("��")},
          {GString::fromLocal8Bit("��5"), GString::fromLocal8Bit("��")},
          {GString::fromLocal8Bit("��G"), GString::fromLocal8Bit("��")},
          {GString::fromLocal8Bit("��L"), GString::fromLocal8Bit("��")},
          {GString::fromLocal8Bit("��N"), GString::fromLocal8Bit("��")},
          {GString::fromLocal8Bit("��Y"), GString::fromLocal8Bit("��")}
    };
    #endif
#endif

class GlodonCustomDrawSymbol;
class GlodonMeterDrawSymbol;
class GlodonDiaDrawSymbol;
class GlodonCustomDrawSymbolFactory;
class GlodonMeterDrawSymbolFactory;
class GlodonDiaDrawSymbolFactory;

class GlodonCustomDrawSymbolFactory
{
public:
    virtual ~GlodonCustomDrawSymbolFactory() = 0;

    virtual GlodonCustomDrawSymbol* create() = 0;
};

class GlodonMeterDrawSymbolFactory : public GlodonCustomDrawSymbolFactory
{
public:
    virtual ~GlodonMeterDrawSymbolFactory() = 0;
    GlodonCustomDrawSymbol* create();
};

class GlodonDiaDrawSymbolFactory : public GlodonCustomDrawSymbolFactory
{
public:
    virtual ~GlodonDiaDrawSymbolFactory() = 0;
    GlodonCustomDrawSymbol* create();
};

class GLDTABLEVIEWSHARED_EXPORT GlodonCustomDrawSymbol
{
public:
    GlodonCustomDrawSymbol(QObject *parent = 0);
    bool virtual canHandle(const QString &text) = 0;

protected:
    virtual void drawText(QPainter *painter, int scale, const QString &text, Qt::Alignment align, QRect &rect) = 0;
};

class GlodonDrawSymbolManager
{
public:
    GlodonDrawSymbolManager();
    ~GlodonDrawSymbolManager();

public:
    int indexOfDrawSymbolClass(const QString &text);
    void addDrawSymbol();

    void drawText(QPainter *painter, int scale, const QString &text, Qt::Alignment align, QRect &rect, bool &handle);
};

class GLDTABLEVIEWSHARED_EXPORT GlodonMeterDrawSymbol : public GlodonCustomDrawSymbol
{
public:
    bool canHandle(const QString &text);
protected:
    /**
     * @brief ������ָ�������������ִ��ĳ��ȣ�ͬʱ����ʵ��ռ�õĿ��
     * @param painter
     * @param text
     * @param width
     * @param height
     * @return
     */
    int calcDrawLineLength(QPainter *painter, const QString &text, int &width);
    /**
     * @brief �������ƶ���Χ����������ִ��ĳ���
     * @param painter
     * @param text
     * @param width
     * @param height
     * @return
     */
    int calcDrawTextLength(QPainter *painter, const QString &text, int width, int height);
    int calcM2M3Length(QPainter *painter);

public:
    void drawText(QPainter *painter, int scale, const QString &text, Qt::Alignment align, QRect &rect);

private:
    bool isTextM2M3(const QString &text);
    bool isTextSharp(const QString &text);
    QString replaceSymbolText(const QString &text);
    void drawLine(QPainter *painter, const QString &text, int x, int y, int &width, int &height);
    void drawM2M3(QPainter *painter, int x, int y, const QString & symbol);
    void drawSharp(QPainter *painter, int x, int y, const QString &symbol);
    void interDrawText(QPainter *painter, const QString &text, Qt::Alignment align, int x, int y, int width, int &height);
};

class GLDTABLEVIEWSHARED_EXPORT GlodonDiaDrawSymbol : public GlodonCustomDrawSymbol
{
public:
    bool canHandle(const QString &text);

public:
    void draw(QPainter *painter, int scale, const QString &text, Qt::Alignment align, QRect &rect);
    void drawText(QPainter *painter, int scale, const QString &text, Qt::Alignment align, QRect &rect);

private:
    void draw1Symbol(QPainter *painter, int scale, const QString &text, Qt::Alignment align, QRect &rect, int index);
    void drawBitMap(QPainter *painter, int scale, Qt::Alignment align, QRect &rect, int index);
    void innerDrawText(QPainter *painter, Qt::Alignment align, QRect &rect, const QString &text);
	int getContentWidth(QPainter *painter, int scale, const QString &text);
	int getContentHeight(QPainter *painter, int scale, const QString &text);
};

//  function  DrawSymbolManager TDrawSymbolManager;

GLDTABLEVIEWSHARED_EXPORT bool includeM2M3(const QString &text);
GLDTABLEVIEWSHARED_EXPORT void drawTextMx(QPainter *painter, const QString &text, Qt::Alignment align, QRect &rect);
GLDTABLEVIEWSHARED_EXPORT bool includeSharp(const QString &text);
GLDTABLEVIEWSHARED_EXPORT bool includeDiaSymbol(const QString &text);

GLDTABLEVIEWSHARED_EXPORT void drawDiaSymbol(QPainter *painter, int scale, const QString &text, Qt::Alignment align, QRect &rect);
GObjectList<GlodonSymbolPos *> *createIndexOfDiameterSymbolList(const QString &text);
GLDTABLEVIEWSHARED_EXPORT bool compare(GlodonSymbolPos *item1, GlodonSymbolPos *item2);

/**
 * @brief The GlodonSymbols class �ֽ������
 */

#ifdef _FONTSYMBOL_
class GLDTABLEVIEWSHARED_EXPORT GlodonSymbols
{
public:
    GlodonSymbols();
    ~GlodonSymbols(){}

public:
    /**
     * @brief aliasFromDisplaySymbol ���displaySymbol���ڸֽ���ſ⣬�򷵻�����������򷵻�displaySymbol
     * @param displaySymbol
     * @return
     */
    QString aliasFromDisplaySymbol(const QString &displaySymbol);
    /**
     * @brief displaySymbolFromGiveSymbol ���alias���ڸֽ���ſ⣬�񷵻�������ʾ�ĸֽ�����ַ��������򷵻�alias
     * @param giveSymbol
     * @return
     */
    QString displaySymbolFromAlias(const QString &alias);

    /**
     * @brief allSymbols �������еĸֽ����
     * @return QMap<QString, QString> QMap�е�һ������Ϊ�ֽ���ű�����ͬGlodonDiameterSymbolRec�ṹ���е�symbol
     *                                QMap�еڶ�������Ϊ�ֽ���ŵ���ʾ�ַ����� ��Ҫ������ʾ
     */
    QMap<QString, QString> allSymbols() const;

    /**
     * @brief aliasesFromDisplaySymbols ����ʾ�ĸֽ���Ŵ�(����ֽ����)תΪ�������Ŵ�(���)
     * @param displaySymbols
     * @return
     */
    QString aliasesFromDisplaySymbols(const QString &displaySymbols);

    /**
     * @brief displaySymbolsFromAliases �ӱ������Ŵ�(���)תΪ��ʾ�ĸֽ���Ŵ�(���)
     * @param aliases
     * @return
     */
    QString displaySymbolsFromAliases(const QString &aliases);

private:
    void initSymbols(const GlodonDiameterSymbolRec array[], size_t size);
    QMap<QString, QString> m_symbols; // �ֽ�����б� ��һ������Ϊ�ֽ���ű�������һ������Ϊ��Ҫ��ʾ�ĸֽ����
};
#endif

#endif // GLDDRAWSYMBOL_H
