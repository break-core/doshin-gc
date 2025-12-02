#include "Kyojin/stream.hpp"
#include "stdarg.h"

// TODO: Get rid of this when the proper headers exist.
extern "C" int atoi(const char* str);
extern "C" double atof(const char* str);
extern "C" int vsprintf(char* s, const char* format, va_list arg);

class TxtStream
{
public:
	virtual int readInt();
	virtual float readFloat();
	virtual int readWord(char* dst, int len);
	virtual void skipLine();
	virtual void skipWS();
	virtual void writeln(char* buf);
	virtual void startPrint();
	virtual void endPrint();

	void printf(const char* format, ...);

	bool isLine(char c)
	{
		return (c == '\r' || c == '\n');
	}

	// Inline function with unofficial name
	bool isWS(char c)
	{
		return (c == ' ' || c == '\t' || c == '\r' || c == '\n');
	}

public:
	int _00;
	int _04;
	Stream* src;
};
