#include "PackBits.h"

using namespace April::Utility;


int PackBits::Pack(char* buf, int len, char* outbuf, int outbuflen)
{
	char* src = buf;
	char* dst = outbuf;

	if (buf == nullptr || outbuf == nullptr)
		return -1;

	while (1)
	{
		if (src >= (buf + len))
			break;
		int sameByteNum = 1;
		
		char *next = src + 1;
		while ((*src) == (*next))
		{
			sameByteNum++;
			next = next + 1;
			if (next >= buf + len)
				break;
		}

		if (sameByteNum > 1)
		{
			while (sameByteNum >= 128)
			{
				*dst = -127;
				dst++;
				*dst = *src;
				dst++;
				sameByteNum = sameByteNum - 128;
			}

			if (sameByteNum != 0)
			{
				*dst = 1 - sameByteNum;
				dst++;
				*dst = *src;
				dst++;
				src = next;
			}
			
		}
		else
		{
			int diffBytes = 2;
			while (next + 1 < buf + len)
			{
				if ( *next != *(next + 1) )
				{
					diffBytes++;
					next = next + 1;
				}
				else
				{
					break;
				}
			}
			while (diffBytes - 127 > 0)
			{
				*dst = 127;
				dst++;
				for (int i = 0; i <= 127; i++)
				{
					*dst = *src;
					dst++;
					src++;
				}
				diffBytes = diffBytes - 127;
			}

			if (diffBytes > 0)
			{
				*dst = diffBytes - 1;
				dst++;
				for (int i = 0; i < diffBytes; i++)
				{
					*dst = *src;
					dst++;
					src++;
				}
			}	
		}
	}
	
	return dst- outbuf -1;
}
int PackBits::Unpack(char* buf, int len, char* outbuf, int outbuflen)
{
	if (buf == nullptr || outbuf == nullptr)
		return -1;

	char* src = buf;
	char* dst = outbuf;

	while (1)
	{
		if (src == (buf + len))
		{
			break;
		}
		char* numbyte = src;
		int copyNum = (*numbyte);
		src++;
		if (copyNum < 0)
		{
			if (copyNum != -128)
			{
				copyNum = 1 - copyNum;
				for (int i = 0; i < copyNum; i++)
				{
					*dst = *src;
					if (dst < outbuf + outbuflen)
						dst++;
					else
						return -1;
				}
			}
		
			src++;
		}
		else
		{
			copyNum = copyNum + 1;
			for (int i = 0; i < copyNum; i++)
			{
				*dst = *src;
				if (dst < (outbuf + outbuflen) &&
					src < (buf + len))
				{
					dst++;
					src++;
				}
				else
					return -1;
			}
		}
	}
	return dst- outbuf -1;
}


