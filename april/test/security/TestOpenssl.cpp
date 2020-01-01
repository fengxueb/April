#include <iostream>
#include "OpenSSLInterface.h"

using namespace April::Security;

#define MAXBUFF  256
#define RSAKEYBUFFER 2048
void printHash(unsigned char *md, int len)
{
	int i = 0;
	printf("this is 0x type:");
	for (i = 0; i < len; i++)
	{
		printf("%02x", md[i]);
	}
	printf("\n");
}

void printData(unsigned char *md, int len)
{
	int i = 0;
	printf("            :");
	for (i = 0; i < len; i++)
	{
		std::cout <<md[i];
	}
	printf("\n");
}

void MD5test(unsigned char*src,int len)
{
	std::cout << "********************************Test MD5 function**************************************" << std::endl;
	std::cout << "Original data:" << std::endl;
	printData(src,len);
	//test MD5 function
	OpenSSLInterface a;
	unsigned char MD5Digest[MD5LENGTH * 2] = { 0 };
	a.GenerateMD5(src, len, MD5Digest);

	std::cout << "MD5 digest data:" << std::endl;
	printData(MD5Digest, MD5LENGTH * 2);
}

void AEStest(unsigned char*data,int len) 
{
	//test AES function
	std::cout << "********************************Test AES function**************************************" << std::endl;
	std::cout << "Original Data:" << std::endl;
	printData(data, len);

	//key should be set 16 24 32 byte
	std::string aesKey = "ABCDEFFEDCBAABCDBASDKSGIASDHJTCV";
	OpenSSLInterface a;
	
	unsigned char aesEncData3[256] = { 0 };
	unsigned char aesDecData[256] = { 0 };
	int enclen;
	int decodelen;

	unsigned char aesEncData[256] = { 0 };
	a.EncryptionAES(data, len,(unsigned char *)aesKey.c_str(),32, aesEncData, &enclen);
	a.DecryptionAES(aesEncData, enclen, (unsigned char*)aesKey.c_str(),32, aesDecData, &decodelen);
	std::cout << "Decode Data:" << std::endl;
	printData(aesDecData, len);

	std::cout << "Test AES CBC function" << std::endl;
	unsigned char aesEncDatacbc[256] = { 0 };
	a.EncryptionAEScbc(data, len, (unsigned char *)aesKey.c_str(), 32, aesEncDatacbc, &enclen);
	a.DecryptionAEScbc(aesEncDatacbc, enclen, (unsigned char*)aesKey.c_str(), 32, aesDecData, &decodelen);
	printData(aesDecData, len);

	std::cout << "Test AES ECB function" << std::endl;
	unsigned char aesEncDataecb[256] = { 0 };
	a.EncryptionAESecb(data, len, (unsigned char *)aesKey.c_str(), 32, aesEncDataecb, &enclen);
	a.DecryptionAESecb(aesEncDataecb, enclen, (unsigned char*)aesKey.c_str(), 32, aesDecData, &decodelen);
	printData(aesDecData, len);
}

void RSAtest(unsigned char* data,int len)
{
	//test RSA function
	std::cout << "***********************************Test RSA function******************************************" << std::endl;
	std::cout << "Original Data:" << std::endl;
	printData(data, len);

	OpenSSLInterface a;
	int pubkeylen = 0;
	int prikeylen = 0;
	unsigned char pubkey[RSAKEYBUFFER] = { 0 };
	unsigned char prikey[RSAKEYBUFFER] = { 0 };
	a.GenerateRSAKey(pubkey,&pubkeylen, prikey,&prikeylen);

	unsigned char ciphertext[RSAKEYBUFFER] = { 0 };
	unsigned char decodetext[RSAKEYBUFFER] = { 0 };
	int cipherlen;
	int decodelen;
	a.RSAPublicEncrypt(data, len, pubkey, pubkeylen, ciphertext,&cipherlen);
	a.RSAPrivateDecrypt(ciphertext, cipherlen, prikey, prikeylen, decodetext,&decodelen);
	std::cout << "Decodetext:" << std::endl;
	printData(data, len);
}

int main()
{
	//do not input \0
	char md5test1[40] ="honeywell test, this is write by wayne0";
	MD5test((unsigned char*)md5test1, 38);

	char md5test2[18] = "do you like me \\0";
	MD5test((unsigned char*)md5test2, 17);

	char AEStest3[4];
	AEStest3[0] = 'h';
	AEStest3[1] = 0;
	AEStest3[2] = 2;
	AEStest3[3] = 0;

	char AEStest4[2];
	AEStest4[0] = 'h';
	AEStest4[1] = '/';

	char AEStest5[3];
	AEStest5[0] = 'h';
	AEStest5[1] = '/';
	AEStest5[2] = '0';

	AEStest((unsigned char *)AEStest3, 4);
	AEStest((unsigned char *)AEStest4, 2);
	AEStest((unsigned char *)AEStest5, 3);

	char AEStest6[17] = "this is AES test";
	AEStest((unsigned char *)AEStest6, 16);

	char RSAtest1[21] = "how are you, in fime";
	RSAtest((unsigned char*)RSAtest1,20);

	char RSAtest2[RSAKEYBUFFER] = "how are you, in fime hskdhakhjgb shudha shiahdakljol sjdoajda ikpaidaoopa ujjsdiaojaiuhiuaiishui hhhhhhhhhhhhhhhhhh.\
								how are you, in fime hskdhakhjgb shudha shiahdakljol sjdoajda ikpaidaoopa ujjsdiaojaiuhiuaiishui hhhhhhhhhhhhhhhhhh.\
								how are you, in fime hskdhakhjgb shudha shiahdakljol sjdoajda ikpaidaoopa ujjsdiaojaiuhiuaiishui hhhhhhhhhhhhhhhhhh.\
								how are you, in fime hskdhakhjgb shudha shiahdakljol sjdoajda ikpaidaoopa ujjsdiaojaiuhiuaiishui hhhhhhhhhhhhhhhhhh.";
	RSAtest((unsigned char*)RSAtest2, 480);

	char RSAtest3[2];
	RSAtest3[0] = 'x';
	RSAtest3[1] = 0;
	RSAtest((unsigned char*)RSAtest3, 2);


	return true;
}
