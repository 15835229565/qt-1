/*!
*@file     
*@brief    GLD�����������ļ�����
*@author   cuidc
*@date     2014��3��11��
*@remarks  
*@version  3.0
*Copyright (c) 1998-2014 Glodon Corporation
*/
#ifndef GLDTRANSLATIONS_H
#define GLDTRANSLATIONS_H

#include <QObject>
#include <QTranslator>
#include "GLDCommon_Global.h"
#include "GLDString.h"
#include "GLDXMLTypes.h"

class GLDTranslationsPrivate;
class GLDCOMMONSHARED_EXPORT GLDTranslations : public QObject
{
	Q_OBJECT
public:
    GLDTranslations(QObject *parent = NULL);
    ~GLDTranslations();
	// ���ط��������ļ�
    bool loadConfigFile(const GString filePath, const GString configfileName = "TranslationsConfig.xml");
	// ���ط����ļ�
    bool installTranslators();
private:
    Q_DECLARE_PRIVATE(GLDTranslations);
};

#endif // GLDTRANSLATIONS_H
