#include "Keyboard.h"

void Keyboard::enableAutoRepeatKeys()
{
	this->autoRepetKeys = true;
}

void Keyboard::disableAutoRepeatKeys()
{
	this->autoRepetKeys = false;
}

bool Keyboard::isAutoRepeatKeys()
{
	return this->autoRepetKeys;
}

void Keyboard::enableAutoRepeatChars()
{
	this->autoRepeatChars = true;
}

void Keyboard::disableAutoRepeatChars()
{
	this->autoRepeatChars = false;
}

bool Keyboard::isAutoRepeatChars()
{
	return this->autoRepeatChars;
}

Keyboard::Keyboard()
{
	for (unsigned int i = 0; i < 256; i++) {
		this->keyStates[i] = false;
	}
}

KeyboardEvent Keyboard::readKey()
{
	if (this->keyBuffer.empty())
		return KeyboardEvent();

	KeyboardEvent e = this->keyBuffer.front();
	this->keyBuffer.pop();

	return e;
}

unsigned char Keyboard::readChar()
{
	if (this->charBuffer.empty())
		return 0;

	unsigned char ch = this->charBuffer.front();
	this->charBuffer.pop();

	return ch;
}

bool Keyboard::isKeyPressed(unsigned char key)
{
	return this->keyStates[key];
}

bool Keyboard::isBufferKeyEmpty()
{
	return this->keyBuffer.empty();
}

bool Keyboard::isBufferCharEmpty()
{
	return this->charBuffer.empty();
}

void Keyboard::onKeyPressed(const unsigned char key)
{
	this->keyStates[key] = true;
	this->keyBuffer.push(KeyboardEvent(KeyboardEvent::Event::Pressed, key));
}

void Keyboard::onKeyReleased(const unsigned char key)
{
	this->keyStates[key] = false;
	this->keyBuffer.push(KeyboardEvent(KeyboardEvent::Event::Released, key));
}

void Keyboard::onChar(const unsigned char key)
{
	this->charBuffer.push(key);
}
