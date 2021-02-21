#include "MouseEvent.h"

MouseEvent::MouseEvent() : etype(MouseEvent::Event::Invalid), x(0), y(0)
{
}

MouseEvent::MouseEvent(const Event etype, const int x, const int y) : etype(etype), x(x), y(y)
{
}

bool MouseEvent::isValid() const
{
	return !(this->etype == Event::Invalid);
}

MouseEvent::Event MouseEvent::getType() const
{
	return this->etype;
}

MousePoint MouseEvent::getPosition() const
{
	return {this->x, this->y };
}

int MouseEvent::getPositionX() const
{
	return this->x;
}

int MouseEvent::getPositionY() const
{
	return this->y;
}
