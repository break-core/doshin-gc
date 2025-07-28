#ifndef KYOJIN_ANIM_HPP
#define KYOJIN_ANIM_HPP

class Animator {
public:
	int getNumFrames(int p1);
	void eventTick();
	void eventEnd();
	void setAnim(int p1);
	void update();
	void stop();

public:
	int _0; // 0x0
	float _4; // 0x4
	int _8; // 0x8
	int _C; // 0xC
};

#endif
