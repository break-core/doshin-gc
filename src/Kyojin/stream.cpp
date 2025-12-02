#include "Kyojin/stream.hpp"

/*
	Base stream class

	Classes can inherit from Stream to create their own streams.
	See stream.hpp for the rest of the functions. Only these are cpp-implemented.
*/

void Stream::skip(int count)
{
	while (count--)
	{
		readByte();
	}
}

void Stream::getPos()
{
	// "Stream can't get pos" error (needs sys)
}

void Stream::addChecksum(void* buf, int len)
{
	unsigned char* data = (unsigned char*)buf;

	for (int i = 0; i < len; i++)
	{
		this->checksum += data[i];
	}
}
