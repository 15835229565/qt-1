#ifndef GLDENUM
#define GLDENUM

enum GLDValueRelationship
{
    gvrLessThanValue = -1,
    gvrEqualsValue = 0,
    gvrGreaterThanValue = 1
};

// TableView.ItemDelegateѡ��
enum GEditStyle
{
    esNone,                     // ���ܱ༭
    esSimple,                   // Ĭ�ϱ༭��,�����������ʹ����༭��ʽ
    esPlainEdit,                // ���б༭��
    esLineEdit,                 // ���б༭��
    esPlainEllipsis,            // ʡ�ԺŰ�ť
    esLineEllipsis,             // ʡ�ԺŰ�ť�����б༭
    esMultiButton,              // �����ť
    esBool,                     // �������͵ĸ���
    esMonthCalendar,            // ����ѡ���
    esImage,                    // ͼƬ
    esVectorGraph,              // ʸ��ͼ
    esFontList,                 // ����ѡ���
    esColorList,                // ��ɫѡ���б�
    esLineWidthList,            // �߿�ѡ���б�
    esUpDown,                   // �������ÿ�
    esDropDown,                 // ����ѡ���
    esTreeView,                 // ���ο�
    esDropDownWindow,           // �����ĸ�������
    esDropDownWindowEllipsis,   // �����ĸ�������, button����ʽΪ������
    esDropDownWindowNone        // �����ĸ�������, ����ʾbutton
};

// GridSettingѡ��
enum GLDGridSettingEditStyle
{
    gesAuto,
    gesEdit,
    gesDropDownList,
    gesDropDown,
    gesEllipsisReadOnly,
    gesEllipsis,
    gesDateTimePicker,
    gesTreeView,
    gesCheckBox,
    gesDropDownWindowReadOnly,
    gesSpin,
    gesDropDownWindow,
    gesLineEdit
};

enum FontStyle
{
    fsBold = 0x01,
    fsItalic = 0x02,
    fsUnderline = 0x04,
    fsStrikeOut = 0x08
};

//MoveCurrent��ԭ��
enum MoveReason { mrKey, mrMouse, mrMouseWheel, mrProgram };

typedef GLDGridSettingEditStyle GLDEditStyle;

#endif // GLDENUM

