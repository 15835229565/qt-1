/*!
* @�ӽ��ܿ�ͷ�ļ�
*
* @author lijb
* @date 2015.06.05
* @remarks ��ע
* Copyright (c) 1998-2015 Glodon Corporation                                                    
*/
#ifndef GLDCRYPT_H
#define GLDCRYPT_H

#include "GLDCrypt_Global.h"
#include "GLDString.h"
#include "GLDCrypt_Global.h"
#include "cryptlib.h"

//class CRYPTOPP_DLL CRYPTOPP_NO_VTABLE SymmetricCipher;

//�ӽ����㷨ö�٣�Ŀǰ֧��AES, DES��������
enum EnAlgorithmType
{
    EN_ALGORITHM_AES = 0,
    EN_ALGORITHM_DES = 1,
    EN_ALGORITHM_UNKOWN
};

//�ӽ����㷨����ģʽö��
enum EnEncodeMode
{
    ENCODE_MODE_CBC = 0,
    ENCODE_MODE_CFB = 1,
    ENCODE_MODE_ECB = 2,
    ENCODE_MODE_OFB = 3,
    ENCODE_MODE_PCBC = 4,
    ENCODE_MODE_UNKOWN
};

//�ӽ����㷨���ģʽö��
enum EnPaddingType
{
	//enum BlockPaddingScheme {NO_PADDING, ZEROS_PADDING, PKCS_PADDING, ONE_AND_ZEROS_PADDING, DEFAULT_PADDING};
	//�±�ö����Ҫ��cryptlib��һ��
    EN_NOPADDING = 0,
    EN_ZEROS_PADDING = 1,
    EN_PKCS_PADDING = 2,
    EN_ONE_AND_ZEROS_PADDING = 3,
    EN_DEFAULT_PADDING = 4, 
    EN_PADDING_UNKOWN
};

class GCryptAlgorithmPrivate;
////////////////////////////////////////////////////////////////////////////////
//���:����һ���ӽ����㷨���Ի��࣬�ṩ��Ӧ��ӿڣ���ؽӿ���Ҫ����ʵ�֣�
//     �����ӿ���encryptStr�ȷ�װ������ʵ��
//����:�㷨���࣬�ṩ�ӽ��ܴ�/�ļ����Լ����üӽ���������ýӿ�
////////////////////////////////////////////////////////////////////////////////
class GLDCRYPTSHARED_EXPORT GCryptAlgorithm
{
public:	
	//ʹ����Կ���������ַ���plainText ���ҷ�������
    const GString encryptStr(const GString &plainText);
	
	//ʹ����Կ��������cipher ���ҷ��ػָ��������
    const GString decryptStr(const GString &cipher);
	
	//ʹ����Կ���������ļ�inFilename ���ҷ��������ļ�outFilename
    bool encryptFile(const GString & outFilename, const GString & inFilename);
	
	//ʹ����Կ���������ļ�DecFilename ���ҷ��ػָ���������ļ�recoverFilename
    bool decryptFile(const GString & recoverFilename, const GString & DecFilename);

	//�����û���������ģʽEnEncodeType�����ض�Ӧ���ַ���
    static GString encodeModeStr(EnEncodeMode EnEncodeType);

	//�����û������������EnPadding�����ض�Ӧ���ַ���
    static GString paddingTypeStr(EnPaddingType EnPadding);

	//���ü��ܲ��������������㷨EnAlgorithmKind������ģʽEnEncodeType���������EnPadding
	void setEncodeMode(EnAlgorithmType EnAlgorithmKind, EnEncodeMode EnEncodeType, EnPaddingType EnPadding);

	//���ü�����Կ�����ȣ��˴���Ҫ���أ���ΪCBCģʽ����Ҫ��ʼ����iv
    void setKey(byte *key, int length, byte *iv);
	void setKey(byte *key, int length);

	//��ȡ������Կ
	byte * key();
	//��ȡ���ܳ�ʼ����
    byte * ivKey();

	//�����ڲ���������ļ�����Կ������
	virtual void setRandomKey() = 0;

    //�����û���������ģʽEnEncodeType ������Ӧ�ļӽ�����
    virtual SymmetricCipher* encryptor(EnEncodeMode EnEncodeType) = 0;
    virtual SymmetricCipher* decryptor(EnEncodeMode EnEncodeType) = 0;

protected:
    GCryptAlgorithm(EnAlgorithmType EnAlgorithmKind, EnEncodeMode EnEncodeType, EnPaddingType EnPadding);
    GCryptAlgorithm(GCryptAlgorithmPrivate &dd, EnAlgorithmType EnAlgorithmKind, EnEncodeMode EnEncodeType, EnPaddingType EnPadding);
    ~GCryptAlgorithm();

protected:
    GCryptAlgorithmPrivate* const d_ptr;
    Q_DECLARE_PRIVATE(GCryptAlgorithm);

	friend class GCrypt;
};

class GAesAlgorithmPrivate;
////////////////////////////////////////////////////////////////////////////////
//���:AES �ӽ����㷨�����࣬ʵ�ָ���GCryptAlgorithm�ӽ������ķ���
//����:AES�㷨���࣬�ṩ�ӽ��ܴ�/�ļ����Լ����üӽ���������ýӿ�
////////////////////////////////////////////////////////////////////////////////
class GLDCRYPTSHARED_EXPORT GAesAlgorithm : public GCryptAlgorithm
{
public:
	GAesAlgorithm(EnEncodeMode EnEncodeMode, EnPaddingType EnPaddingType);
	~GAesAlgorithm();
	
	//�����ڲ���������ļ�����Կ������
	void setRandomKey();
	
    //�����û������ӽ���ģʽEnEncodeType�� ������Ӧ�ļӽ�������
    SymmetricCipher* encryptor(EnEncodeMode EnEncodeMode);
    SymmetricCipher* decryptor(EnEncodeMode EnEncodeMode);

private:
    Q_DECLARE_PRIVATE(GAesAlgorithm);
};

class GDesAlgorithmPrivate;
////////////////////////////////////////////////////////////////////////////////
//���:DES �ӽ����㷨�����࣬ʵ�ָ���GCryptAlgorithm�ӽ������ķ���
//     
//����:DES�㷨���࣬�ṩ�ӽ��ܴ�/�ļ����Լ����üӽ���������ýӿ�
////////////////////////////////////////////////////////////////////////////////
class GLDCRYPTSHARED_EXPORT GDesAlgorithm : public GCryptAlgorithm
{
public:
	GDesAlgorithm(EnEncodeMode EnEncodeMode, EnPaddingType EnPaddingType);
	~GDesAlgorithm();
	
	//�����ڲ���������ļ�����Կ������
	void setRandomKey();
	
    //�����û������ӽ���ģʽEnEncodeType ������Ӧ�ļӽ�������
    SymmetricCipher* encryptor(EnEncodeMode EnEncodeMode);
    SymmetricCipher* decryptor(EnEncodeMode EnEncodeMode);

private:
    Q_DECLARE_PRIVATE(GDesAlgorithm);
};

class GCryptPrivate;
////////////////////////////////////////////////////////////////////////////////
//���:����һ���ӽ��ܲ����࣬�����û�����������ù���������̬�����ӽ��ܶ���
//            �����β��죬�û�����֪��������չ����װ�������ӿڣ����������ʵ��
//����:�����û�����ļ��ܲ��������ɶ�Ӧ�ļ��ܶ���
////////////////////////////////////////////////////////////////////////////////
class GLDCRYPTSHARED_EXPORT GCrypt
{
public:
    GCrypt(EnAlgorithmType enAlgorithmType = EN_ALGORITHM_DES
         , EnEncodeMode EnEncodeType = ENCODE_MODE_CBC, EnPaddingType EnPadding = EN_PKCS_PADDING);
	~GCrypt();
	
	//ʹ����Կ���������ַ���plainText ���ҷ�������
    GString encryptStr(const GString &strPlainText);
	
	//ʹ����Կ��������cipher ���ҷ��ػָ��������
    GString decryptStr(const GString &strCipher);
	
	//ʹ����Կ���������ļ�inFilename ���ҷ��������ļ�outFilename
    bool encryptFile(const GString &strOutFilename, const GString &strInFilename);
	
	//ʹ����Կ���������ļ�DecFilename ���ҷ��ػָ���������ļ�recoverFilename
    bool decryptFile(const GString &strRecoverFilename, const GString &strDecFilename);

	//���ü��ܲ��������������㷨EnAlgorithmKind������ģʽEnEncodeType���������EnPadding
    void setEncodeMode(EnAlgorithmType EnAlgorithmKind, EnEncodeMode EnEncodeType, EnPaddingType EnPadding);
	
	//�����ڲ���������ļ�����Կ������
    void setRandomKey();
	
	//���ü�����Կ�����ȣ��˴���Ҫ���أ���ΪCBCģʽ����Ҫ��ʼ����iv
    void setKey(byte *key, int length, byte *iv);
    void setKey(byte *key, int length) ;
	
	//��ȡ������Կ
    byte * key();
	
	//��ȡ���ܳ�ʼ����
    byte * ivKey();
	
private:	
	//�����û�����ļ��ܲ��������ɶ�Ӧ�ļ��������
	GCryptAlgorithm* createAlgorithm(EnAlgorithmType enAlgorithmType, EnEncodeMode EnEncodeMode, EnPaddingType EnPaddingType);

private:
    GCryptPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(GCrypt);
};

#endif
