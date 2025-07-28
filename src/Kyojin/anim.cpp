#include "Kyojin/anim.hpp"

int Animator::getNumFrames(int p1)
{
	return 0;
}

void Animator::eventTick()
{
	// Implemented in other classes
}

void Animator::eventEnd()
{
	// Implemented in other classes
}

void Animator::setAnim(int p1)
{
	_8 = p1;
}

void Animator::stop()
{
	_8 = -1;
	_C = 0;
}

void Animator::update()
{
	
}
