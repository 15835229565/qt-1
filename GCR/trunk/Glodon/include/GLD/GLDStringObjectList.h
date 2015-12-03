#ifndef GSTRINGOBJECTLIST_H
#define GSTRINGOBJECTLIST_H

/*!
 * @brief ʵ��TStringList�Լ������
 *
 * ��ϸ˵��
 * @author duanb
 * @date 2013.08.23
 * @remarks ��ע
 * Copyright (c) 1998-2013 Glodon Corporation
*/

#include "GLDHash.h"
#include "GLDString.h"
#include "GLDIODevice.h"
#include "GLDSortUtils.h"

struct GStringItem
{
    GString str;
    void* object;
};

class GStringObjectListPrivate;
class GLDCOMMONSHARED_EXPORT GStringObjectList
{
public:
    explicit GStringObjectList();
    GStringObjectList(GStringObjectListPrivate &dd);
    //�������캯��
    GStringObjectList(const GStringObjectList& other);
    virtual ~GStringObjectList();
public:
    enum GDuplicates
    {
        dupIgnore,
        dupAccept,
        dupError
    };
    enum GStringsDefined
    {
        sdDelimiter,
        sdQuoteChar,
        sdNameValueSeparator,
        sdLineBreak,
        sdStrictDelimiter
    };

    virtual int add(const GString &s);
    virtual int add(GStringItem *item);
    virtual int addObject(const GString &s, void *object);
    virtual int addStrings(GStringObjectList *list);

    virtual void insert(int index, const GString &s);
    virtual void insertObject(int index, const GString &s, void *object);

    virtual bool find(const GString &s, int &index);
    virtual int indexOfObject(void *value);
    virtual int indexOf(const GString &value);

    virtual void put(int index, const GString &s);
    GString string(int index);
    virtual void putString(int index, const GString &s);

    virtual void *object(int index);
    virtual void putObject(int index, void *object);

    virtual void clear();
    bool isEmpty();
    virtual int count() const;
    virtual int size();
    GStringItem *at(int index) const;
    void setIndex(int index, GStringItem* item);
    GStringItem* &operator[](int index);

    virtual void push_back(GStringItem *item);
    virtual void append(GStringItem *item);
    virtual void append(GObjectList<GStringItem*> &items);
    GObjectList<GStringItem*> &list();
    virtual void Delete(int index);
    virtual void removeAt(int index);
    virtual void exchange(int index1, int index2);
    virtual void swap(int index1, int index2);

    virtual void sort(bool ascend = true);
    virtual void customSort(CSortCompareEvent *customSortEvent = NULL, bool ascend = false);

    GString value(const GString &name);
    void setValue(const GString &name, const GString &value);
    GString valueFromIndex(int index);
    void setValueFromIndex(int index, const GString &value);

    GString names(int index);
    virtual int indexOfName(const GString &name);

    bool caseSensitive() const;
    void setCaseSensitive(bool caseSensitive);

    bool sorted() const;
    void setSorted(bool sorted);

    GDuplicates duplicates() const;
    void setDuplicates(const GDuplicates &duplicates);

    void checkIndex(int index) const;
    virtual int compareStrings(const GString &s1, const GString &s2);

    virtual void setTextStr(const GString &value);
    GString textStr();

    virtual void loadFromFile(const GString &fileName);
    virtual void loadFromStream(GStream *stream);
    virtual void saveToFile(const GString &fileName);
    virtual void saveToStream(GStream *stream);

    //��������ʹ�ô˷���
    virtual void changed();

    // ������Щ����������û����
    void beginUpdate();
    void endUpdate();
    void setUpdateState(bool updating);

    void assign(GStringObjectList *source);

    GString lineBreak();
    void setLineBreak(const GString &lineBreak);

    char quoteChar();
    void setQuoteChar(char quoteChar);

    char nameValueSeparator();
    void setNameValueSeparator(char nameValueSeparator);

    bool strictDelimiter();
    void setStrictDelimiter(bool strictDelimiter);

    char delimiter();
    void setDelimiter(char delimiter);

    GString delimitedText();
    void setDelimitedText(const GString &value);

    void setCommaText(const GString &value);
    GString commaText();
protected:
    virtual void insertItem(int index, const GString &s, void *object);
    virtual void insertItem(int index, GStringItem *item);
    virtual void changing();
    GString extractName(const GString &s);
private:
    int findItem(const GString &s, void *object);
    bool containsBeforeSpace(const gint64 set);
    template <typename Set, typename T>
    inline bool contains(const Set &set, const T t) const
    {
        return 0 != (set & (byte(1) << byte(t)));//TODOREVIEW
    }
    inline bool containsOfGint64(const gint64 &set, const gint64 t) const
    {
        return 0 != (set & gint64(gint64(1) << gint64(t)));//TODOREVIEW
    }
    inline void includeOfGint64(gint64 &set, const gint64 t)
    {
        set |= (gint64(1) << gint64(t));
    }

    inline void excludeOfGint64(gint64 &set, const gint64 t)
    {
        set &= ~(gint64(1) << gint64(t));
    }

protected:
    GStringObjectListPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(GStringObjectList);
};

class GHashedStringObjectListPrivate;
/*!
 *@ GHashedStringObjectList
 *@brief ���ڼӿ�����ٶ�
 *@author duanb
 *@date 2013.08.23
*/
class GLDCOMMONSHARED_EXPORT GHashedStringObjectList : public GStringObjectList
{
public:
    explicit GHashedStringObjectList();
    ~GHashedStringObjectList();
public:
    int indexOfName(const GString &name);
    int indexOf(const GString &value);
    void changed();

private:
    void updateValueHash();
    void updateNameHash();
private:
    Q_DECLARE_PRIVATE(GHashedStringObjectList);
};

#endif // GSTRINGOBJECTLIST_H
