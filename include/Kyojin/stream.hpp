class Stream {
public:
	virtual char readByte()
	{
		char value;
		read(&value, sizeof(char));
		return value;
	}
	virtual int readInt()
	{
		int value;
		read(&value, sizeof(int));
		return value;
	}
	virtual float readFloat()
	{
		float value;
		read(&value, sizeof(float));
		return value;
	}
	virtual short readShort()
	{
		short value;
		read(&value, sizeof(short));
		return value;
	}
	virtual void writeByte(char value)
	{
		write(&value, sizeof(char));
	}
	virtual void writeInt(int value)
	{
		write(&value, sizeof(int));
	}
	virtual void writeFloat(float value)
	{
		write(&value, sizeof(float));	
	}
	virtual void writeShort(short value) 
	{
		write(&value, sizeof(short));
	}
	virtual int read(void* buf, int size) { return 0; }
	virtual int write(void* buf, int size) { return 0; }
	virtual void skip(int count);
	virtual void seekTo(int count)
	{
		rewind();
		skip(count);
	}
	virtual int eof() { return 0; }
	virtual void rewind() {}
	virtual void close() {}
	virtual void flush() {}
	virtual int getLength() { return 0; }
	virtual int getBuffer() { return 0; }
	virtual void resetChecksum() { checksum = 0; }
	virtual long getChecksum() { return ~checksum; }
	virtual int newData(int) { return 0; }
	virtual void getPos();

	void addChecksum(void* buf, int len);

public:
	int _4;
	int _8;
	int _C;
	long checksum;
};
