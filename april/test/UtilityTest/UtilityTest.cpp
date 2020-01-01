// UtilityTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include"Base64.h"
#include"PackBits.h"
using namespace April::Utility;
int main()
{
	/*
	char buf[] = { 0xfe, 0xff, 0xfe, 0xf0 };
	char outbuf[10] = { 0 };
	int len = Base64::Encode(buf, 4, outbuf);
	std::cout << outbuf << std::endl;
	char decodedbuf[10] = { 0 };
	int decodedlen = Base64::Decode(outbuf, len, decodedbuf);
	for (int i = 0; i < decodedlen; i++)
	{
		std::cout << std::hex << decodedbuf[i]<<" ";
	}
	
	char unpackedbuf[20] = {0};
	int unpackedlen = PackBits::Unpack(buf, 4, unpackedbuf, 20);

    std::cout << "Hello World!\n"; 

	char packedbuf[20] = { 0 };
	int packedlen = PackBits::Pack(unpackedbuf, unpackedlen, packedbuf, 20);
	*/

	char buf[11] = { -16, 0, 5, 112, 0, 1, -64, 0, 7, -18, 0 };
	char outbuf[20] = { 0 };
	int len = Base64::Encode(buf, 11, outbuf);
	char unpacked[1024] = { 0 };
	int lenunpack = PackBits::Unpack(buf, 11, unpacked, 1024);

	char packed[1024] = { 0 };
	int packlen = PackBits::Pack(unpacked, lenunpack, packed, 1024);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
