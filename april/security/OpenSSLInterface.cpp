/**************************************************************************
Author: Feng Xuebing 
Date:2019-09-06
**************************************************************************/
#include "OpenSSLInterface.h"
#include <openssl/rsa.h>
#include <openssl/md5.h>
#include <openssl/aes.h>
#include <openssl/sha.h>
#include <openssl/rc4.h>
#include <openssl/pem.h>

#include <string.h>

using namespace April::Security;

void OpenSSLInterface::GenerateMD5(const unsigned char* SrcData,int len, unsigned char* EncodedHexStr)
{
	unsigned char mdStr[MD5LENGTH] = { 0 };
	MD5(SrcData, len, mdStr);

	char buf[MD5LENGTH*2+1] = { 0 };
	char tmp[3] = { 0 };
	for (int i = 0; i < MD5LENGTH; i++)
	{
		snprintf(tmp,sizeof(tmp), "%02x", mdStr[i]);
		memcpy(EncodedHexStr+i*2, tmp,2);
	}
}


void OpenSSLInterface::GenerateSHA256(const unsigned char* SrcData,int len, unsigned char *EncodedHexStr)
{
	unsigned char mdStr[SHA256LENGTH] = { 0 };
	SHA256(SrcData, len, mdStr);

	char buf[SHA256LENGTH*2+1] = { 0 };
	char tmp[3] = { 0 };
	for (int i = 0; i < 32; i++)
	{
		snprintf(tmp, sizeof(tmp), "%02x", mdStr[i]);
		memcpy(EncodedHexStr + i * 2, tmp, 2);
	}
	
}


OpenSSLInterface::ErrorType OpenSSLInterface::EncryptionAES(const unsigned char* SrcData, int len,
									 const unsigned char *AESKey,int KeyLen, 
									unsigned char* CipherData, int *CipherLen)
{
	std::string enc_data;
	int data_length = len;
	int padding = 0;
	unsigned char* data_dup;
	AES_KEY m_aes_key;

	int res = AES_set_encrypt_key(AESKey, KeyLen * 8, &m_aes_key);
	if (res < 0)
	{
		return AESEncryptError;
	}

	//padding data to ensure data_length%AES_BLOCK_SIZE=0
	if (data_length%AES_BLOCK_SIZE > 0)
	{
		padding = AES_BLOCK_SIZE - data_length % AES_BLOCK_SIZE;
	}
	data_length += padding;
	*CipherLen = data_length;

	data_dup = (unsigned char*)calloc(data_length, sizeof(unsigned char));
	memcpy(data_dup, SrcData, len);
	
	//encryption data(16byte per times)
	for (int i = 0; i < (data_length/AES_BLOCK_SIZE); i++)
	{
		unsigned char tmpstr[AES_BLOCK_SIZE] = {0};
		memcpy(tmpstr, &data_dup[AES_BLOCK_SIZE*i], AES_BLOCK_SIZE);
		unsigned char out[AES_BLOCK_SIZE] = {0};
		
		AES_encrypt(tmpstr, out, &m_aes_key);
		memcpy(&CipherData[AES_BLOCK_SIZE*i], out, AES_BLOCK_SIZE);
	}

	return OperationOK;
}


OpenSSLInterface::ErrorType OpenSSLInterface::DecryptionAES(const unsigned char* SrcData, int SrcLen,
									const unsigned char* AESKey, int KeyLen,
									unsigned char* CipherData, int *CipherLen)
{
	int datalen = 0;
	AES_KEY m_aes_key;
	int res = AES_set_decrypt_key(AESKey, KeyLen * 8, &m_aes_key);
	if (res < 0)
	{
		return AESDecryptError;
	}
	for (int i = 0; i < SrcLen / AES_BLOCK_SIZE; i++)
	{
		unsigned char tmpstr[AES_BLOCK_SIZE] = {0};
		memcpy(tmpstr, &SrcData[AES_BLOCK_SIZE*i], AES_BLOCK_SIZE);
		unsigned char out[AES_BLOCK_SIZE] = { 0 };
		
		AES_decrypt(tmpstr, out, &m_aes_key);
		memcpy(&CipherData[AES_BLOCK_SIZE*i], out, AES_BLOCK_SIZE);
	}
	return OperationOK;
}


OpenSSLInterface::ErrorType OpenSSLInterface::EncryptionAEScbc(const unsigned char* SrcData, int SrcLen,
										const unsigned char* AESKey, int KeyLen,
										unsigned char* CipherData, int *CipherLen)
{
	int outlength;
	AES_KEY m_aes_key;
	unsigned char ivec[AES_BLOCK_SIZE] = {0};
	if (SrcLen % AES_BLOCK_SIZE == 0)
	{
		outlength = SrcLen;
	}
	else
	{
		outlength = (SrcLen / AES_BLOCK_SIZE + 1)*AES_BLOCK_SIZE;
	}
	*CipherLen = outlength;

	int res = AES_set_encrypt_key(AESKey, KeyLen* 8, &m_aes_key);
	if (res < 0)
	{
		return AEScbcEncryptError;
	}

	AES_cbc_encrypt(SrcData, CipherData, outlength, &m_aes_key, ivec, AES_ENCRYPT);
	return OperationOK;
}

OpenSSLInterface::ErrorType OpenSSLInterface::DecryptionAEScbc(const unsigned char* SrcData, int SrcLen,
						const unsigned char* AESKey, int KeyLen,
						unsigned char* CipherData, int *CipherLen)
{
	unsigned char ivec[AES_BLOCK_SIZE] = {0};
	AES_KEY m_aes_key;

	//set decryption key
	int res = AES_set_decrypt_key(AESKey, KeyLen * 8, &m_aes_key);
	if (res < 0)
	{
		return AEScbcDecryptError;
	}
	
	AES_cbc_encrypt(SrcData, CipherData, SrcLen, &m_aes_key, ivec, AES_DECRYPT);
	return OperationOK;
}

OpenSSLInterface::ErrorType OpenSSLInterface::EncryptionAESecb(const unsigned char* SrcData, int SrcLen,
										const unsigned char* AESKey, int KeyLen,
										unsigned char* CipherData, int *CipherLen)
{
	int data_length = SrcLen;
	int padding = 0;
	unsigned char *data_dup = NULL;
	AES_KEY m_aes_key;

	int res = AES_set_encrypt_key(AESKey, KeyLen * 8, &m_aes_key);
	if (res < 0)
	{
		return AESecbEncryptError;
	}

	//padding data to ensure data_length%AES_BLOCK_SIZE=0
	if (data_length%AES_BLOCK_SIZE > 0)
	{
		padding = AES_BLOCK_SIZE - data_length % AES_BLOCK_SIZE;
	}
	data_length += padding;

	data_dup = (unsigned char*)calloc(data_length, sizeof(unsigned char));
	memcpy(data_dup, SrcData, SrcLen);
	*CipherLen = data_length;

	//encryption data(16byte per times)
	for (int i = 0; i < (data_length / AES_BLOCK_SIZE); i++)
	{
		unsigned char tmpstr[AES_BLOCK_SIZE] = { 0 };
		memcpy(tmpstr, &data_dup[AES_BLOCK_SIZE*i], AES_BLOCK_SIZE);
		unsigned char out[AES_BLOCK_SIZE] = { 0 };
		
		AES_ecb_encrypt(tmpstr, out, &m_aes_key, AES_ENCRYPT);
		memcpy(&CipherData[AES_BLOCK_SIZE*i], out, AES_BLOCK_SIZE);
	}
	return OperationOK;
}

OpenSSLInterface::ErrorType OpenSSLInterface::DecryptionAESecb(const unsigned char* SrcData, int SrcLen,
							const unsigned char* AESKey, int KeyLen,
							unsigned char* DecodeData, int *DecodeDataLen)
{

	int data_length = SrcLen;
	int padding = 0;
	unsigned char *data_dup;
	AES_KEY m_aes_key;

	int res = AES_set_decrypt_key(AESKey, KeyLen * 8, &m_aes_key);
	if (res < 0)
	{
		return AESecbDecryptError;
	}

	//padding data to ensure data_length%AES_BLOCK_SIZE=0
	if (data_length%AES_BLOCK_SIZE > 0)
	{
		padding = AES_BLOCK_SIZE - data_length % AES_BLOCK_SIZE;
	}
	data_length += padding;

	//encryption data(16byte per times)
	for (int i = 0; i < (data_length / AES_BLOCK_SIZE); i++)
	{
		unsigned char tmpstr[AES_BLOCK_SIZE] = { 0 };
		memcpy(tmpstr, &SrcData[AES_BLOCK_SIZE*i], AES_BLOCK_SIZE);
		unsigned char out[AES_BLOCK_SIZE] = { 0 };
		
		AES_ecb_encrypt(tmpstr, out, &m_aes_key, AES_DECRYPT);
		memcpy(&DecodeData[AES_BLOCK_SIZE*i], out, AES_BLOCK_SIZE);
	}
	return OperationOK;
}


void OpenSSLInterface::GenerateRSAKey(unsigned char* PublicKey, int* PubKeyLen, unsigned char* PrivateKey, int* PriKeyLen)
{
	size_t pri_len;
	size_t pub_len;
	char *pri_key = NULL;
	char *pub_key = NULL;

	//generate key pair
	RSA *keyPair = RSA_generate_key(RSAKEYLENGTH, RSA_F4, NULL, NULL);

	BIO *pri = BIO_new(BIO_s_mem());
	BIO *pub = BIO_new(BIO_s_mem());

	PEM_write_bio_RSAPrivateKey(pri, keyPair, NULL, NULL, 0, NULL, NULL);
	PEM_write_bio_RSAPublicKey(pub, keyPair);
   
	pri_len = BIO_pending(pri);
	pub_len = BIO_pending(pub);

	pri_key = (char *)malloc(pri_len + 1);
	pub_key = (char *)malloc(pub_len + 1);

	BIO_read(pri, pri_key, pri_len);
	BIO_read(pub, pub_key, pub_len);

	pri_key[pri_len] = '\0';
	pub_key[pub_len] = '\0';

	memcpy(PublicKey, pub_key, pub_len);
	memcpy(PrivateKey, pri_key, pri_len);
	*PubKeyLen = pub_len;
	*PriKeyLen = pri_len;

	//free memory
	RSA_free(keyPair);
	BIO_free_all(pub);
	BIO_free_all(pri);

	free(pri_key);
	free(pub_key);
}


OpenSSLInterface::ErrorType OpenSSLInterface::RSAPublicEncrypt(const unsigned char* SrcData, int SrcLen,
										const unsigned char* RSAKey, int KeyLen,
										unsigned char* CipherData, int *CipherLen)
{
	std::string strRet;
	int nCount = 0;
	int nMode = 0;
	int ret = -1;

	RSA *rsa = NULL;
	BIO *keybio = BIO_new_mem_buf(RSAKey, -1);

	RSA* pRSAPublicKey = RSA_new();
	rsa = PEM_read_bio_RSAPublicKey(keybio, &rsa, NULL, NULL);
	
	if (SrcLen > 200) 
	{
		nCount = SrcLen / 200;
		nMode = SrcLen - 200 * nCount;

		for (int i = 0; i < nCount; i++) 
		{
			int ret = RSA_public_encrypt(200, SrcData+i*200, CipherData+i*256, rsa, RSA_PKCS1_PADDING);
			if (ret < 0)
				return RSAEncryptError;
		}
		*CipherLen = 256 * nCount;
		if (nMode > 0)
		{
			ret = RSA_public_encrypt(nMode, SrcData + nCount * 200, CipherData + nCount * 256, rsa, RSA_PKCS1_PADDING);
			if (ret < 0)
				return RSAEncryptError;
			*CipherLen = 256 * (nCount + 1);
		}

	}
	else
	{
		ret = RSA_public_encrypt(SrcLen, SrcData, CipherData, rsa, RSA_PKCS1_PADDING);
		if(ret<0)
			return RSAEncryptError;
		*CipherLen = ret;
	}

	//free(encryptedText);
	BIO_free_all(keybio);
	RSA_free(rsa);

	return OperationOK;

}

OpenSSLInterface::ErrorType OpenSSLInterface::RSAPrivateDecrypt(const unsigned char* CipherData, int CipherDataLen,
										const unsigned char* RSAKey, int KeyLen,
										unsigned char* DecodedData, int *DecodedDataLen)
{
	std::string strRet;
	int nCount = 0;
	int DecodeLen = 0;
	RSA *rsa = RSA_new();
	BIO *keybio;
	keybio = BIO_new_mem_buf(RSAKey, -1);
	rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);

	if (CipherDataLen >= 256) 
	{
		nCount = CipherDataLen / 256;
	}
	for (int i = 0; i < nCount; i++) 
	{
		int ret = RSA_private_decrypt(256, CipherData + 256 * i, DecodedData + DecodeLen, rsa, RSA_PKCS1_PADDING);
		if (ret < 0)
			return RSADecryptError;
		DecodeLen += ret;
	}
	*DecodedDataLen = DecodeLen;
	BIO_free_all(keybio);
	RSA_free(rsa);
	return OperationOK;
}
