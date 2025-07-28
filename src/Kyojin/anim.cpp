#include "Kyojin/anim.hpp"

Animator::Animator()
{
	stop();
}

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

void Animator::start(int p1, float p2)
{
	_4 = p2;
	_8 = p1;

	_C = getNumFrames(_8);

	if (p2 < 0.0f) {
		_0 = (float)(_C - 1);
	} else {
		_0 = 0.0f;
	}

	eventStart();
}

void Animator::stop()
{
	_8 = -1;
	_C = 0;
}

void Animator::play(int p1, float p2)
{
	if (_8 != p1) {
		_4 = p2;
		_8 = p1;

		_C = getNumFrames(_8);

		if (p2 < 0.0f) {
			_0 = (float)(_C - 1);
		} else {
			_0 = 0.0f;
		}

		eventStart();
	}
}

void Animator::update()
{
	eventTick();

    if (_8 >= 0) {
        _0 += _4;
        if (_0 < 0.0f) {
            _0 += _C;
            eventEnd();
        } else if (_0 >= _C) {
            _0 -= _C;
            eventEnd();
        }
    }
}
