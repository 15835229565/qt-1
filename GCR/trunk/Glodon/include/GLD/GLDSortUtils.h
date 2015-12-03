#ifndef GLDSORTUTILS_H
#define GLDSORTUTILS_H

#include "GLDVariant.h"
#include "GLDMathUtils.h"
#include "GLDInterfaceObject.h"

enum GSeekOption
{
    soFirst,                          // ���ص�һ��ƥ��ļ�¼�±�
    soLast,                           // �������һ��ƥ��ļ�¼�±�
    soMatch                           // ���ض��ֲ���ʱ�״�ƥ��ļ�¼�±�
};

class GLDCOMMONSHARED_EXPORT CSortCompareEvent
{
public:
    virtual ~CSortCompareEvent() {}

    virtual CompareResult compare(void *item1, void *item2) = 0;
};

class GLDCOMMONSHARED_EXPORT ISearchCompareEvent
{
public:
    virtual CompareResult compare(void *item1, const GVariant &keyvalue) = 0;
};

inline CompareResult doSortCompare(void *item1, void *item2, CSortCompareEvent *compare, bool ascend)
{
    CompareResult result = compare->compare(item1, item2);
    if (!ascend)
    {
        if (result == crEqual)
        {
            return result;
        }
        if (result == crGreaterThan)
        {
            result = crLessThan;
        }
        else
        {
            result = crGreaterThan;
        }
    }
    return result;
}

template <typename T>
void merge(GLDVector<T> &source, GLDVector<T> &dest, int low, int mid, int high, CSortCompareEvent *compare, bool ascend)
{
    int nFirst = low;              // ��һ�ε��α�
    int nSecnd = mid + 1;          // �ڶ��ε��α�
    int nResult = low;              // ������α�
    // ֻҪ�ڶ��д���I��J���򲻶Ͻ��й鲢
    while ((nFirst <= mid) && (nSecnd <= high))
    {
        if (doSortCompare(source.at(nFirst), source.at(nSecnd), compare, ascend) != crGreaterThan)
        {
            dest[nResult] = source[nFirst];
            nResult++;
            nFirst++;
        }
        else
        {
            dest[nResult] = source[nSecnd];
            nResult++;
            nSecnd++;
        }
    }
    // �������µĲ���
    if (nFirst > mid)
    {
        for (int i = nSecnd; i <= high; ++i)
        {
            dest[nResult] = source[i];
            nResult++;
        }
    }
    else
    {
        for (int i = nFirst; i <= mid; ++i)
        {
            dest[nResult] = source[i];
            nResult++;
        }
    }
}

template <typename T>
void mergePass(GLDVector<T> &source, GLDVector<T> &dest, int subSection, int n, CSortCompareEvent *compare, bool ascend)
{
    int nIndex = 0;
    // �鲢������СΪSubSection�����ڶ�
    while (nIndex <= n - 2 * subSection)
    {
        merge(source, dest, nIndex, nIndex + subSection - 1, nIndex + 2 * subSection - 1, compare, ascend);
        nIndex = nIndex + 2 * subSection;
    }
    // ʣ�²�������Ԫ��
    if (nIndex + subSection < n)
    {
        merge(source, dest, nIndex, nIndex + subSection - 1, n - 1, compare, ascend);
    }
    else          // �����һ�θ��Ƶ�ADest
    {
        for (int j = nIndex; j <= n - 1; ++j)
        {
            dest[j] = source[j];
        }
    }
}

template <typename T>
void doSort(int lowIndex, int highIndex, GLDVector<T> &sortList, CSortCompareEvent *compare, bool ascend)
{
    int nIt1 = 0;
    int nIt2 = 0;
    PtrInt pInt1 = 0;
    PtrInt pInt2 = 0;
    do
    {
        nIt1 = lowIndex;
        nIt2 = highIndex;
        void *ptr = (sortList.at((lowIndex + highIndex) >> 1));
        pInt1 = (PtrInt)ptr;
        do
        {
            while (doSortCompare(sortList.at(nIt1), (void*)(pInt1), compare, ascend) == crLessThan)
            {
                nIt1++;
            }
            while (doSortCompare(sortList.at(nIt2), (void*)(pInt1), compare, ascend) == crGreaterThan)
            {
                nIt2--;
            }
            if (nIt1 <= nIt2)
            {
                pInt2 = PtrInt(sortList.at(nIt1));
                sortList[nIt1] = sortList[nIt2];
                sortList[nIt2] = (T)(pInt2);
                nIt1++;
                nIt2--;
            }
        } while (nIt1 <= nIt2);
        if (lowIndex < nIt2)
        {
            doSort(lowIndex, nIt2, sortList, compare, ascend);
        }
        lowIndex = nIt1;
    } while (nIt1 < highIndex);
}

template <typename T>
void mergeSort(GLDVector<T> &sortList, CSortCompareEvent *compare, bool ascend = true)
{
    int nSubSection = 1;      // �εĴ�С
    int nCount = sortList.count();
    GLDVector<T> oList; // �����м�ת���������б�
    for (int i = 0; i < nCount; i++)
    {
        oList.push_back(NULL);
    }
    while (nSubSection < nCount)
    {
        mergePass(sortList, oList, nSubSection, nCount, compare, ascend); // ��ASource�鲢��oList
        nSubSection = nSubSection << 1;
        mergePass(oList, sortList, nSubSection, nCount, compare, ascend); // ��oList�鲢��ASource
        nSubSection = nSubSection << 1;
    }
}

template <typename T>
void quickSort(GLDVector<T> &sortList, CSortCompareEvent *compare, bool ascend = true)
{
    if (sortList.size() <= 1)
    {
        return;
    }
    doSort(0, int(sortList.size()) - 1, sortList, compare, ascend);
}

/*-----------------------------------------------------------------------------
  ������Tu Jianhua 2005.08.29
  ���ܣ����ַ�����
  ������searchList -- �����б�
        compare -- �ȽϺ���
       keyValue -- ��ֵ
        *index -- ���ص�ƥ�������б��е��±�
        seekOption -- ����ѡ��
  ���أ��Ƿ��ҵ���־
  ˵���������Ҳ���keyValue��Ӧ����
        ���seekOption = soFirst��*indexֵΪС��AKeyValue������
        ���seekOption = soLast��*indexֵΪ����AKeyValue�������
-----------------------------------------------------------------------------*/
template <typename T>
bool binSearch(GLDVector<T> &searchList, ISearchCompareEvent *compare, const GVariant &keyValue, long *index, GSeekOption seekOption)
{
    bool result = false;
    if (searchList.size() == 0)
    {
        *index = 0;
        return result;
    }
    int nLow = 0;
    int nHigh = int(searchList.size()) - 1;
    *index = nHigh;
    while (nLow <= nHigh)              // ���ַ�����
    {
        *index = (nLow + nHigh) / 2;
        switch (compare->compare(searchList.at(*index), keyValue))
        {
        case crLessThan:
            nLow = *index + 1;
            break;
        case crGreaterThan:
            nHigh = *index - 1;
            break;
        default:
            result = true;
            break;
        }
        if (result)
        {
            break;
        }
    }

    if (!result)                  // �����Ҳ���ʱ��λ��
    {
        switch (seekOption)
        {
        case soFirst:
            if (compare->compare(searchList.at(*index), keyValue) == crGreaterThan)
            {
                (*index)--;
            }
            break;
        case soLast:
            if (compare->compare(searchList.at(*index), keyValue) == crLessThan)
            {
                (*index)++;
            }
            break;
        default:
            break;
        }
    }
    else                          // �ҵ�ƥ���������ܶ�����ͬ��ֵ�����
    {
        switch (seekOption)
        {
        case soFirst:                        // ��λ����һ�����ϵ�����
        {
            for (int i = *index-1; i >= 0; i--)
            {
                if (compare->compare(searchList.at(i), keyValue) == crEqual)
                {
                    *index = i;
                }
                else
                {
                    break;
                }
            }
            break;
        }
        case soLast:                         // ��λ�����һ�����ϵļ�¼
        {
            for (int i = *index + 1; i != searchList.count(); ++i)
            {
                if (compare->compare(searchList.at(i), keyValue) == crEqual)
                {
                    *index = i;
                }
                else
                {
                    break;
                }
            }
            break;
        }
        default:
            break;
        }
    }
    return result;
}

GLDCOMMONSHARED_EXPORT void fast_sort(int *ptr, int begin, int end);

#endif // GLDSORTUTILS_H
