������Դ���������Ӣ�Ĺ��ܡ�
����ʹ��Ӣ�ģ�Ĭ�ϵأ����ǲ���Ҫ���κ��޸ġ�
����ʹ�����ģ�������Ҫ�����²���:

1.��main����������������QApplication�󣬵����������:
    GLDTranslations cbbtr;
    cbbtr.loadConfigFile(exePath() + "translations");
    cbbtr.installTranslators();
    ����translations�ǹ�����Դ�����ӵ��ļ��С�loadConfigFile�Ĳ������Ǹ��ļ��е�·����

2.���Ӷ�Ӧ��ͷ�ļ�����
    #include "GLDTranslations.h"
    #include "GLDFileUtils.h" //��ʹ��exePath()�򲻱ذ���

