#ifndef PACKBITS_H
#define PACKBITS_H
namespace April {
	namespace Utility {

		class PackBits
		{
		public:
			static int Pack(char* buf, int len, char* outbuf, int outlen);
			static int Unpack(char* buf, int len, char* outbuf, int outlen);
		};

	}
}

#endif

