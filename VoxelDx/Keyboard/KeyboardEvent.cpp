#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent() : etype(Event::Invalid), key(0u)
{
}

KeyboardEvent::KeyboardEvent(Event etype, const unsigned char key) : etype(etype), key(key)
{

}

bool KeyboardEvent::isPressed() const
{
	return etype == Event::Pressed;
}

bool KeyboardEvent::isReleased() const
{
	return etype == Event::Released;
}

bool KeyboardEvent::isInvalid() const
{
	return etype == Event::Invalid;
}

unsigned char KeyboardEvent::getKeyCode() const
{
	return key;
}
