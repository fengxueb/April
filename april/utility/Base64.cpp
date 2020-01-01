/****************************************************************************************************
Author:              Date:                 comments
Li,Yangang           December,2019           created

****************************************************************************************************/
#include "Base64.h"

using namespace April::Utility;

static const char base64EncodeChar[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const signed char _base64_decode_chars[] =
{
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
	-1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
	-1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1
};

int Base64::Encode(char* buf, int len, char* outbuf)
{
	int i = 0;
	int index = 0;
	unsigned char c1;
	unsigned char c2;
	unsigned char c3;

	if (nullptr == buf || nullptr == outbuf)
	{
		return -1;
	}

	while (i < len)
	{
		c1 = buf[i++];
		if (i == len)
		{
			outbuf[index++] = base64EncodeChar[c1 >> 2];
			outbuf[index++] = base64EncodeChar[(c1 & 0x3) << 4];
			outbuf[index++] = '=';
			outbuf[index++] = '=';
			break;
		}

		c2 = buf[i++];
		if (i == len)
		{
			outbuf[index++] = base64EncodeChar[c1 >> 2];
			outbuf[index++] = base64EncodeChar[((c1 & 0x3) << 4) | ((c2 & 0xF0) >> 4)];
			outbuf[index++] = base64EncodeChar[(c2 & 0xF) << 2];
			outbuf[index++] = '=';
			break;
		}

		c3 = buf[i++];

		outbuf[index++] = base64EncodeChar[c1 >> 2];
		outbuf[index++] = base64EncodeChar[((c1 & 0x3) << 4) | ((c2 & 0xF0) >> 4)];
		outbuf[index++] = base64EncodeChar[((c2 & 0xF) << 2) | ((c3 & 0xC0) >> 6)];
		outbuf[index++] = base64EncodeChar[c3 & 0x3F];
	}

	return index;
}
int Base64::Decode(char* buf, int len, char* outbuf)
{

	int i = 0;
	int index = 0;
	signed char c1;
	signed char c2;
	signed char c3;
	signed char c4;

	while (i < len)
	{
		do
		{
			c1 = _base64_decode_chars[(int)buf[i++]];
		} while ((i < len) && (c1 == -1));
		if (c1 == -1)
		{
			break;
		}

		do
		{
			c2 = _base64_decode_chars[(int)buf[i++]];
		} while ((i < len) && (c2 == -1));
		if (c2 == -1)
		{
			break;
		}
		outbuf[index++] = (char)((c1 << 2) | ((c2 & 0x30) >> 4));

		do
		{
			c3 = buf[i++];
			if (c3 == 61)
			{
				return index;
			}
			c3 = _base64_decode_chars[(int)c3];
		} while ((i < len) && (c3 == -1));
		if (c3 == -1)
		{
			break;
		}
		outbuf[index++] = (char)(((c2 & 0XF) << 4) | ((c3 & 0x3C) >> 2));

		do
		{
			c4 = buf[i++];
			if (c4 == 61)
			{
				return index;
			}

			c4 = _base64_decode_chars[(int)c4];
		} while ((i < len) && (c4 == -1));

		if (c4 == -1)
		{
			break;
		}
		outbuf[index++] = (char)(((c3 & 0x03) << 6) | c4);
	}

	return index;
}