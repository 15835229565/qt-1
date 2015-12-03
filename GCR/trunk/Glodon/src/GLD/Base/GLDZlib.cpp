#include "GLDZlib.h"

#include <QTemporaryFile>
#include <QDebug>
#ifndef WIN32
#   undef FAR
#   define FAR
#endif
#include "zlib.h"
#include "GLDStream.h"
#include "GLDSysUtils.h"
#include "GLDException.h"
#include "GLDStreamUtils.h"

const int c_fragment_length_7z = 0x100000;   //7zѹ����ѹ���ķ�Ƭ��С

////////////////////////////////////////////////////////////////////////////////
//���:����һ�������࣬�����û�����������ù���������̬�����������β��죬�û�����֪��������չ
//����:�����û�����Ĳ���(�ļ���/�ļ���С)�������ļ�����ȱʡ���ļ���С����16Mʱ�������ڴ���
//������strFileName �����ļ���
//     strDirName  ����Ŀ¼��
//     strFileName �����ļ���׺
//     nFragSize   ��Ƭ��С���������˴�С���ļ������ļ������˲�����bUseFileStreamFlag��Ч��������
//     bUseFileStreamFlag  �Ƿ�������ʱ�ļ��������
////////////////////////////////////////////////////////////////////////////////
GStreamStrategy::GStreamStrategy(const GString &strFileName, const GString &strDirName, const GString &strSuffix, bool bUseFileStreamFlag, gint64 nFragSize) //16M
{
    if (false == bUseFileStreamFlag)
    {
        m_stream = new GBlockMemoryStream(GStream::ReadWrite);
        m_stream->open(GStream::ReadWrite);
        return;
    }

    setStreamFragmentSize(nFragSize);

    GFileStream fileStream(strDirName + strFileName);
    if (fileStream.exists())
    {
         fileStream.open(GFileStream::ReadOnly);
    }

    gint64 nStreamSize = fileStream.size();

    if (nStreamSize == 0)
    {
        m_stream = NULL;
    }
    else if (nStreamSize <= streamFragmentSize())
    {
        m_stream = new GBlockMemoryStream(GStream::ReadWrite);
        m_stream->open(GStream::ReadWrite);
    }
    else
    {
        //��ϵͳ��ʱĿ¼������ʱ�ļ�
        this->createFileInDir(strFileName + strSuffix);
    }
}
////////////////////////////////////////////////////////////////////////////////
//���:����һ�������࣬�����û�����������ù���������̬�����������β��죬�û�����֪��������չ
//����:�����û�����Ĳ���(�ļ���/�ļ���С)�������ļ��������ļ���С����16Mʱ�������ڴ���
//������strFileName �����ļ���
//     nStreamSize �����ļ���С
//     strSuffix   �����ļ���׺
//     nFragSize   ��Ƭ��С���������˴�С���ļ������ļ������˲�����bUseFileStreamFlag��Ч��������
//     bUseFileStreamFlag  �Ƿ�������ʱ�ļ��������
////////////////////////////////////////////////////////////////////////////////
GStreamStrategy::GStreamStrategy(const GString &strFileName, gint64 nStreamSize, const GString &strSuffix, bool bUseFileStreamFlag, gint64 nFragSize)
{
    if (false == bUseFileStreamFlag)
    {
        m_stream = new GBlockMemoryStream(GStream::ReadWrite);
        m_stream->open(GStream::ReadWrite);
        return;
    }

    setStreamFragmentSize(nFragSize);

    if (nStreamSize <= streamFragmentSize())
    {
        m_stream = new GBlockMemoryStream(GStream::ReadWrite);
    }
    else
    {
        this->createFileInDir(strFileName + strSuffix);
    }
}

////////////////////////////////////////////////////////////////////////////////
//���: �����û�ָ���ķ�Ƭ��С����Ƭ������
//����: �����û�ָ���ķ�Ƭ��С����Ƭ������������ָ����С���ݵ��������
//������ inStream          ������
//      OutStream         �����
//      nFragmentLength   ��Ƭ����
//      nCopySize         �����ĳ���
////////////////////////////////////////////////////////////////////////////////
void GStreamStrategy::copyStreamByFragment(GStream *outStream, GStream *inStream, uint nFragmentLength, gint64 nCopySize)
{
    assert(nFragmentLength != 0);

    uint nCount  = nCopySize / nFragmentLength;

    for (uint i = 0; i < nCount; ++i)
    {
        outStream->write(inStream->read(nFragmentLength));
    }
    outStream->write(inStream->read(nCopySize % nFragmentLength));
}

////////////////////////////////////////////////////////////////////////////////
//���:����ָ��·�������ļ�����������ڵĻ���
//����:����ָ��·�������ļ�����������ڵĻ�����Ŀǰ����������ʱ���ã�������չ������ָ��Ŀ¼
//     ����ָ�������ļ�
//������strFileName  �ļ���
////////////////////////////////////////////////////////////////////////////////
void GStreamStrategy::createFileInDir(const GString &strFileName)
{
    try
    {
        QTemporaryFile *tempFile = new QTemporaryFile("compressXXXXXX.tmp");
        m_stream = tempFile;
        m_stream->open(GFileStream::ReadWrite);
        tempFile->setAutoRemove(true);
    }

    catch (...)
    {
        throw GLDException("Internal Error: create file:"  + strFileName + "failed!");
    }
}

/* CGLDZlib */
CGLDZlib::CGLDZlib()
{

}

CGLDZlib::~CGLDZlib()
{
}

////////////////////////////////////////////////////////////////////////////////
//���: ѹ�������������û������hasZlibHeaderFlag�ж��������ֵΪ1���򲻴�zlibѹ��ͷ��ѹ�������outStream
//����: ѹ���û������ԭʼ���ݣ����ѹ��������ݣ�ѹ��������ݰ���zlibѹ��ͷ��
//������inStream  �����ԭʼ����
//     outStream �����ԭʼ����
//     hasZlibHeaderFlag  Ϊtrueʱ�����������zlibѹ��ͷ�� falseʱ�����������ѹ��ͷ
////////////////////////////////////////////////////////////////////////////////
int CGLDZlib::newCompress(GStream *inStream, GStream *outStream, bool hasZlibHeaderFlag)
{
    int nRet = -1;
    int nnflush = -1;
    bool zlibHeaderFlag = hasZlibHeaderFlag;
    z_stream zcpr;
    const int c_DefMaxBufSize = 0x10000;
    Bytef *compressPtr = (Bytef *)malloc(sizeof(c_DefMaxBufSize) * (c_DefMaxBufSize + 1));
    unsigned long ninputSize = inStream->size();
    inStream->seek(0);
    /* allocate deflate state */
    zcpr.zalloc = Z_NULL;
    zcpr.zfree = Z_NULL;
    zcpr.opaque = Z_NULL;
    nRet = deflateInit(&zcpr, Z_DEFAULT_COMPRESSION);
    zcpr.next_out = compressPtr;
    if (nRet != Z_OK)
        return nRet;

    while (ninputSize != 0)
    {
        int ntmpSize = 0;
        if (ninputSize > c_DefMaxBufSize)
        {
            ntmpSize = c_DefMaxBufSize;
            ninputSize = ninputSize - c_DefMaxBufSize;
            nnflush = Z_NO_FLUSH;
        }
        else
        {
            ntmpSize = ninputSize;
            nnflush = Z_FINISH;
            ninputSize = 0;
        }

        GByteArray in = inStream->read(ntmpSize);

        zcpr.next_in = (Bytef *)(in.data());
        long lToDo = ntmpSize;
        long lReadBefore = 0;
        long lReadOutBefore = 0;
        do
        {
            lReadBefore = zcpr.total_in;
            lReadOutBefore = zcpr.total_out;
            zcpr.avail_in = lToDo > c_DefMaxBufSize? c_DefMaxBufSize : lToDo;
            zcpr.avail_out = c_DefMaxBufSize;
            nRet = deflate(&zcpr, nnflush);
            if (zlibHeaderFlag)
            {
                outStream->write((const char *)compressPtr, zcpr.total_out - lReadOutBefore);
            }
            else
            {
                outStream->write((const char *)compressPtr + ZLIB_HEADER_LENGTH, zcpr.total_out - lReadOutBefore - ZLIB_HEADER_LENGTH);
                zlibHeaderFlag = true ;
            }

            lToDo -= (zcpr.total_in - lReadBefore);
            zcpr.next_out = compressPtr;

        } while (nRet == Z_OK);
    }
    if (nRet >= 0)
    {
        deflateEnd(&zcpr);
    }
    freeAndNil(compressPtr);
    return nRet;
}
////////////////////////////////////////////////////////////////////////////////
//���: ��ѹ�������������û������zlibHeader��������inStream��ӻ����zlibѹ��ͷ
//����: ��ѹ�û������ѹ�����ݣ������ѹ�����ݸ��û�
//������inStream �û������ѹ������
//     outStream ����Ľ�ѹ������
//     zlibHeader zlibѹ��ͷ�������inStream�Ѱ���ѹ��ͷʱ���ò�����մ�
////////////////////////////////////////////////////////////////////////////////
bool CGLDZlib::unCompress(GStream *inStream, GStream *outStream, GByteArray zlibHeader)
{
    bool bResult = false;
    bool zlibHeaderFlag = false;
    int zlibHeaderLen  = ZLIB_HEADER_LENGTH;

    if (inStream == NULL)
        return bResult;

    const uint c_DefMaxBufSize = 0xf000; 
    const uint c_DefMaxInBufSize = 65536;
    z_stream zcpr;
    memset(&zcpr, 0, sizeof(z_stream));
    // ��ʼ��
    inflateInit(&zcpr);
    Bytef *unCompressPtr = (Bytef *)malloc(sizeof(c_DefMaxBufSize) * (c_DefMaxBufSize + 1));

    if (zlibHeader.isEmpty())
    {
        zlibHeaderFlag = true;
        zlibHeaderLen  = 0;
    }

    GByteArray oTempArray(zlibHeader);
    zcpr.next_out = unCompressPtr;

    int nRet = Z_OK;
    ULONG lInStreamSize = inStream->size() + zlibHeaderLen;
    ULONG lTempLength = 0;

    // ���������û�ж��꣬��һֱѭ����ȡ
    // ������ò�Ҫseek 0
    inStream->seek(0);
    ULONG lReadBefore = 0;
    ULONG lReadOutBefore = 0;
    int i = 0;
    int j = 0;
    while (lInStreamSize > 0)
    {
        i++;
        if (lInStreamSize > c_DefMaxBufSize)
        {
            lTempLength = c_DefMaxBufSize;
            lInStreamSize = lInStreamSize - c_DefMaxBufSize;
            nRet = Z_NO_FLUSH;
        }
        else
        {
            lTempLength = lInStreamSize;
            lInStreamSize = 0;
            nRet = Z_FINISH;
        }

        // һ��һ�ζ�ȡ����ֹGByteArray���
        if (zlibHeaderFlag)
        {
            oTempArray.clear();
            oTempArray = inStream->read(lTempLength);
        }
        else
        {
            oTempArray.append(inStream->read(lTempLength - zlibHeaderLen));
            zlibHeaderFlag = true ;
        }

        zcpr.next_in = (Bytef *)(oTempArray.data());

        long lToDo = lTempLength;
        do
        {
            j++;
            zcpr.avail_out = c_DefMaxBufSize;
            nRet = Z_OK;

            // ��һ�ִ����ĳ���
            lReadBefore = zcpr.total_in;
            lReadOutBefore = zcpr.total_out;

            int nPreOutOfTemp = 0;
            int nPreInOfTemp = 0;
            int nCurOutOfTemp = 0;
            while ((zcpr.avail_out > 0) && (nRet != Z_STREAM_END))
            {
                // ��һ����ѭ���У����ÿռ�϶���0����Ҫ����ռ䣬������洦��
                // ��������Ѿ������꣬ҲӦ����0�������Ҫ�����ж�
                if (0 == zcpr.avail_in)
                {
                    zcpr.avail_in =
                            lToDo > long(c_DefMaxInBufSize) ? c_DefMaxInBufSize : lToDo;
                }
                // �����ֱ꣬��Break
                if (0 == zcpr.avail_in)
                {
                    break;
                }

                // �Ѿ�����ĳ���
                nPreInOfTemp = zcpr.total_in - lReadBefore;
                // �Ѿ�����ĳ���
                nPreOutOfTemp = zcpr.total_out - lReadOutBefore;
                // ���ִ���ĳ��ȳ�ʼ��Ϊ0
                nCurOutOfTemp = 0;

                // ��ѹ������
                nRet = inflate(&zcpr, Z_NO_FLUSH);

                if (nRet < 0)
                    break;

                lToDo = lToDo - (zcpr.total_in - lReadBefore);
                nCurOutOfTemp = zcpr.total_out - lReadOutBefore - nPreOutOfTemp;
                zcpr.next_in = (Bytef *)(oTempArray.data() + (lTempLength - lToDo));
            }

            zcpr.next_out = unCompressPtr;
            outStream->write((const char *)unCompressPtr, nCurOutOfTemp);

        } while (zcpr.total_out - lReadOutBefore == c_DefMaxBufSize);
    }

    if (nRet >= 0)
    {
        inflateEnd(&zcpr);
        bResult = true;
    }
    freeAndNilByGFree(unCompressPtr);

    return bResult;
}
////////////////////////////////////////////////////////////////////////////////
//���: �����ѹ���������û�������inStream�Ѱ���zlibѹ��ͷ
//����: ��ѹ�û��������е�ѹ�����ݣ������ѹ�����ݸ��û�
//������inStream �����ѹ��������ָ��
//     bUseFileStreamFlag �Ƿ������ļ����淽ʽ���������˷�ʽ����������ļ����ڷ�Ƭ��С
//     ��ȱʡ16M�����򽫷����ļ����洢��ѹ��������ݣ����ظ��û�
////////////////////////////////////////////////////////////////////////////////
GStream* CGLDZlib::unCompress(GStream *inStream, bool bUseFileStreamFlag)
{
    if (inStream == NULL)
    {
        return false;
    }

    GStreamStrategy StreamStrategyTemp("_temp", inStream->size(),  "_temp_unzip", bUseFileStreamFlag);
    GStream *outStream = StreamStrategyTemp.stream();

    //�û�������inStream�Ѱ���zlibѹ��ͷ,������������մ�
    unCompress(inStream, outStream, "");
    if (outStream)
    {
        outStream->seek(0);
    }
    return outStream;
}
////////////////////////////////////////////////////////////////////////////////
//���: �ڲ�ѹ��������ѹ�������outStream������zlibͷ
//����: ѹ���û������ԭʼ���ݣ����ѹ��������ݣ�ѹ��������ݲ�����zlibѹ��ͷ����Ҫ��zipfile���ã�
//     winzip�ȵ��������߼�ѹʱ�����ѹ�����ݰ�����zilbͷ�����ѹʧ��
//������inStream  �����ԭʼ����
//     outStream �����ԭʼ����
////////////////////////////////////////////////////////////////////////////////
bool CGLDZlib::compress(GStream *inStream, GStream *outStream)
{
    if (inStream == NULL)
    {
        return false;
    }

    //�����outStream����Ҫ����zlibѹ��ͷ,������������false
    newCompress(inStream, outStream, false);
    if (outStream)
    {
        outStream->seek(0);
    }
    return true;
}
////////////////////////////////////////////////////////////////////////////////
//���:����ѹ�����������ز������������zlibѹ��ͷ
//����: ѹ���û������ԭʼ���ݣ����ѹ��������ݣ�ѹ��������ݰ���zlibѹ��ͷ��
//������inStream  �����ԭʼ����
//     bUseFileStreamFlag �Ƿ������ļ����淽ʽ���������˷�ʽ����������ļ����ڷ�Ƭ��С
//     ��ȱʡ16M�����򽫷����ļ����洢ѹ��������ݣ����ظ��û�
////////////////////////////////////////////////////////////////////////////////
GStream* CGLDZlib::compress(GStream *inStream, bool bUseFileStreamFlag)
{
    if (inStream == NULL)
    {
        return false;
    }

    GStreamStrategy StreamStrategyTemp("_temp", inStream->size(), "_temp_zip", bUseFileStreamFlag);
    GStream *outStream = StreamStrategyTemp.stream();

    //����ѹ�����������ز���outStream���������zlibѹ��ͷ
    newCompress(inStream, outStream, true);
    if (outStream)
    {
        outStream->seek(0);
    }
    return outStream;
}

#ifdef WIN32
#include "LzmaLib.h"
/* CGLD7Zip */
bool CGLD7Zip::unCompress(GStream *instream, GStream *outStream, int unCompressedSize)
{
    int nOldPos = outStream->pos();
    try
    {
        const unsigned char prop[5] = {93, 0, 0, 0, 1}; //lzma��ѹȱʡ�����������Ҫ��ѹ��ʱ�����proc����ֵһ�£������ѹ��ʧ��

        int nSrcSize = readIntFromStream(instream);
        int nDestLen = -1;
        size_t nRead = instream->read((char *)&nDestLen, sizeof(int));
        while(nRead > 0)
        {
            GByteArray srcRead = instream->read(nDestLen);
            nRead = srcRead.size();

            size_t ndead = nSrcSize;
//            size_t ndead = nRead * 2;
            unsigned char *aucDecomress = (unsigned char *)malloc(ndead);
            int ret = -1;
            if (SZ_OK != (ret = LzmaUncompress(aucDecomress, &ndead, (const uchar *)srcRead.data(), &nRead, prop, 5)))
            {
                //����ռ䲻��
                aucDecomress = (unsigned char *)realloc(aucDecomress, ndead);
                memset(aucDecomress, '\0', ndead);
                if (SZ_OK != (ret = LzmaUncompress(aucDecomress, &ndead, (const uchar *)srcRead.data(), &nRead, prop, 5)))
                {
                    qWarning() << "LzmaUncompress error:" << ret;
                }
            }
            //���LzmaUncompress�ӿ��ڽ�ѹ���һ����Ƭ���ں�߶����һ��0�����⣬������Ҫ�ض϶����ַ���������㺯��У��crc��ʧ��
            if ((outStream->size() + ndead) >= unCompressedSize)
            {
                ndead = unCompressedSize - outStream->size();
                outStream->write((const char *)aucDecomress, ndead);
                break;
            }
            outStream->write((const char *)aucDecomress, ndead);
            nSrcSize = readIntFromStream(instream);
            nRead = instream->read((char *)&nDestLen, sizeof(int));
            free(aucDecomress);
            aucDecomress = NULL;
        }
    }
    catch (...)
    {
        throw;
    }
    outStream->seek(nOldPos);
    return true;
}

GStream *CGLD7Zip::unCompress(GStream *inStream, int unCompressedSize)
{
    GBlockMemoryStream *result = new GBlockMemoryStream;
    unCompress(inStream, result, unCompressedSize);
    return result;    
}

bool CGLD7Zip::compress(GStream *instream, GStream *outStream)
{
    size_t nDestLen = c_fragment_length_7z * 2;
    size_t nSizeProp = 5; //LzmaCompress����aucProp�ĳ���
    int ret;
    unsigned char aucProp[5] = {0};
    GByteArray srcRead;
    unsigned char *aucLzma = new unsigned char[c_fragment_length_7z * 2] ;

    int nOldPos = outStream->pos();
    int nCount = (instream->size() - instream->pos() + c_fragment_length_7z - 1) / c_fragment_length_7z; //�����Ƭ����������һ����һ��
    for (int i = 0; i < nCount; ++i)
    {
        srcRead = instream->read(c_fragment_length_7z);
        nDestLen = c_fragment_length_7z * 2;

        memset(aucProp, 0, sizeof(aucProp));

        int nSrcSize = srcRead.size();
        if (SZ_OK != (ret = LzmaCompress(aucLzma, &nDestLen, (const uchar *)srcRead.data(), nSrcSize,
                                         aucProp, &nSizeProp, 0, (1 << 24), 3, 0, 2, 32, 2)))
        {
            outStream->seek(nOldPos);
            return false;
        }

        writeIntToStream(outStream, nSrcSize);
        writeIntToStream(outStream, nDestLen);
        outStream->write((const char *)aucLzma, nDestLen);
    }
    outStream->seek(nOldPos);
    delete(aucLzma);
    return true;
}

GStream *CGLD7Zip::compress(GStream *inStream)
{
    GBlockMemoryStream *result = new GBlockMemoryStream;
    compress(inStream, result);
    return result;
}
#endif

/* CGLDAutoCompress */
GStream *CGLDAutoCompress::unCompress(GStream *inStream)
{
    return CGLDZlib::unCompress(inStream);

    int nOldPos = inStream->pos();
    char szLength = readByteFromStream(inStream);
    inStream->seek(nOldPos);
    if (szLength == strlen("_7zip_"))
    {
        GString id = readStrFromStream(inStream);
        if (sameText(id, "_7zip_"))
        {
#ifdef WIN32
            return CGLD7Zip::unCompress(inStream, readIntFromStream(inStream));
#else
            assert(false);
#endif
        }
        inStream->seek(nOldPos);
    }
    return CGLDZlib::unCompress(inStream);
}

GStream *CGLDAutoCompress::compress(GStream *inStream)
{
    return CGLDZlib::compress(inStream);

#ifdef WIN32
    GBlockMemoryStream *result = new GBlockMemoryStream;

    writeStrToStream(result, "_7zip_");
    writeIntToStream(result, inStream->size() - inStream->pos());

    CGLD7Zip::compress(inStream, result);

    result->seek(0);
    return result;
#else
    return CGLDZlib::compress(inStream);
#endif
}
