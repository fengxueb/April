/**************************************************************************
Author: Feng Xuebing 
Date:2019-09-06
**************************************************************************/
#ifndef OPENSSLINTERFACE_H
#define OPENSSLINTERFACE_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>


#define MD5LENGTH  16
#define SHA1LENGTH 20
#define SHA256LENGTH 32
#define MAXDATABUFFER 1024
#define RSAKEYLENGTH 2048

namespace April 
{
	namespace Security
	{
		class OpenSSLInterface
		{

		public:
			enum ErrorType
			{
				OperationOK = 0,
				RSAEncryptError,
				RSADecryptError,
				AESEncryptError,
				AESDecryptError,
				AEScbcEncryptError,
				AEScbcDecryptError,
				AESecbEncryptError,
				AESecbDecryptError
			};
			//MD5 function
			void GenerateMD5(const unsigned char* SrcData, int SrcLen, unsigned char* EncodedHexStr);

			//SHA256 function
			void GenerateSHA256(const unsigned char* SrcData, int len ,unsigned char *CipherData);
	
			//AES function
			ErrorType EncryptionAES(const unsigned char* SrcData,int SrcLen,
						const unsigned char* AESKey, int KeyLen,
						unsigned char* CipherData,int *CipherLen);
			ErrorType EncryptionAEScbc(const unsigned char* SrcData, int SrcLen,
						const unsigned char* AESKey, int KeyLen,
						unsigned char* CipherData, int *CipherLen);
			ErrorType EncryptionAESecb(const unsigned char* SrcData, int SrcLen,
						const unsigned char* AESKey, int KeyLen,
						unsigned char* CipherData, int *CipherLen);
			ErrorType DecryptionAES(const unsigned char* SrcData, int SrcLen,
						const unsigned char* AESKey, int KeyLen,
						unsigned char* DecodeData, int *DecodeDataLen);
			ErrorType DecryptionAEScbc(const unsigned char* SrcData, int SrcLen,
							const unsigned char* AESKey, int KeyLen,
							unsigned char* DecodeData, int *DecodeDataLen);
			ErrorType DecryptionAESecb(const unsigned char* SrcData, int SrcLen,
						const unsigned char* AESKey, int KeyLen,
						unsigned char* DecodeData, int *DecodeDataLen);

			//RSA function
			void GenerateRSAKey(unsigned char* publicKey,int* PubKeyLen, unsigned char* privateKey,int* PriKeyLen);

			ErrorType RSAPublicEncrypt(const unsigned char* SrcData, int SrcLen,
						const unsigned char* RSAKey, int KeyLen,
						unsigned char* CipherData, int *CipherLen);
			ErrorType RSAPrivateDecrypt(const unsigned char* CipherData, int CipherDataLen,
						const unsigned char* RSAKey, int KeyLen,
						unsigned char* DecodedData, int *DecodedDataLen);

		};
	}
	
}

#endif // !OPENSSLINTERFACE_H

