#ifndef GLDZLIB_H
#define GLDZLIB_H

#include "GLDTypes.h"
#include "GLDStream.h"
#include "GLDZip_Global.h"

#define FRAGMENT_LENGTH_ZIP 0x100000  //16M, ���ļ�����16Mʱ�������ļ������棬�������ڴ���
#define FRAGMENT_LENGTH_7Z  0x10000   //7zѹ����ѹ���ķ�Ƭ��С
#define ZLIB_HEADER_LENGTH  2         //zlibͷ����

////////////////////////////////////////////////////////////////////////////////
//���:����һ�������࣬�����û�����������ù���������̬�����������β��죬�û�����֪��������չ
//����:�����û�����Ĳ���(�ļ���/�ļ���С)�������ļ��������ļ���С����16Mʱ�������ڴ���
////////////////////////////////////////////////////////////////////////////////
class GStreamStrategy
{
public:
    void setStreamFragmentSize(gint64 nFragmentSize)
    {
        m_nFragMentSize = nFragmentSize;
    }
    gint64 streamFragmentSize()
    {
        return m_nFragMentSize;
    }
    GStream * stream()
    {
        return m_stream;
    }
    static void copyStreamByFragment(GStream *outStream, GStream *inStream, uint nFragmentLength, gint64 nCopySize);
    void createFileInDir(const GString &strFileName);

private:
    GStreamStrategy(const GString &strFileName, const GString &strDirName, const GString &strSuffix = "", bool bUseFileStreamFlag = true, gint64 nFragSize = 0x1000000);//16M
    GStreamStrategy(const GString &strFileName, gint64 streamSize, const GString &strSuffix = "", bool bUseFileStreamFlag = true, gint64 nFragSize = 0x1000000);

private:
    GStream *m_stream ; // ��ָ��
    gint64  m_nFragMentSize; //��Ƭ��С���û�����ָ���������˴�С������Ҫ�����ļ��������򴴽����ڴ�
    friend class CGLDZlib;
    friend class CGLDZipFileEntry;
};

class GLDZIPSHARED_EXPORT CGLDZlib
{
public:
    CGLDZlib();
    virtual ~CGLDZlib();
    static bool compress(GStream *inStream, GStream *outStream);
    static GStream* compress(GStream *inStream, bool bUseFileStreamFlag = true);
    static bool unCompress(GStream *inStream, GStream *outStream, GByteArray zlibHeader = "");
    static GStream* unCompress(GStream *inStream, bool bUseFileStreamFlag = true);
    static int newCompress(GStream *inStream, GStream *outStream, bool hasZlibHeaderFlag = true);
};

#ifdef WIN32
class GLDZIPSHARED_EXPORT CGLD7Zip
{
public:
    CGLD7Zip() {}
    virtual ~CGLD7Zip() {}
    // ���ⲿ����outStream
    static GStream* compress(GStream *inStream);
    static GStream* unCompress(GStream *inStream, int unCompressedSize = 0);
private:
    static bool compress(GStream *instream, GStream *outStream);
    static bool unCompress(GStream *instream, GStream *outStream, int unCompressedSize = 0);
    friend class CGLDAutoCompress;
};
#endif

class GLDZIPSHARED_EXPORT CGLDAutoCompress
{
public:
    CGLDAutoCompress() {}
    virtual ~CGLDAutoCompress() {}
    // ���ⲿ����outStream
    static GStream* compress(GStream *inStream);
    static GStream* unCompress(GStream *inStream);
};

#endif // GLDZLIB_H
