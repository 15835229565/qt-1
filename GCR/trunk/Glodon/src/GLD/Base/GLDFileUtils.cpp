/*************************************************************************
*                                                                        *
*   �������ļ�����ع���������Ԫ CPP                                          *
*                                                                        *
*   ��ƣ�Zhangsk 2012.05.21                                              *
*   ��ע��                                                                *
*   ��ˣ�                                                                *
*                                                                        *
*   Copyright (c) 2012-2013 Glodon Corporation                           *
*                                                                        *
*************************************************************************/

#include "GLDFileUtils.h"
#include <QCoreApplication>
#include <QProcess>
#include <QTemporaryFile>
#include "GLDDir.h"
#include "GLDFile.h"
#include "GLDFileInfo.h"
#include "GLDException.h"
#include "GLDGlobal.h"
#include "GLDSysUtils.h"

#ifdef WIN32
#include <ShlObj.h>
#endif

G_GLODON_BEGIN_NAMESPACE
G_GLODON_END_NAMESPACE

/*************************************************************************
  ���ߣ� yanyq-a 2013-07-31
  ������ ��
  ���أ� GString
  ���ܣ� ��ȡexe�ļ���������
*************************************************************************/
GString exeFullName()
{
#ifdef WIN32
    // ��֧�ֳ�·��??
    wchar_t szModuleName[MAX_PATH + 1] = {0};
    GetModuleFileName(NULL, szModuleName, MAX_PATH + 1);
    GString strPath = GString::fromUtf16((ushort *)szModuleName);
    return strPath;
#else
    return qApp->applicationName();
#endif
}

/*************************************************************************
  ˵�������ص�ǰ����EXE�ļ���·��
  ��������
  ���أ���ǰ����EXE�ļ���·��
*************************************************************************/
GString exePath()
{
    return exeDir() + pathDelim(); //��ȡ��ǰӦ�ó���·��
}

GString exeDir()
{
#ifdef WIN32
    GString strPath = exeFullName();
    int nIndex = strPath.lastIndexOf('\\');
    if (nIndex < 0)
    {
        nIndex = strPath.lastIndexOf('/');
        if (nIndex < 0)
        {
            return GString();
        }
    }
    strPath = strPath.left(nIndex);
    return strPath;
#else
    return QCoreApplication::applicationDirPath(); //��ȡ��ǰӦ�ó���·��
#endif
}

GString moduleName(void *module)
{
    // todo
    return exeFullName();
    G_UNUSED(module)
}

GString getCurrentDir()
{
    return GDir::currentPath();
}

bool isLibrary()
{
    const GString strModuleName = moduleName(NULL);
    const GString strModuleExt = extractFileExt(strModuleName);

    return GString::compare(strModuleExt, ".dll", Qt::CaseInsensitive) == 0;
}

bool fileExists(const GString &fileName)
{
    GFileInfo fileInfo(fileName);

    if (fileInfo.isDir())
    {
        return false;
    }

    return GFile::exists(fileName);
}

GStream *createFileStream(const GString &fileName)
{
    return new GFileStream(fileName);
}

GString extractFileExt(const GString &fileName)
{
    int nIndex = rPos('.', fileName);
    if (nIndex >= 0 && fileName[nIndex] == '.')
    {
        return copy(fileName, nIndex);
    }
    else
    {
        return GString();
    }
}

GString changeFileExt(const GString &fileName, const GString &extension)
{
    GString sFileName = fileName;
    GFileInfo info(sFileName);
    GString sResult(sFileName);
    sResult = sResult.replace(info.suffix(), extension);
    return sResult;
}

/*************************************************************************
 *���ߣ� zhouyl-a 2013-8-8
 *������
 *  1��oldFile : ���������ļ���
 *  2��newFile : ���ļ���
 *  3��failIfExists : ������ʶ; failIfExists == true ��������ļ����ھ�ʧ�ܣ�
 *                            failIfExists == false��������ļ����ھ͸��ǣ�
 *���أ�true �ɹ�, false ʧ��
*************************************************************************/
bool copyFile(const GString &oldFile, const GString &newFile, bool failIfExists)
{
    // ��� failIfExists Ϊ��,��newFile����,ֱ�ӷ���
    if (failIfExists && fileExists(newFile))
    {
        return false;
    }

    // ��� failIfExists Ϊ��,��newFile����
    if (!failIfExists && fileExists(newFile))
    {
        //ɾ��newFile
        GFile::remove(newFile);
    }

    return (GFile::copy(oldFile, newFile));

}

bool deleteFile(const GString &fileName)
{
    if (fileExists(fileName))
    {
        return GFileStream::remove(fileName);
    }
    return false;
}

bool deleteTree(const GString &path)
{
    if (path.isEmpty())
        return false;
    GString strPath = includeTrailingPathDelimiter(path);
    GDir dir(strPath);
    if (!dir.exists())
        return true;

    GFileInfoList fileList = dir.entryInfoList(GDir::AllEntries | GDir::Hidden);
    GString strFileName;
    GString strFile;
    foreach (GFileInfo fileInfo, fileList)
    {
        strFileName = fileInfo.fileName();
        if ((strFileName == GString("..")) || (strFileName == GString(".")))
            continue;
        if (fileInfo.isDir())
        {
            strFile = strPath + strFileName + "/";
            deleteTree(strFile);
        }
        else
        {
            strFile = strPath + strFileName;
            if (!fileInfo.permission(GFileStream::WriteOwner))
            {
                GFileStream file(strFile);
                file.setPermissions(GFileStream::WriteOwner);
            }
            GFileStream::remove(strFile);
        }
    }
    return dir.rmdir(strPath);
}

/*************************************************************************
  ���ߣ� jiangjb 2013-06-04
  ������ const GString &, GStrings &
  ���أ� ��
  ���ܣ� �õ�������Ŀ¼
*************************************************************************/
void findSubFolders(const GString &path, GStrings &folders)
{
    GDir oDir(path);

    oDir.setFilter(GDir::Dirs | GDir::NoDotAndDotDot);
    folders.clear();
    folders = oDir.entryList();
}

/*************************************************************************
  ���ߣ� jiangjb 2013-06-26
  ������ const GString &, const GStrings &, GStrings &
  ���أ� ��
  ���ܣ� ͨ����׺��Ѱ��Ŀ¼���Լ���ǰĿ¼��������Ŀ¼�������ļ�
*************************************************************************/
void findFiles(const GString &path, const GStrings &nameFilters, GStrings &files)
{
    GDir oDir(path);
    oDir.setFilter(GDir::Files | GDir::NoDotAndDotDot);

    if (nameFilters.size() == 1)
    {
        if (!nameFilters.at(0).isEmpty())
        {
            oDir.setNameFilters(nameFilters);
        }
    }
    else
    {
        oDir.setNameFilters(nameFilters);
    }

    GStrings oFiles = oDir.entryList();
    for (int i = 0; i < oFiles.size(); i++)
    {
        files.append(includeTrailingPathDelimiter(path) + oFiles.at(i));
    }

    GStrings oSubFileDirs;
    findSubFolders(path, oSubFileDirs);
    for (int i = 0; i < oSubFileDirs.size(); i++)
    {
        findFiles((includeTrailingPathDelimiter(path) + oSubFileDirs.at(i)), nameFilters, files);
    }
}

/*************************************************************************
  ���ߣ� jiangjb 2013-06-26
  ������ const GString &, GStrings &, const GString &
  ���أ� ��
  ���ܣ� ͨ����׺��Ѱ��Ŀ¼���Լ���ǰĿ¼��������Ŀ¼�������ļ�
*************************************************************************/
void findFiles(const GString &path, const GString &nameFilter, GStrings &files)
{
    GStrings oNameFilters;
    if (nameFilter.isEmpty())
    {
        oNameFilters.append("*.*");

    }
    else
    {
        oNameFilters.append(nameFilter);
    }

    findFiles(path, oNameFilters, files);
}

/*************************************************************************
  ���ߣ� jiangjb 2013-06-26
  ������ const GString &, GStrings &, const GString &, bool
  ���أ� ��
  ���ܣ� ͨ����׺��Ѱ�ҵ�ǰĿ¼�������ļ�
*************************************************************************/
void getFiles(const GString &path, GStrings &files, const GString &nameFilter)
{
    GStrings oNameFilters;
    if (nameFilter.isEmpty())
    {
        oNameFilters.append("*.*");

    }
    else
    {
        oNameFilters.append(nameFilter);
    }

    getFiles(path, oNameFilters, files);
}

void getFiles(const GString &path, const GStrings &nameFilters, GStrings &files, bool includeDir)
{
    GDir oDir(path);
    if (includeDir)
    {
        oDir.setFilter(GDir::Files | GDir::Dirs | GDir::NoDotAndDotDot);
    }
    else
    {
        oDir.setFilter(GDir::Files | GDir::NoDotAndDotDot);
    }

    if (nameFilters.size() == 1)
    {
        if (!nameFilters.at(0).isEmpty())
        {
            oDir.setNameFilters(nameFilters);
        }
    }
    else
    {
        oDir.setNameFilters(nameFilters);
    }

    files.append(oDir.entryList());
}

/*************************************************************************
  ���ߣ� yanyq-a 2013-07-31
  ������ GString&
  ���أ� GString
  ���ܣ� ��ȡ����ϵͳ�ɽ��ܵ��ļ���(��ӦԭGetValidFileName)
*************************************************************************/
GString getValidFileName(const GString &fileName)
{
    GStrings oInvalidChars = (GStrings() << "\\" << "/" << ":" << "\"" << ">" << "<" << "\r\n" << "|" << "?" << "*");
    GString sValidFileName(fileName);
    for (int i = 0; i < oInvalidChars.count(); ++i)
    {
        sValidFileName.replace(oInvalidChars[i], "_", Qt::CaseInsensitive);
    }

    return sValidFileName;
}

bool createDir(const GString &path)
{
    GDir oDir;
    return oDir.mkdir(path);
}

bool forceDirectories(const GString &path)
{
    if (path.isEmpty())
        return false;
    GString strDir = excludeTrailingPathDelimiter(path);
    GDir oDir(strDir);
    if (oDir.exists())
        return true;
    return oDir.mkpath(strDir);
//    GString strParentDir = extractFilePath(strDir);
//    if (sameText(strParentDir, strDir))
//        return true;
//    return forceDirectories(strParentDir) && oDir.mkdir(strDir);
}

bool directoryExists(const GString &path)
{
    if (path.isEmpty())
    {
        return false;
    }
    GDir oDir(path);
    return oDir.exists();
}

GString extractFilePath(const GString &fileName)
{
    int nIndex = pathDelimPos(fileName);
    if (nIndex >= 0)
        return copy(fileName, 0, nIndex + 1);
    else
    {
        return GString();
    }
}

/*************************************************************************
  ���ߣ� jiangjb 2013-06-20
  ������ const GString &
  ���أ� GString
  ���ܣ� ���ļ����л�ȡĿ¼��(�ļ����ڸ�Ŀ¼��ʱȡ�õ�ֵ��û�С�/�����ڸ�Ŀ¼ʱһ���������̷������硰C:/��)
*************************************************************************/
GString extractFileDir(const GString &fileName)
{
    int nIndex = pathDelimPos(fileName);
    if (nIndex >= 0)
    {
        if ((nIndex >= 1) && (fileName[nIndex - 1] == driveDelim()))
        {
            ++nIndex;
        }
        return copy(fileName, 0, nIndex);
    }
    else
        return GString();
}

GString extractFileName(const GString &fileName)
{
    int nIndex = pathDelimPos(fileName);
    return copy(fileName, nIndex + 1);
}

GString extractFileNameOnly(const GString &fileName)
{
    GString result = extractFileName(fileName);
    int nDotPos = rPos(GChar('.'), result);
    if (nDotPos >= 0)
        return copy(result, 0, nDotPos);
    else
        return result;
}

// ���·��ת��Ϊ����·��
GString expandFileName(const GString &fileName)
{
    GFileInfo oFileInfo(fileName);
#ifdef WIN32
    return oFileInfo.absoluteFilePath().replace(GChar('/'), pathDelim());
#else
    return oFileInfo.absoluteFilePath();
#endif
}

/*************************************************************************
  ���ߣ� jiangjb 2013-06-14
  ������ const GString &, bool
  ���أ� ��
  ���ܣ� �����ļ�ֻ��
*************************************************************************/
void fileSetReadOnly(const GString &fileName, bool readOnly)
{
    if (readOnly)
    {
        GFileStream::setPermissions(fileName, GFileStream::ReadOther);
    }
    else
    {
        GFileStream::setPermissions(fileName, GFileStream::WriteOther | GFileStream::ReadOther);
    }
}

/*************************************************************************

  ���ߣ�liudi 2013 ԭ���ߣ�
  ������const GString &fileName
  ���أ�gint64
  ����: �����ļ���С

  �������ԭ����TGBQ4ZipFileUtils��
*************************************************************************/
gint64 getFileSize(const GString &fileName)
{
    GFileInfo fileInfo(fileName);

    return fileInfo.size();
}

/*************************************************************************
  ���ߣ� zhangjq 2013-09-25
  ������ path������·����productName����ǰ��Ʒ���ƣ�version����ǰ��Ʒ�汾
        xxxx\CompanyName\ProductName\ProductVersion
  ���أ�
  ���ܣ� ���ط��Ϲ�˾�淶���ļ�·��
*************************************************************************/
GString getProductPath(const GString &path, const GString &productName, const GString &version)
{
    return GString("%1GrandSoft\\%2\\%3").arg(includeTrailingPathDelimiter(path), productName, version);
}

GString getCommonDocumentsPath()
{
#ifdef Q_OS_WIN
    return getSpecialFolderPath(CSIDL_COMMON_DOCUMENTS);
#else
    return GString("");
#endif
}

GString getTempFile(const GString &prefix, const GString &path)
{
    QTemporaryFile tempFile(includeTrailingPathDelimiter(path) + prefix + "XXXXXX.tmp");
    tempFile.setAutoRemove(false);
    if (tempFile.open())
    {
        GString result = tempFile.fileName();
        tempFile.close();
        return result;
    }
    return GString();
}

int pathDelimPos(const GString &fileName)
{
    int nPathDelimPos = rPos(pathDelim(), fileName);
    int nBackSlashPos = rPos(backSlashDelim(), fileName);
    return (nPathDelimPos > nBackSlashPos ? nPathDelimPos : nBackSlashPos);
}

GString getCommandLineOutput(
        const GString &commandLine, const GString &workDir, int &exitCode)
{
    QProcess process;
    //process.setReadChannel(QProcess::StandardOutput);
    //process.setReadChannelMode(ForwardedChannels);
    process.setWorkingDirectory(workDir);
    process.start(commandLine);
    if (!process.waitForFinished(-1))
    {
        exitCode = -2;
        return GString();
    }
    if (process.exitStatus() == QProcess::NormalExit)
    {
        exitCode = process.exitCode();
        GByteArray array = process.readAllStandardOutput();
        return GString::fromLocal8Bit(array.constData());
    }
    else
    {
        exitCode = -1;
        return GString();
    }
}

GString loadQssFile(const GString &fileName)
{
    GFile oQssFile(fileName);
    if (!oQssFile.open(QIODevice::ReadOnly))
    {
        return QString();
    }
    else
    {
        return oQssFile.readAll();
    }
}
