#ifndef KYOJIN_ANIM_HPP
#define KYOJIN_ANIM_HPP

class Animator {
public:
	Animator();
	
	void start(int p1, float p2);
	void setAnim(int p1);
	void play(int p1, float p2);

public:
	float _0; // 0x0
	float _4; // 0x4
	int _8; // 0x8
	int _C; // 0xC

	virtual float getSeq() {return _0;} // 0x8
	virtual int getNumFrames(int p1); // 0xC
	virtual void update(); // 0x10
	virtual void stop(); // 0x14
	virtual void eventStart(); // 0x18
	virtual void eventTick(); // 0x1C
	virtual void eventEnd(); // 0x20
};

#endif
