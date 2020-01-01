/****************************************************************************************************
Author:              Date:                 comments
Li,Yangang           December,2019           created

****************************************************************************************************/
#ifndef BITSTRINGCONVERTER_H
#define BITSTRINGCONVERTER_H
#include<string>
namespace April {
	namespace Utility {
		class BitStringConverter
		{
		public:
			static std::string byte2bitString(unsigned char ch[], int byteslen);
			static int bitstring2Byte(std::string bitstr, unsigned char bytes[], int lenbytes);
		};
	}
}

#endif //BITSTRINGCONVERTER_H

