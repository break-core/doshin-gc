#include "Kyojin/txtstream.hpp"

// Temporary storage for readInt/readFloat
char tmp[0x20];

// Reads a word as big as tmp (0x20) and converts to an int.
int TxtStream::readInt()
{
	readWord(tmp, sizeof(tmp));

	return atoi(tmp);
}

// Reads a word as big as tmp (0x20) and converts to a float.
float TxtStream::readFloat()
{
	readWord(tmp, sizeof(tmp));

	return atof(tmp);
}

// Reads a word into `dst` for `len` amount.
// WARNING: Whitespace will cause reading to break.
int TxtStream::readWord(char* dst, int len)
{
	char* buf = dst;
	int i = 0;

	while (i < len)
	{
		char c = this->src->readByte();

		if (isWS(c) != false) 
		{
			break;
        }

		*buf = c;
		buf++;
		i++;
	}

	dst[i] = 0;
	return i;
}

// Skips whitespace recursively in a stream until there is none.
// Whitespace is spaces, tabs, CR characters, and newlines.
void TxtStream::skipWS()
{
	while (true)
	{
		// Read a byte
		char c = this->src->readByte();

		// If the byte was whitespace, continue the loop again
        if (isWS(c) != false) 
		{
            continue;
        }

		// When no whitespace is present we break the loop.
        break;
	}

	this->src->skip(-1);
}

// Skips over CR characters and newlines until there is none.
void TxtStream::skipLine()
{
	while (true)
	{
		char c = this->src->readByte();

		if (isLine(c))
		{
			break;
		}
	}
}

// Minor issues having to do with stack(?)
void TxtStream::printf(const char* format, ...)
{
	startPrint();

	char buf[0xff];
	va_list args;

	va_start(args, format);
	vsprintf(buf, format, args);
	va_end(args);

	writeln(buf);

	endPrint();
}

void TxtStream::endPrint()
{

}

void TxtStream::startPrint()
{

}

void TxtStream::writeln(char* buf)
{

}
