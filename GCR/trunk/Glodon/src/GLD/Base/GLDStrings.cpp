#include "GLDStrings.h"
#include <QCoreApplication>

const char *g_InvalidInteger			 = QT_TRANSLATE_NOOP("GLD", "Invalid integer [%s]");// "�Ƿ�����ֵ[%s]");
const char *g_InvalidFloat			 = QT_TRANSLATE_NOOP("GLD", "Illegal floating number [%s]");// "�Ƿ�������[%s]");
const char *g_InvalidGUID			 = QT_TRANSLATE_NOOP("GLD", "Invalid GUID[%s]");// "�Ƿ�GUIDֵ[%s]");
const char *g_InvalidTypeCompare		 = QT_TRANSLATE_NOOP("GLD", "Types dosn`t match");// "���Ͳ�ƥ��");

const char *g_rsInvalidBase64Data		 = QT_TRANSLATE_NOOP("GLD", "Invalid Base64 Data");// "�ַ��������ʽ�Ƿ�");
const char *g_rsInvalidTimeFormat		 = QT_TRANSLATE_NOOP("GLD", "\'%1\'is not a valid date and time");// "\'%s\' ���ǺϷ�������ʱ��");

const char *g_MissingExtPropCode      = QT_TRANSLATE_NOOP("GLD", "Extended attribute code cannot be null");// "��չ���Դ��벻��Ϊ��");
const char *g_ExtPropCodeExist        = QT_TRANSLATE_NOOP("GLD", "Extended attribute code[%1] is repeated");// "��չ���Դ���[%s]�ظ�");

const char *g_InvalidFieldName		 = QT_TRANSLATE_NOOP("GLD", "Invalid Edit Field Name[%1] of Table[%2]");// "��[%s]�Ƿ��༭�ֶ���[%s]");
const char *g_NeedRunState			 = QT_TRANSLATE_NOOP("GLD", "This Operation Can Only Be Used in Running Status");// "�ò���ֻ��������״̬��ʹ��");
const char *g_InvalidFieldNameMark	 = QT_TRANSLATE_NOOP("GLD", "Table [%1] has illegal field name [%2]");// "��[%s]�Ƿ��ֶ�����[%s]��\"&\"�����Ϊö���ֶΡ����ʽ�ֶΡ�ʱ�������ֶ�");
const char *g_NotExistVisibleCol		 = QT_TRANSLATE_NOOP("GSP", "No Non Fixed Column to Display");// "û�п���ʾ�ķǹ̶���");

const char *g_InvalidXMLNode			 = QT_TRANSLATE_NOOP("GSP", "Invalid configuration file");// "�����ļ��Ƿ�");
const char *g_NeedXMLNode			 = QT_TRANSLATE_NOOP("GSP", "XML Node field cannot be null");// "XML�ڵ㲻��Ϊ��");

const char *g_SelectImage             = QT_TRANSLATE_NOOP("GLD", "select image");//ѡ��ͼƬ
const char *g_SquareReplace          = QT_TRANSLATE_NOOP("GLD", "two");//TRANS_STRING("�p");
const char *g_CubeReplace            = QT_TRANSLATE_NOOP("GLD", "three");//TRANS_STRING("�q");

const char *g_rsInvalideRule         = QT_TRANSLATE_NOOP("GLD", "Current rule not exist");     //"��ǰRule������");
const char *g_rsHasNoActiveSheet     = QT_TRANSLATE_NOOP("GLD", "No actived Sheet");           //"û�м����Sheet");
const char *g_rsGetMergeRectFailed   = QT_TRANSLATE_NOOP("GLD", "Getting merge cell failed");  //"��úϲ���ʧ��");
const char *g_rsTitleIndex           = QT_TRANSLATE_NOOP("GLD", "Index");                      //���
const char *g_rsTitleSelect          = QT_TRANSLATE_NOOP("GLD", "Select");                     //ѡ��
const char *g_rsTitleSymbol          = QT_TRANSLATE_NOOP("GLD", "Symbol");                     //��ʶ

// BinFile2
const char *g_InvalidBinFile         = QT_TRANSLATE_NOOP("GSP", "InvalidBinFile"); // ��Ч�Ķ������ļ�
const char *g_ReadBinFileError       = QT_TRANSLATE_NOOP("GSP", "ReadBinFileError"); // ��ȡ�������ļ�����

const char *g_rsMonth                  = QT_TRANSLATE_NOOP("GLD", "Month");
const char *g_rsYear                   = QT_TRANSLATE_NOOP("GLD", "Year");
const char *g_rsDay                    = QT_TRANSLATE_NOOP("GLD", "Day");
const char *g_rsMonDay                 = QT_TRANSLATE_NOOP("GLD", "Mon");
const char *g_rsTueDay                 = QT_TRANSLATE_NOOP("GLD", "Tue");
const char *g_rsWedDay                 = QT_TRANSLATE_NOOP("GLD", "Wed");
const char *g_rsThuDay                 = QT_TRANSLATE_NOOP("GLD", "Thu");
const char *g_rsFriDay                 = QT_TRANSLATE_NOOP("GLD", "Fri");
const char *g_rsSatDay                 = QT_TRANSLATE_NOOP("GLD", "Sat");
const char *g_rsSunDay                 = QT_TRANSLATE_NOOP("GLD", "Sun");

const char *g_rsFontEffect             = QT_TRANSLATE_NOOP("GLD", "FontEffect");
const char *g_rsEffect                 = QT_TRANSLATE_NOOP("GLD", "Effect");
const char *g_rsNoLine                 = QT_TRANSLATE_NOOP("GLD", "NoLine");
const char *g_rsOtherLine              = QT_TRANSLATE_NOOP("GLD", "OtherLine(w)...");
const char *g_rsLineWidth              = QT_TRANSLATE_NOOP("GLD", "Pounds");

const char *g_rsAutoHide               = QT_TRANSLATE_NOOP("GLD", "AutoHide");
const char *g_rsLocked                 = QT_TRANSLATE_NOOP("GLD", "Locked");

const char *g_rsSimsun                 = QT_TRANSLATE_NOOP("GLD", "Simsun");
const char *g_rsAccount                = QT_TRANSLATE_NOOP("GLD", "Account:");
const char *g_rsPassword               = QT_TRANSLATE_NOOP("GLD", "Password:");
const char *g_rsLogin                  = QT_TRANSLATE_NOOP("GLD", "Login");
const char *g_rsCancel                 = QT_TRANSLATE_NOOP("GLD", "Cancel");
const char *g_rsRegisterAccount        = QT_TRANSLATE_NOOP("GLD", "RegisterAccount");
const char *g_rsGetBackPassword        = QT_TRANSLATE_NOOP("GLD", "GetBackPassword");
const char *g_rsRemeberPassword        = QT_TRANSLATE_NOOP("GLD", "RemeberPassword");
const char *g_rsAutoLogin              = QT_TRANSLATE_NOOP("GLD", "AutoLogin");
const char *g_rsOpenVirtualKeyboard    = QT_TRANSLATE_NOOP("GLD", "OpenVirtualKeyboard");
const char *g_rsAccountError           = QT_TRANSLATE_NOOP("GLD", "The username or password is error, please enter again!");
const char *g_rsLoginError             = QT_TRANSLATE_NOOP("GLD", "Login failed, please try again later!");
const char *g_rsNetworkError           = QT_TRANSLATE_NOOP("GLD", "Network connection error, please check your network!");

GString getGLDi18nStr(const char *originalStr)
{
    static const char *s_context = "GLD";
    return qApp->translate(s_context, originalStr);
}

GString getGSPi18nStr(const char *originalStr)
{
    static const char *s_context = "GSP";
    return qApp->translate(s_context, originalStr);
}

GString getGEPEnginei18nStr(const char *originalStr)
{
    static const char *s_context = "GEPEngine";
    return qApp->translate(s_context, originalStr);
}
