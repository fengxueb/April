/****************************************************************************************************
Author:              Date:                 comments
Li,Yangang           December,2019           created

****************************************************************************************************/
#ifndef BASE64_H
#define BASE64_H
namespace April {
	namespace Utility {
		class Base64
		{
		public:
			static int Encode(char* buf, int len, char* outbuf);
			static int Decode(char* buf, int len, char* outbuf);
			
		};
	}
}


#endif //BASE64_H
