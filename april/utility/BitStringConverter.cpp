#include "BitStringConverter.h"
using namespace April::Utility;


std::string BitStringConverter::byte2bitString(unsigned char ch[], int byteslen)
{
	std::string result = "";
	for (int j = 0; j < byteslen; j++)
	{
		unsigned char uch = 128;
		for (int i = 0; i < 8; i++)
		{
			if (uch& ch[j])
			{
				result += "1";
			}
			else
			{
				result += "0";
			}
			uch = uch >> 1;
		}
	}

	return result;
}
int BitStringConverter::bitstring2Byte(std::string bitstr, unsigned char bytes[], int lenbytes)
{

	int len = bitstr.length();
	if (len % 8 != 0)
	{
		return -1;
	}

	if (lenbytes < len / 8)
	{
		return -1;
	}

	int k = 0;
	for (int i = 0; i < len; i = i + 8)
	{
		unsigned char ch = 128;
		unsigned char val = 0x00;

		for (int j = 0; j < 8; j++)
		{
			if (bitstr[i + j] == '1')
			{
				val = val + ch;
			}
			ch = ch >> 1;
		}
		bytes[k++] = val;
	}
	return len / 8;
}
