#pragma once

class KeyboardEvent
{
public:
	enum Event {
		Pressed,
		Released,
		Invalid
	};

	KeyboardEvent();
	KeyboardEvent(Event etype, const unsigned char key);
	bool isPressed() const;
	bool isReleased() const;
	bool isInvalid() const;
	unsigned char getKeyCode() const;

private:
	Event etype;
	unsigned char key;
};