#include "GLDSortUtils.h"

void fast_sort(int *ptr, int begin, int end)
{
    if (!ptr)
    {
        return;
    }
    int nTemp = *(ptr + begin);//���ó�ʼ�Ƚϻ�׼����
    int nIt1 = begin + 1;
    int nIt2 = end;
    int nCurPosition = begin;//���忪ͷ�ͽ�β��I j
    bool bDirection = false;
    while (nIt1 <= nIt2)
    {
        if (bDirection)
        {
            if (*(ptr + nIt1) < nTemp)//�����ǰ����С�ڻ�׼���� ��ô��λ�� �ĵ�ǰλ��
            {
                *(ptr + nCurPosition) = *(ptr + nIt1);
                nCurPosition = nIt1;
                bDirection = false;
            }
            nIt1++;
        }
        else
        {
            //�ȴӺ�ǰ�Ƚ�����
            if (*(ptr + nIt2) > nTemp)
            {//������һ�����ڻ�׼ ��ô���һ�����ݸ�ֵ����ǰ��׼���ݵ��Ǹ�λ�� ������׼���ݵ�λ��
                *(ptr + nCurPosition) = *(ptr + nIt2);//
                nCurPosition = nIt2;
                bDirection = true;
            }
            nIt2--;
        }
    }

    *(ptr + nCurPosition) = nTemp;
    if (nCurPosition - begin > 1)//ǰ��С�ıȽ�
    {
        fast_sort(ptr, begin, nCurPosition - 1);
    }
    if (end - nCurPosition > 1)//�����ıȽ�
    {
        fast_sort(ptr, nCurPosition + 1, end);
    }
}
