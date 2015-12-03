#include "GLDMathUtils.h"

#ifdef WIN32
#include "WTypes.h"
#endif

#include <time.h>
#include <qmath.h>

#include "GLDGlobal.h"
#include "GLDStrUtils.h"
#include "GLDFloatFormating.h"

//const int CFuzzFactor = 1000;
//const int CExtendedResolution = 1e-19 * CFuzzFactor;
//const int CDoubleResolution   = 1e-15 * CFuzzFactor;
//const int CSingleResolution   = 1e-7 * CFuzzFactor;

const double c_defDoubleEpsilon = 1e-12;

double ln(double v)
{
    assert(v > 0);
    return qLn(v);
}

// Log.N(X) := Log.2(X) / Log.2(N)
double logN(double x, double n)
{
    assert(x > 0);
    assert(n > 0);
    assert(n != 1);
    return ln(x) / ln(n);
}

double arcSin(double v)
{
    return qAsin(v);
}

double arcCos(double v)
{
    return qAcos(v);
}

double arctan(double v)
{
    return qAtan(v);
}

double sqr(double v)
{
    return v * v;
}

bool sameFloat(float firstNum, float secondNum)
{
    return (fabs(firstNum - secondNum) < 0.00001 ? true : false);
}

bool sameValue(double a, double b, double epsilon)
{
    return fabs(a - b) < epsilon;
}

GLDValueRelationship compareValue(double a, double b, double epsilon)
{
    if (sameValue(a, b, epsilon))
    {
        return gvrEqualsValue;
    }
    else if (a < b)
    {
        return gvrLessThanValue;
    }
    else
    {
        return gvrGreaterThanValue;
    }
}

// ȥβȡ�� trunc(5.6) == 5; trunc(-5.6) == -5
long long itrunc(double v)
{
    return (long long)(v);
}

// ������������˫ round(2.5) == 2; round(3.5) == 4; round(-2.5) == -2; round(-3.5) == -4;
long long iround(double v)
{
    // todo ������+1
    double dFabsVal = fabs(v);
    long long llTmp = itrunc(dFabsVal);
    if (dFabsVal - llTmp > 0.5)
    {
        ++llTmp;
    }
    else if (dFabsVal - llTmp == 0.5)
    {
        if ((llTmp % 2) != 0)
        {
            ++llTmp;
        }
    }
    if (v < 0)
        return -llTmp;
    else
        return llTmp;
}

////////////////////////////////////////////////////////////////////////////////
// ˵����������ȡָ��λС������
// ������F -- ������
//       ADecimal -- С��λ��
// ���أ�F��ADecimalλС���������������ĸ�����
// ע�⣺FRound( 518.775, 2) = 518.78
//       FRound(-518.775, 2) = -518.78
//       FRound(-518.775, -1) = -520
//       Ϊ�˱���������⣬���� IEEE �Ĺ涨ֱ���� F β���ϼ� 1������ 2 �� 4 ��
// ��ע����� ADecimal Ϊ����ʱ�Ĵ������������ֵľ��ȼ��㣻 zhangjq 2011.12.13
////////////////////////////////////////////////////////////////////////////////
double fRound(double v, int decimal, double epsilon)
{
    const static double c_DecBase[10] = {1, 1E1, 1E2, 1E3, 1E4, 1E5, 1E6, 1E7, 1E8, 1E9};
    if ((v > c_MaxInt64) || (v < c_MinInt64))
        return v;
    else if (decimal < 0)
    {
        // todo
        return v;
    }
    else if (decimal <= 8)
    {
        //����ֵ����10λʱ��+512����������Ƚϴ󣬵����ܱ�֤���Ƚ�С��ʱ������ȷ�ģ�by huangp 2015.9.6
        long long *ptmp = (long long *)(&v);
        *ptmp += 512; // ֧��512����ͬ������������Ӻ�fRound
        long long llIntVal = itrunc(v);
        long long llDecimalVal = itrunc((v - llIntVal) * c_DecBase[decimal + 1]);
        long long llModVal = llDecimalVal % 10;
        if (llModVal >= 5)
        {
            llDecimalVal += 10;
        }
        else if (llModVal <= -5)
        {
            llDecimalVal -= 10;
        }
        llDecimalVal = llDecimalVal / 10;
        return llIntVal + llDecimalVal / c_DecBase[decimal];
    }
    else
    {
        double result = strToFloat(
                    formatFloat("0." + stringOfChar(char('#'), decimal), v + epsilon));
        if (sameValue(result, 0.0))
        {
            result = 0;
        }
        return result;
    }
}

double frac(double v)
{
    return v - itrunc(v);
}

double drandom()
{
#ifdef WIN32
    srand(GetTickCount());
    return double(rand()) / double(RAND_MAX);
#else
    return drand48();
#endif
}

int random(int n)
{
    if (n <= 0)
    {
        return 0;
    }
    srand(time(0));
    return rand() % (n);
}

int randomRange(int from, int to)
{
    if (sameValue(from, to))
    {
        return from;
    }
    else if (from > to)
    {
        return random(from - to) + to;
    }
    else
    {
        return random(to - from) + from;
    }
}

double radToDeg(double radians)
{
    return radians * 180.0 / PI;
}

double degToRad(double degrees)
{
    return degrees * PI / 180.0;
}

double power(double x, double y)
{
    return qPow(x, y);
}

bool isZero(double value, double epsilon)
{
    if (epsilon == 0)
      epsilon = 1E-19 * 1000;;
    return fabs(value) <= epsilon;
}

bool varIsNullEx(const GVariant &value)
{
    return value.isNull();
}

GVariant varArrayOf(GLDVector<GVariant> &values)
{
    GVariantList result;
    for (int i = 0; i != values.count(); ++i)
    {
        result << values.at(i);
    }
    return GVariant(result);
}

GVariant inc(const GVariant &value)
{
    GVariant result;
    switch (value.type())
    {
    case GVariant::LongLong:
        result.setValue(value.toLongLong() + 1);
        break;
    case GVariant::ULongLong:
        result.setValue(value.toULongLong() + 1);
        break;
    case GVariant::Int:
        result.setValue(value.toInt() + 1);
        break;
    case GVariant::UInt:
        result.setValue(value.toUInt() + 1);
        break;
    case GVariant::Double:
        result.setValue(value.toDouble() + 1);
        break;
    case GVariant::ByteArray:
        result.setValue(GUIDToByteArray(createGUID()));
        break;
    case GVariant::String:
        result.setValue(GUIDToVariant(createGUID()));
        break;
    case GVariant::Uuid:
        result.setValue(GUIDToVariant(createGUID()));
        break;
    default:
        assert(false);
        break;
    }
    return result;
}

////////////////////////////////////////////////////////////////////////////////
// ˵��������ת��Ϊ��������
// ����: n -- ����(1~99)
// ����: ���ֶ�Ӧ�ĺ���
////////////////////////////////////////////////////////////////////////////////
GString num2CChar(int n)
{
    GString result;
    if ((n < 1) || (n > 99))
    {
        return "";
    }
    int nNumber = n % 10;
    switch (nNumber)
    {
    case 0:
        result = "";
        break;
    case 1:
        result = TRANS_STRING("һ");
        break;
    case 2:
        result = TRANS_STRING("��");
        break;
    case 3:
        result = TRANS_STRING("��");
        break;
    case 4:
        result = TRANS_STRING("��");
        break;
    case 5:
        result = TRANS_STRING("��");
        break;
    case 6:
        result = TRANS_STRING("��");
        break;
    case 7:
        result = TRANS_STRING("��");
        break;
    case 8:
        result = TRANS_STRING("��");
        break;
    case 9:
        result = TRANS_STRING("��");
        break;
    default:
        assert(false);
        break;
    }
    nNumber = n / 10;
    switch (nNumber)
    {
    case 1:
        result = TRANS_STRING("ʮ") + result;
        break;
    case 2:
        result = TRANS_STRING("��ʮ") + result;
        break;
    case 3:
        result = TRANS_STRING("��ʮ") + result;
        break;
    case 4:
        result = TRANS_STRING("��ʮ") + result;
        break;
    case 5:
        result = TRANS_STRING("��ʮ") + result;
        break;
    case 6:
        result = TRANS_STRING("��ʮ") + result;
        break;
    case 7:
        result = TRANS_STRING("��ʮ") + result;
        break;
    case 8:
        result = TRANS_STRING("��ʮ") + result;
        break;
    case 9:
        result = TRANS_STRING("��ʮ") + result;
        break;
    }
    return result;
}

// ������������ת�����������ִ�
// ʾ��: Num2CNum(10002.34) ==> һ�����������
GString num2ChsNum(double arabic)
{
    const GString c_ChineseNumeric = TRANS_STRING("��һ�����������߰˾�");
    GString result;
    GString sIntArabic;
    GString strSectionArabic;
    GString strSection;
    int nDigit = 0;
    bool bInZero = true;
    bool bMinus = false;

    GString strArabic = floatToStr(arabic);    // ������ת�ɰ����������ִ�
    if ('-' == strArabic.at(0).toLatin1())
    {
        bMinus = true;
        strArabic = copy(strArabic, 1);
    }
    int nPosOfDecimalPoint = pos('.', strArabic);    // ȡ��С�����λ��
    // �ȴ��������Ĳ���
    if (nPosOfDecimalPoint < 0)
    {
        sIntArabic = reverseString(strArabic);
    }
    else
    {
        sIntArabic = reverseString(copy(strArabic, 0, nPosOfDecimalPoint));
    }
    int nSection = 0;
    // �Ӹ�λ������ÿ��λ��ΪһС��
    for (nSection = 0; nSection <= (sIntArabic.length() - 1) / 4; ++nSection)
    {
        strSectionArabic = copy(sIntArabic, nSection * 4, 4);
        strSection = "";
        // ���µ� i ����: ��ʮ��ǧλ�ĸ�λ��
        for (int i = 0; i != strSectionArabic.length(); ++i)
        {
            nDigit = strSectionArabic.at(i).toLatin1() - 48;
            if (0 == nDigit)
            {
                // 1. ���� '��' ���ظ�����
                // 2. ��λ���� 0 ����ת�� '��'
                if ((!bInZero) && (i != 0))
                {
                    strSection = TRANS_STRING("��") + strSection;
                }
                bInZero = true;
            }
            else
            {
                switch (i)
                {
                case 1:
                    strSection = TRANS_STRING("ʮ") + strSection;
                    break;
                case 2:
                    strSection = TRANS_STRING("��") + strSection;
                    break;
                case 3:
                    strSection = TRANS_STRING("ǧ") + strSection;
                    break;
                default:
                    break;
                }
                strSection = c_ChineseNumeric[nDigit] + strSection;
                bInZero = false;
            }
        }
        // ���ϸ�С�ڵ�λ��
        if (0 == strSection.length())
        {
            if ((result.length() > 0) && (copy(result, 0, 2)) != TRANS_STRING("��"))
            {
                result = TRANS_STRING("��") + result;
            }
        }
        else
        {
            switch (nSection)
            {
            case 0:
                result = strSection;
                break;
            case 1:
                result = strSection + TRANS_STRING("��") + result;
                break;
            case 2:
                result = strSection + TRANS_STRING("��") + result;
                break;
            case 3:
                result = strSection + TRANS_STRING("��") + result;
                break;
            default:
                break;
            }
        }
    }
    // ����С�����ұߵĲ���
    if (nPosOfDecimalPoint >= 0)
    {
        result = result + TRANS_STRING("��");
        for (int i = nPosOfDecimalPoint + 1; i != strArabic.length(); ++i)
        {
            nDigit = strArabic.at(i).toLatin1() - 48;
            result = result + c_ChineseNumeric[nDigit];
        }
    }

    // ��������״���Ĵ���
    if (0 == result.length())
    {
        result = TRANS_STRING("��");
    }
    if (copy(result, 0, 2) == TRANS_STRING("һʮ"))
    {
        result = copy(result, 1);
    }
    if (copy(result, 0, 1) == TRANS_STRING("��"))
    {
        result = TRANS_STRING("��") + result;
    }

    // �Ƿ�Ϊ����
    if (bMinus)
    {
        result = TRANS_STRING("��") + result;
    }
    return result;
}

GString fourNumToChnNum(const GString &str, const GString &chnNum, bool &pre)
{
    const GString c_Digits = TRANS_STRING("��Ҽ��������½��ƾ�");
    GString result;
    int nLen = str.length();
    for (int i = 0; i != nLen; ++i)
    {
        int nOffset = str.at(i).toLatin1() - '0';
        if (0 == nOffset)
        {
            pre = true;
        }
        else
        {
            if (pre)
            {
                result = result + c_Digits[0];
            }
            result = result + c_Digits[nOffset] + copy(chnNum, nLen - i - 1, 1);
            pre = false;
        }
    }
    return stringReplace(result, TRANS_STRING("��"), "");
}

//����ʽ���õ�Сд��ת��Ϊ��д��
GString stringToChnNum(const GString &str)
{
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    const GString c_chnNum1 = GString("Ԫ������");
#else
    const GString c_chnNum1 = TRANS_STRING("Ԫ������");
#endif
    GString result;
    GString strTmp;
    GString strTmp1;
    int nLen = pos(".", str);
    int nLevel = (nLen + 3) / 4;
    int nLen1 = nLen % 4;
    if (0 == nLen1)
    {
        nLen1 = 4;
    }
    int nStart = 0;
    bool bPre = false;
    for (int i = 1; i <= nLevel; ++i)
    {
        bPre = false;
        strTmp = copy(str, nStart, nLen1);
        strTmp1 = fourNumToChnNum(strTmp, TRANS_STRING("��ʰ��Ǫ"), bPre);    // �����ո��Ϊ��ռλ��
        if ((strTmp1 != "") || ((i > 1) && (i == nLevel)))
        {
            result = result + strTmp1 + copy(c_chnNum1, nLevel - i, 1);
        }
        nStart = nStart + nLen1;
        nLen1 = 4;
    }
    bPre = false;
    strTmp1 = fourNumToChnNum(copy(str, nLen + 1, 2), TRANS_STRING("�ֽ�"), bPre);
    if (strTmp1.length() == 0)
    {
        strTmp1 = TRANS_STRING("��");
    }
    return result + strTmp1;
}

// ˵������Сд���ת��Ϊ��д
GString currToChnNum(double currnum)
{
    if (fabs(currnum) < c_defDoubleEpsilon)
    {
        return TRANS_STRING("��Ԫ��");
    }
    GString result;
    if (currnum < c_defDoubleEpsilon)
    {
        result = TRANS_STRING("��");
    }
    GString strTmp = GString::number(fabs(currnum), 'f', 2);
    return result + stringToChnNum((trim(strTmp)));
}

int rightZeroNumber(const GString &str)
{
    int nCount = 0;
    for (int i = str.length() - 1; i >= 0; --i)
    {
        if (str.at(i) == QChar('0'))
        {
            ++nCount;
        }
        else if (str.at(i) == QChar('.'))
        {
            ++nCount;
            break;
        }
        else
        {
            break;
        }
    }
    return nCount;
}

int leftZeroNumber(const GString &str)
{
    int nCount = 0;
    for (int i = 0; i <= str.length() - 1; ++i)
    {
        if (str.at(i) == QChar('0'))
        {
            ++nCount;
        }
        else
        {
            break;
        }
    }
    return nCount;
}

int rightZeroNumberNextDot(const GString &str)
{
    int result = 0;
    for (int i = str.length() - 1; i >= 0; i--)
    {
        if (str.at(i) == QChar('0'))
        {
            ++result;
        }
        else if (str.at(i) == QChar('.'))
        {
            break;
        }
    }
    return result;
}

int zeroNumberAfterDot(const GString &str)
{
    int result = 0;
    int nPos = str.indexOf('.');
    if (nPos < 0)
    {
        return result;
    }
    for (int i = nPos + 1; i < str.length() - 1; ++i)
    {
        if (str.at(i) == QChar('0'))
        {
            ++result;
        }
        else
        {
            break;
        }
    }
    return result;
}

/*!
 * \brief ����format�ĺ����0�ĸ���
 * \param format
 * \param value
 * \param nAfter
 * \return
 */
GString makeUpZero(const GString &format, const GString &value, int nAfter)
{
    GString result = value;
    int nRightZeroNum = 0;
    if (format.at(format.length() - 1) == QChar('0'))//���һλ��0, ���油��0
    {
        nRightZeroNum = nAfter;
    }
    else
    {
        nRightZeroNum = rightZeroNumberNextDot(format);
    }
    if ((result.length() <= nRightZeroNum) && (nRightZeroNum > 0))
    {
        int nCount = result.length();
        for (int i = 0; i < nRightZeroNum - nCount; i++)
        {
            result += '0';
        }
    }
    return result;
}

GString formatFloat(const GString &format, double value)
{
    return GLDFloatFormating::formatFloat(value, format);

//    GString sValue = GString::number(value, 'g', 14);
//    if (sValue.contains('e') || sValue.contains('E'))
//    {
//        sValue = GString::number(value, 'f', 15);
//    }
//    value = sValue.toDouble();
//    GString result;
//    if (format.toLower().contains('e'))
//    {
//        // todo
//    }
//    else if (format.contains(','))
//    {
//        int nPos = pos(".", format);
//        int nAfter = format.length() - 1 - nPos;
//        int nCommaPos = format.lastIndexOf(',');
//        GString strAfterDot;
//        if (nPos > 0)
//        {
//            int nIndex = sValue.indexOf('.');
//            if (nIndex > 0)
//            {
//                strAfterDot = copy(sValue, sValue.indexOf('.') + 1);
//            }
//            else
//            {
//                strAfterDot = "";
//            }
//            sValue = GString::number(trunc(abs(value)));
//        }
//        else
//        {
//            sValue = GString::number(qRound(abs(value)));
//            strAfterDot = "";
//        }
//        if (nPos > 0)//С�����ĸ�ʽ����
//        {
//            if (nAfter >= strAfterDot.length())
//            {
//                strAfterDot = makeUpZero(format, strAfterDot, nAfter);
//            }
//            else //��ȡС��,�������봦��
//            {
//                double dValue = strToInt64(strAfterDot);
//                long long llValue = pow(10.0, strAfterDot.length() - nAfter);
//                dValue = dValue / llValue;
//                long long nTrancValue = trunc(dValue);
//                GString strTrancValue = GString::number(nTrancValue);
//                strAfterDot = GString::number(qRound(dValue));
//                if (strTrancValue.length() < strAfterDot.length())
//                {
//                    strAfterDot = "";
//                    sValue = GString::number(strToInt64(sValue) + 1);
//                    strAfterDot = makeUpZero(format, strAfterDot, nAfter);
//                }
//                else
//                {
//                    int nLen = nAfter - strAfterDot.length();
//                    for (int i = 0; i < nLen; i++)
//                    {
//                        strAfterDot = '0' + strAfterDot;
//                    }
//                }
//            }
//        }
//        if (sValue != "")//С����ǰ�ĸ�ʽ����
//        {
//            int nLength;
//            if (nPos > 0)
//            {
//                nLength = nPos - nCommaPos - 1;
//            }
//            else
//            {
//                nLength = format.length() - nCommaPos - 1;
//            }
//            int nSum = sValue.length() / nLength;
//            result = sValue;
//            if (nSum > 0)
//            {
//                int nInsert = sValue.length() % nLength;
//                if (nInsert > 0)
//                {
//                    result = result.insert(nInsert, ',');
//                }
//                for (int i = 0; i < nSum - 1; i++)
//                {
//                    nInsert = nInsert + nLength + 1;
//                    result = result.insert(nInsert, ',');
//                }
//            }
//        }
//        if (value < 0)
//        {
//            result = "-" + result;
//        }
//        if ("" == strAfterDot)
//        {
//            return result;
//        }
//        else
//        {
//            return GString("%1.%2").arg(result).arg(strAfterDot);
//        }
//    }
//    else if (format.contains('.'))
//    {
//        int nPos = pos(".", format);
//        int nPosByValue = pos(".", sValue);
//        int nBefore = nPos;
//        int nAfter = format.length() - 1 - nPos;
//        double dAfterDot = fabs(frac(value));
//        int nAfterDot = int(dAfterDot * power(10, nAfter));
//        int nAfterByValue = sValue.length() - pos('.', sValue) - 1;

//        // valueΪ������0
//        if (!sValue.contains('.'))
//        {
//            result = GString("%1.%2").arg(trunc(value), nBefore, 'f', 0, '0').arg(nAfterDot, nAfter, 'f', 0, '0');
//        }
//        else
//        {
//            // value����Ч���Ƚ�С��0
//            if (nAfterByValue < nAfter)
//            {
//                GString strTmp(nAfter - nAfterByValue, '0');
//                result = GString("%1").arg(trunc(value), nBefore, 'f', 0, '0') + sValue.mid(nPosByValue) + strTmp;
//            }
//            else if (nAfter <= zeroNumberAfterDot(sValue))
//            {
//                result = GString("%1").arg(trunc(value), nBefore, 'f', 0, '0');
//            }
//            // ֱ��ɾ��β��
//            else
//            {
//                long long lValue = pow(10.0, nAfter);
//                double dValue = sValue.toDouble();
//                dValue = dValue * lValue;
//                GString strTrans = QString::number(trunc(dValue));
//                int nRoundValue = qRound(dValue);
//                GString strRound = GString::number(nRoundValue);
//                dValue = nRoundValue * 1.0 / lValue;
//                sValue = GString::number(dValue);
//                if (strTrans.length() < strRound.length())
//                {
//                    sValue = "";
//                    result = GString("%1").arg(trunc(value + 1), nBefore, 'f', 0, '0');
//                }
//                else
//                {
//                    result = GString("%1").arg(trunc(value), nBefore, 'f', 0, '0');
//                }
//                nPosByValue = 0;
//                if (sValue != "")
//                {
//                    nPosByValue = pos(".", sValue);
//                    if (nPosByValue > 0)
//                    {
//                        sValue = sValue.mid(nPosByValue + 1);
//                    }
//                }
//                int nCount = rightZeroNumber(format) - sValue.length() - 1;
//                for (int i = 0; i < nCount; i++)
//                {
//                    sValue += '0';
//                }
//                if (sValue != "")
//                {
//                    result = GString("%1.%2").arg(result).arg(sValue);
//                }
//                else
//                {
//                    return result;
//                }
//            }
//        }

//        if (format.at(format.length() - 1) == '#')
//        {
//            result = copy(result, 0, result.length() - rightZeroNumber(result));
//        }
//        if ((result.length() > 1) && ((format.at(0) == '#') || (format.at(0) == '.')))
//        {
//            result = copy(result, leftZeroNumber(result));
//        }
//        if (value < 0)
//        {
//            result = "-" + result;
//        }
//        return result;
//    }
//    else
//    {
//        // todo
//    }
//    return result;
}


GRgb turnRgb(GRgb rgb)
{
    return ((rgb & 0xff) << 16) | (rgb & 0xff00) | ((rgb & 0xff0000) >> 16);
}
