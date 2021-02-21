#pragma once
#include "KeyboardEvent.h"
#include <queue>

class Keyboard
{
public:
	Keyboard();

	KeyboardEvent readKey();
	unsigned char readChar();

	bool isKeyPressed(unsigned char key);
	bool isBufferKeyEmpty();
	bool isBufferCharEmpty();
	
	void onKeyPressed(const unsigned char key);
	void onKeyReleased(const unsigned char key);
	void onChar(const unsigned char key);

	void enableAutoRepeatKeys();
	void disableAutoRepeatKeys();
	bool isAutoRepeatKeys();

	void enableAutoRepeatChars();
	void disableAutoRepeatChars();
	bool isAutoRepeatChars();

private:
	bool autoRepetKeys = false;
	bool autoRepeatChars = false;
	bool keyStates[256];

	std::queue<KeyboardEvent> keyBuffer;
	std::queue<unsigned char> charBuffer;
};

