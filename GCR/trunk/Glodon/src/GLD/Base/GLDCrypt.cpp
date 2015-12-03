/*!
* @�ӽ��ܿ���
* @ ��ϸ: �����ӽ�������༰����AES������DES������;
*                 �ӽ����㷨�����༰����
* @author lijb
* @date 2015.06.05
* @remarks ��ע
* Copyright (c) 1998-2015 Glodon Corporation                                                    
*/

//cryptlib��궨�壬�Ծ�̬lib��ʽ����cryptlib.lib
#define _CRT_SECURE_NO_DEPRECATE
#define CRYPTOPP_DEFAULT_NO_DLL
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include "dll.h"

using namespace CryptoPP;
using namespace std;

#include "qglobal.h"
#include "GLDCrypt.h"
#include "GLDFile.h"

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: �ӽ����㷨��˽��
//������
////////////////////////////////////////////////////////////////////////////////
class GCryptAlgorithmPrivate
{
public:
  GCryptAlgorithmPrivate()
  {
  }

protected:
  GCryptAlgorithm * q_ptr;
  byte * m_pbyKey;	  //��Կ
  byte * m_pbyIv; 	  //��ʼ����
  int    m_nKeyLength; //��Կ����
  EnAlgorithmType m_EnAlgorithmType;  //�㷨���ͣ���AES , DES��
  EnEncodeMode  m_EnEncodeMode;      //����ģʽ����CBC, ECB��
  EnPaddingType m_EnPaddingType;	  //������ͣ���NoPadding��PKCS5Padding��

private:
  Q_DECLARE_PUBLIC(GCryptAlgorithm);
};

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: �ӽ����㷨�๹�캯�������ü��ܲ���
//������enAlgorithmType  �����㷨���ͣ���AES, DES��
//     EnEncodeMode      ����ģʽ���ͣ���CBC, ECB��
//     EnPaddingType     ���ģʽ���ͣ���NoPadding��PKCS5Padding��
////////////////////////////////////////////////////////////////////////////////
GCryptAlgorithm::GCryptAlgorithm(EnAlgorithmType EnAlgorithmKind, EnEncodeMode EnEncodeKind
                               , EnPaddingType EnPaddingKind)
    : d_ptr(new GCryptAlgorithmPrivate)
{
    Q_D(GCryptAlgorithm);

    d->q_ptr = this;

    d->m_EnAlgorithmType  = EnAlgorithmKind;
    d->m_EnEncodeMode     = EnEncodeKind;
    d->m_EnPaddingType    = EnPaddingKind;
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: �ӽ����㷨�๹�캯�������ü��ܲ���
//������enAlgorithmType  �����㷨���ͣ���AES, DES��
//     EnEncodeMode      ����ģʽ���ͣ���CBC, ECB��
//     EnPaddingType     ���ģʽ���ͣ���NoPadding��PKCS5Padding��
////////////////////////////////////////////////////////////////////////////////
GCryptAlgorithm::GCryptAlgorithm(GCryptAlgorithmPrivate &dd, EnAlgorithmType EnAlgorithmKind
               , EnEncodeMode EnEncodeType, EnPaddingType EnPadding)
    : d_ptr(&dd)
{
    Q_D(GCryptAlgorithm);

    d->q_ptr = this;

    d->m_EnAlgorithmType  = EnAlgorithmKind;
    d->m_EnEncodeMode     = EnEncodeType;
    d->m_EnPaddingType    = EnPadding;
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: �ӽ����㷨�����캯��
////////////////////////////////////////////////////////////////////////////////
GCryptAlgorithm::~GCryptAlgorithm()
{
    Q_D(GCryptAlgorithm);

    delete(d);
}
////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: ����Կ���������ַ��������ؼ��ܺ�������ַ���
//����: strPlainText  �����ַ���     
//����:  �����ַ���
////////////////////////////////////////////////////////////////////////////////
const GString GCryptAlgorithm::encryptStr(const GString &strPlainText)
{
    Q_D(GCryptAlgorithm);

    string strCipher;

    // ���ɼ���������
    SymmetricCipher *penncryptor = encryptor(d->m_EnEncodeMode);

    StringSource(strPlainText.toLatin1().data(), true, new StreamTransformationFilter(*penncryptor, new StringSink(strCipher)
                  , (StreamTransformationFilter::BlockPaddingScheme)d->m_EnPaddingType));

    //����������stringת��ΪGString
    return QString(QLatin1String(strCipher.c_str()));
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: ����Կ���������ַ��������ؽ��ܺ�������ַ���
//����: strPlainText  �����ַ���     
//����:  �����ַ���
////////////////////////////////////////////////////////////////////////////////
const GString GCryptAlgorithm::decryptStr(const GString &strCipher)
{
    Q_D(GCryptAlgorithm);

    string strCipherString = strCipher.toStdString();

    string strRecover;

	// ���ɽ���������
    SymmetricCipher* pdecryptor = decryptor(d->m_EnEncodeMode);
	
    StringSource(strCipher.toLatin1().data(), true, new StreamTransformationFilter(*pdecryptor, new StringSink(strRecover)
                 , (StreamTransformationFilter::BlockPaddingScheme)d->m_EnPaddingType));

    return QString(QLatin1String(strRecover.c_str()));
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: ����Կ���������ļ������ؼ��ܺ�������ļ�
//����: inFilename  �����ļ���
//            outFilename �����ļ���
//����: �ɹ�or  ʧ��
////////////////////////////////////////////////////////////////////////////////
bool GCryptAlgorithm::encryptFile(const GString &strOutFilename, const GString &strInFilename)
{
    Q_D(GCryptAlgorithm);

    if (!GFileStream::exists(strInFilename))
    {
        cout << "The file " << strInFilename.data() << " is not exist! " << endl;
        return false;
    }
	
    // ���ɼ���������
    SymmetricCipher* penncryptor = encryptor(d->m_EnEncodeMode);
		
    FileSource(strInFilename.toLatin1().data(), true,
            new StreamTransformationFilter(*penncryptor, new FileSink(strOutFilename.toLatin1().data())
             , (StreamTransformationFilter::BlockPaddingScheme)d->m_EnPaddingType));

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: ����Կ���������ļ������ؽ��ܺ�������ļ�
//����: decFilename  �����ļ���
//            recoverFilename �����ļ���
//����: �ɹ�or  ʧ��
////////////////////////////////////////////////////////////////////////////////
bool GCryptAlgorithm::decryptFile(const GString &strRecoverFilename, const GString &strDecFilename)
{
    Q_D(GCryptAlgorithm);

    if (!GFileStream::exists(strDecFilename))
    {
        cout << "The file " << strDecFilename.data() << " is not exist! " << endl;
        return false;
    }
	
	// ���ɽ���������
    SymmetricCipher* pdecryptor = decryptor(d->m_EnEncodeMode);
		
    FileSource(strDecFilename.toLatin1().data(), true, new StreamTransformationFilter((*pdecryptor),
         new FileSink(strRecoverFilename.toLatin1().data()), (StreamTransformationFilter::BlockPaddingScheme)d->m_EnPaddingType));

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: �����û���������ģʽEnEncodeType�����ض�Ӧ���ַ���
//             ��ȱʡ����"CBC"
//������ EnEncodeMode      ����ģʽ���ͣ���CBC, ECB��
//    
//���أ�����ģʽ��Ӧ���ַ���    
////////////////////////////////////////////////////////////////////////////////
GString GCryptAlgorithm::encodeModeStr(EnEncodeMode EnEncodeMode)
{
	switch (EnEncodeMode)
	{
		case ENCODE_MODE_CBC:
		{
			return "CBC";
			break;
		}
	
		case ENCODE_MODE_ECB:
		{
			return "ECB";
			break;
		}
		
		default:
			assert(false);
	}

    return "ECB";
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: �����û��������ģʽEnPaddingType�����ض�Ӧ���ַ�����ȱʡ����"PKCS5Padding"
//������ EnPaddingType      ����������ͣ���EN_NOPADDING��
//    
//���أ��������ģʽ��Ӧ���ַ���    
////////////////////////////////////////////////////////////////////////////////
GString GCryptAlgorithm::paddingTypeStr(EnPaddingType EnPaddingType)
{
	switch (EnPaddingType)
	{
		case EN_NOPADDING:
		{
			return "NoPadding";
			break;
		}

		case EN_PKCS_PADDING:
		{
			return "PKCS5Padding";
			break;
		}
		
		default:
			assert(false);
	}

	return "PKCS5Padding";
	
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����:  ���ü��ܲ��������������㷨EnAlgorithmKind������ģʽEnEncodeType���������EnPadding
//����:  EnAlgorithmKind    �����㷨���ͣ���AES, DES��
//              EnEncodeMode      ����ģʽ���ͣ���CBC, ECB��
//              EnPaddingType      ���ģʽ���ͣ���NoPadding��PKCS5Padding��?
//���أ���  
////////////////////////////////////////////////////////////////////////////////
void GCryptAlgorithm::setEncodeMode(EnAlgorithmType EnAlgorithmKind, EnEncodeMode EnEncodeMode, EnPaddingType EnPaddingType)
{
    Q_D(GCryptAlgorithm);

    d->m_EnAlgorithmType  = EnAlgorithmKind;
    d->m_EnEncodeMode     = EnEncodeMode;
    d->m_EnPaddingType    = EnPaddingType;
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����:  ������Կ����Կ���ȣ���ECBģʽ
//������ pbyKey   ������Կ
//                 nLength  ��Կ����
//                 pbyIv     ��ʼ����
//���أ���  
////////////////////////////////////////////////////////////////////////////////
void GCryptAlgorithm::setKey(byte *pbyKey, int nLength, byte *pbyIv)
{
   Q_D(GCryptAlgorithm);

   d->m_pbyKey = pbyKey;
   d->m_pbyIv  = pbyIv;
   d->m_nKeyLength = nLength;
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����:  ������Կ����Կ���ȣ�ECBģʽ
//������ pbyKey   ������Կ
//                 nLength  ��Կ����
//���أ���    
////////////////////////////////////////////////////////////////////////////////
void GCryptAlgorithm::setKey(byte *pbyKey, int nLength)
{
   Q_D(GCryptAlgorithm);

   d->m_pbyKey = pbyKey;
   d->m_nKeyLength = nLength;
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����:  ��ȡ��Կ
//������                 
//���أ���Կ�ֽ�ָ��    
////////////////////////////////////////////////////////////////////////////////
byte* GCryptAlgorithm::key()
{
    Q_D(GCryptAlgorithm);

    return d->m_pbyKey;
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����:  ��ȡ��ʼ����
//������                 
//���أ���Կ�ֽ�ָ��    
////////////////////////////////////////////////////////////////////////////////
byte* GCryptAlgorithm::ivKey()
{
    Q_D(GCryptAlgorithm);

    return d->m_pbyIv;
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: AES�ӽ����㷨˽�๹�캯��
////////////////////////////////////////////////////////////////////////////////
class GAesAlgorithmPrivate : public GCryptAlgorithmPrivate
{
public:
  GAesAlgorithmPrivate()
  {
  }

private:
  Q_DECLARE_PUBLIC(GAesAlgorithm);

  SymmetricCipher *m_encryptor;  //���������󣬸��ݼ���ģʽ���ɲ�ͬ����
  SymmetricCipher *m_decryptor;  //���������󣬸��ݼ���ģʽ���ɲ�ͬ����
};

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: AES�ӽ����㷨�๹�캯�������ü��ܲ���
//������enAlgorithmType  �����㷨���ͣ���AES, DES��
//     EnEncodeMode      ����ģʽ���ͣ���CBC, ECB��
//     EnPaddingType     ���ģʽ���ͣ���NoPadding��PKCS5Padding��
////////////////////////////////////////////////////////////////////////////////
GAesAlgorithm::GAesAlgorithm(EnEncodeMode EnEncodeMode, EnPaddingType EnPaddingType)
    : GCryptAlgorithm(*(new GAesAlgorithmPrivate), EN_ALGORITHM_AES, EnEncodeMode, EnPaddingType)
{
    Q_D(GAesAlgorithm);

    d->m_encryptor = NULL;
    d->m_decryptor = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.8
//����: AES�ӽ����㷨�������������ͷżӽ�������Դ
//������   
////////////////////////////////////////////////////////////////////////////////
GAesAlgorithm::~GAesAlgorithm()
{
    Q_D(GAesAlgorithm);

    if (NULL != d->m_encryptor)
	{
        delete d->m_encryptor;
	}

    if (NULL != d->m_decryptor)
	{
        delete d->m_decryptor;
	}
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.8
//����: �����ڲ���������ļ�����Կ������
//������   
////////////////////////////////////////////////////////////////////////////////
void GAesAlgorithm::setRandomKey()
{
    Q_D(GAesAlgorithm);

	AutoSeededRandomPool rnd;
	byte byKey[AES::DEFAULT_KEYLENGTH];
	rnd.GenerateBlock(byKey, AES::DEFAULT_KEYLENGTH);

    if (ENCODE_MODE_CBC != d->m_EnEncodeMode)
    {
		// Generate a random IV
		byte byIv[AES::BLOCKSIZE];
		rnd.GenerateBlock(byIv, AES::BLOCKSIZE);
		
		setKey(byKey, AES::DEFAULT_KEYLENGTH, byIv);	
	}
	else
	{		
		setKey(byKey, AES::DEFAULT_KEYLENGTH);	
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: �����û���������ģʽEnEncodeType���������EnPadding�� ������Ӧ�Ľ�����
//������
//     EnEncodeMode      ����ģʽ���ͣ���CBC, ECB��
//����:  ����������ָ��
//////////////////////////////////////////////////////////////////////////////////////////////////////////
SymmetricCipher* GAesAlgorithm::decryptor(EnEncodeMode EnEncodeMode)
{
    Q_D(GAesAlgorithm);

	SymmetricCipher* pdecryptor = NULL;
	
	switch (EnEncodeMode)
	{
		case ENCODE_MODE_CBC:
		{
            pdecryptor = new CBC_Mode<AES>::Decryption(d->m_pbyKey, d->m_nKeyLength, d->m_pbyIv);
			break;
		}

		case ENCODE_MODE_CFB:
		{
            pdecryptor = new CFB_Mode<AES>::Decryption(d->m_pbyKey, d->m_nKeyLength, d->m_pbyIv);
			break;
		}
		
		case ENCODE_MODE_ECB:
		{
            pdecryptor = new ECB_Mode<AES>::Decryption(d->m_pbyKey, d->m_nKeyLength);
			break;
		}	
		
		case ENCODE_MODE_OFB:
		{
            pdecryptor = new OFB_Mode<AES>::Decryption(d->m_pbyKey, d->m_nKeyLength, d->m_pbyIv);
			break;
		}
				
		default:
			assert(false);
	}
	
    d->m_decryptor = pdecryptor;

	return pdecryptor;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: �����û���������ģʽEnEncodeType���������EnPadding�� ������Ӧ�ļ�����
//������
//     EnEncodeMode      ����ģʽ���ͣ���CBC, ECB��
//����:  ����������ָ��
//////////////////////////////////////////////////////////////////////////////////////////////////////////
SymmetricCipher* GAesAlgorithm::encryptor(EnEncodeMode EnEncodeMode)
{
    Q_D(GAesAlgorithm);

	SymmetricCipher* pencryptor = NULL;

	switch (EnEncodeMode)
	{
		case ENCODE_MODE_CBC:
		{
            pencryptor = new CBC_Mode<AES>::Encryption(d->m_pbyKey, d->m_nKeyLength, d->m_pbyIv);
			break;
		}

		case ENCODE_MODE_CFB:
		{
            pencryptor = new CFB_Mode<AES>::Encryption(d->m_pbyKey, d->m_nKeyLength, d->m_pbyIv);
			break;
		}
		
		case ENCODE_MODE_ECB:
		{
            pencryptor = new ECB_Mode<AES>::Encryption(d->m_pbyKey, d->m_nKeyLength);
			break;
		}	
		
		case ENCODE_MODE_OFB:
		{
            pencryptor = new OFB_Mode<AES>::Encryption(d->m_pbyKey, d->m_nKeyLength, d->m_pbyIv);
			break;
		}
				
		default:
			assert(false);
	}
	
    d->m_encryptor = pencryptor;
	
	return pencryptor;

}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.8
//����: DES�ӽ����㷨˽��
////////////////////////////////////////////////////////////////////////////////
class GDesAlgorithmPrivate : public GCryptAlgorithmPrivate
{
public:
  GDesAlgorithmPrivate()
  {
  }

private:
  Q_DECLARE_PUBLIC(GDesAlgorithm);

  SymmetricCipher *m_encryptor;  //���������󣬸��ݼ���ģʽ���ɲ�ͬ����
  SymmetricCipher *m_decryptor;  //���������󣬸��ݼ���ģʽ���ɲ�ͬ����
};

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.8
//����: DES�ӽ����㷨�๹�캯�������ü��ܲ���
//������
//     EnEncodeMode      ����ģʽ���ͣ���CBC, ECB��
//     EnPaddingType     ���ģʽ���ͣ���NoPadding��PKCS5Padding��
////////////////////////////////////////////////////////////////////////////////
GDesAlgorithm::GDesAlgorithm(EnEncodeMode EnEncodeMode, EnPaddingType EnPaddingType)
    : GCryptAlgorithm(* new GDesAlgorithmPrivate(), EN_ALGORITHM_DES, EnEncodeMode, EnPaddingType)
{	
    Q_D(GDesAlgorithm);

    d->m_encryptor = NULL;
    d->m_decryptor = NULL;
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.8
//����: DES�ӽ����㷨�������������ͷżӽ�������Դ
//������   
////////////////////////////////////////////////////////////////////////////////
GDesAlgorithm::~GDesAlgorithm()
{
    Q_D(GDesAlgorithm);

    if (NULL != d->m_encryptor)
	{
        delete d->m_encryptor;
	}

    if (NULL != d->m_decryptor)
	{
        delete d->m_decryptor;
	}
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.8
//����: �����ڲ���������ļ�����Կ������
//������   
////////////////////////////////////////////////////////////////////////////////
void GDesAlgorithm::setRandomKey()
{
    Q_D(GDesAlgorithm);

	AutoSeededRandomPool rnd;
	byte byKey[DES::DEFAULT_KEYLENGTH];
	rnd.GenerateBlock(byKey, DES::DEFAULT_KEYLENGTH);

    if (ENCODE_MODE_CBC != d->m_EnEncodeMode)
    {
		// Generate a random IV
		byte byIv[AES::BLOCKSIZE];
		rnd.GenerateBlock(byIv, DES::BLOCKSIZE);
		
		setKey(byKey, DES::DEFAULT_KEYLENGTH, byIv);	

	}
	else
	{		
		setKey(byKey, DES::DEFAULT_KEYLENGTH);	
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.9
//����: �����û���������ģʽEnEncodeType���������EnPadding�� ������Ӧ�Ľ�����
//������
//     EnEncodeMode      ����ģʽ���ͣ���CBC, ECB��
//����:  ����������ָ��
//////////////////////////////////////////////////////////////////////////////////////////////////////////
SymmetricCipher* GDesAlgorithm::decryptor(EnEncodeMode EnEncodeKind)
{
    Q_D(GDesAlgorithm);

	SymmetricCipher* decryptor = NULL;
	
    switch (EnEncodeKind)
	{
		case ENCODE_MODE_CBC:
		{
            decryptor = new CBC_Mode<DES>::Decryption(d->m_pbyKey, d->m_nKeyLength, d->m_pbyIv);
			break;
		}

		case ENCODE_MODE_CFB:
		{
            decryptor = new CFB_Mode<DES>::Decryption(d->m_pbyKey, d->m_nKeyLength, d->m_pbyIv);
			break;
		}
		
		case ENCODE_MODE_ECB:
		{
            decryptor = new ECB_Mode<DES>::Decryption(d->m_pbyKey, d->m_nKeyLength);
			break;
		}	
		
		case ENCODE_MODE_OFB:
		{
            decryptor = new OFB_Mode<DES>::Decryption(d->m_pbyKey, d->m_nKeyLength, d->m_pbyIv);
			break;
		}
		
		//case ENCODE_MODE_PCBC:
		//{
            //decryptor = new PCBC_Mode<DES>::Decryption(d->m_pbyKey, d->m_nKeyLength, d->m_pbyIv);
			//break;
		//}
					
		default:
			assert(false);
	}
	
    d->m_decryptor = decryptor;

	return decryptor;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: �����û���������ģʽEnEncodeType���������EnPadding�� ������Ӧ�ļ�����
//������
//     EnEncodeKind      ����ģʽ���ͣ���CBC, ECB��
//����:  ����������ָ��
//////////////////////////////////////////////////////////////////////////////////////////////////////////
SymmetricCipher* GDesAlgorithm::encryptor(EnEncodeMode EnEncodeKind)
{
    Q_D(GDesAlgorithm);

	SymmetricCipher* encryptor = NULL;
	
    switch (EnEncodeKind)
	{
		case ENCODE_MODE_CBC:
		{
            encryptor = new CBC_Mode<DES>::Encryption(d->m_pbyKey, d->m_nKeyLength, d->m_pbyIv);
			break;
		}

		case ENCODE_MODE_CFB:
		{
            encryptor = new CFB_Mode<DES>::Encryption(d->m_pbyKey, d->m_nKeyLength, d->m_pbyIv);
			break;
		}
		
		case ENCODE_MODE_ECB:
		{
            encryptor = new ECB_Mode<DES>::Encryption(d->m_pbyKey, d->m_nKeyLength);
			break;
		}	
		
		case ENCODE_MODE_OFB:
		{
            encryptor = new OFB_Mode<DES>::Encryption(d->m_pbyKey, d->m_nKeyLength, d->m_pbyIv);
			break;
		}
		
		//case ENCODE_MODE_PCBC:
		//{
            //cryptAlgorithm = new PCBC_Mode<DES>::Encryption(d->m_pbyKey, d->m_nKeyLength, d->m_pbyIv);
			//break;
		//}
					
		default:
			assert(false);
	}
	
    d->m_encryptor = encryptor;
	
	return encryptor;

}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: �ӽ����㷨������˽��
////////////////////////////////////////////////////////////////////////////////
class GCryptPrivate
{
public:
  GCryptPrivate(GCrypt *parent)
    : q_ptr(parent)
  {
  }

private:
  GCrypt * const q_ptr;
  Q_DECLARE_PUBLIC(GCrypt);

  GCryptAlgorithm *m_algorithm; //�����㷨����ָ�룬��AES , DES��
};

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: �ӽ����㷨�����๹�캯�������ü��ܲ�����
//             ���ɼӽ����㷨�����
//     EnAlgorithmKind  �����㷨���ͣ���AES, DES��
//     EnEncodeMode      ����ģʽ���ͣ���CBC, ECB��
//     EnPaddingType     ���ģʽ���ͣ���NoPadding��PKCS5Padding��
////////////////////////////////////////////////////////////////////////////////
GCrypt::GCrypt(EnAlgorithmType EnAlgorithmKind, EnEncodeMode EnEncodeMode, EnPaddingType EnPaddingType)
    : d_ptr(new GCryptPrivate(this))
{
    Q_D(GCrypt);

    d->m_algorithm = createAlgorithm(EnAlgorithmKind, EnEncodeMode, EnPaddingType);
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: �����û�����ļ��ܲ��������ɶ�Ӧ�ļӽ��������
//������enAlgorithmType  �����㷨���ͣ���AES, DES��
//     EnEncodeMode      ����ģʽ���ͣ���CBC, ECB��
//     EnPaddingType     ���ģʽ���ͣ���NoPadding��PKCS5Padding?
//����: �ӽ��������ָ��
////////////////////////////////////////////////////////////////////////////////
GCryptAlgorithm* GCrypt::createAlgorithm(EnAlgorithmType EnAlgorithmType, EnEncodeMode EnEncodeMode 
                                            ,EnPaddingType EnPaddingType)
{
	GCryptAlgorithm* cryptAlgorithm = NULL;

	switch (EnAlgorithmType)
	{
		case EN_ALGORITHM_AES:
		{
			cryptAlgorithm = new GAesAlgorithm(EnEncodeMode, EnPaddingType);
			break;
		}
		
		case EN_ALGORITHM_DES:
		{
			cryptAlgorithm = new GDesAlgorithm(EnEncodeMode, EnPaddingType);
			break;
		}
		
		default:
			assert(false);
	}

	return cryptAlgorithm;

}

GCrypt::~GCrypt()
{
    Q_D(GCrypt);

    if (NULL != d->m_algorithm)
    {
        delete d->m_algorithm;
	}

    delete d;
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: ʹ����Կ���������ַ���plainText ���ҷ�������
//����: strPlainText  ����ԭ���ַ���
//����: ���������ַ�������
////////////////////////////////////////////////////////////////////////////////

GString GCrypt::encryptStr(const GString &strPlainText)
{
    Q_D(GCrypt);

    return  d->m_algorithm->encryptStr(strPlainText);
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: ʹ����Կ��������cipher ���ҷ��ػָ��������
//����: strCipher  ���������ַ���
//����: ���ػָ��������
////////////////////////////////////////////////////////////////////////////////
GString GCrypt::decryptStr(const GString &strCipher)
{
    Q_D(GCrypt);

    return  d->m_algorithm->decryptStr(strCipher);
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: ʹ����Կ���������ļ�inFilename ���ҷ��������ļ�outFilename
//����: inFilename  �����ļ�
//     outFilename �����ļ�
//����: �ɹ����
////////////////////////////////////////////////////////////////////////////////
bool GCrypt::encryptFile(const GString &strOutFilename, const GString &strInFilename)
{
    Q_D(GCrypt);

    return  d->m_algorithm->encryptFile(strOutFilename, strInFilename);
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: ʹ����Կ���������ļ�DecFilename ���ҷ��ػָ���������ļ�recoverFilename
//����: strDecFilename �����ļ�
//     strRecoverFilename �ָ���������ļ�recoverFilename
//����: �ɹ����
////////////////////////////////////////////////////////////////////////////////
bool GCrypt::decryptFile(const GString &strRecoverFilename, const GString &strDecFilename)
{
    Q_D(GCrypt);

    return  d->m_algorithm->decryptFile(strRecoverFilename, strDecFilename);
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: ���ü��ܲ��������������㷨EnAlgorithmKind������ģʽEnEncodeType���������EnPadding
//����: EnAlgorithmKind �����㷨
//     EnEncodeType    ����ģʽ
//     EnPadding       �������
//����: ��
////////////////////////////////////////////////////////////////////////////////
void GCrypt::setEncodeMode(EnAlgorithmType EnAlgorithmKind, EnEncodeMode EnEncodeType, EnPaddingType EnPadding)
{
    Q_D(GCrypt);

    return  d->m_algorithm->setEncodeMode(EnAlgorithmKind, EnEncodeType, EnPadding);
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: �����ڲ���������ļ�����Կ������
//����: ��
////////////////////////////////////////////////////////////////////////////////
void GCrypt::setRandomKey()
{
    Q_D(GCrypt);

    return  d->m_algorithm->setRandomKey();
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: ���ü�����Կ�����ȣ��˴���Ҫ���أ���ΪCBCģʽ����Ҫ��ʼ����iv
//����: key    ��Կ�ַ���
//     length ��Կ����
//     iv     ��ʼ����
//����: ��
////////////////////////////////////////////////////////////////////////////////
void GCrypt::setKey(byte *key, int length, byte *iv)
{
    Q_D(GCrypt);

    return  d->m_algorithm->setKey(key, length, iv);
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: ���ü�����Կ�����ȣ��˴���Ҫ���أ���ΪCBCģʽ����Ҫ��ʼ����iv
//����: key    ��Կ�ַ���
//     length ��Կ����
//����: ��
////////////////////////////////////////////////////////////////////////////////
void GCrypt::setKey(byte *key, int length)
{
    Q_D(GCrypt);

    return  d->m_algorithm->setKey(key, length);
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: ��ȡ������Կ
//����: ��
//����: ��Կ�ַ���
////////////////////////////////////////////////////////////////////////////////
byte * GCrypt::key()
{
    Q_D(GCrypt);

    return  d->m_algorithm->key();
}

////////////////////////////////////////////////////////////////////////////////
//���: Lijb 2015.06.5
//����: ��ȡ���ܳ�ʼ����
//����: ��
//����: ��ʼ����
////////////////////////////////////////////////////////////////////////////////
byte * GCrypt::ivKey()
{
    Q_D(GCrypt);

    return  d->m_algorithm->ivKey();
}
