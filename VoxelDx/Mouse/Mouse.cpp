#include "Mouse.h"

void Mouse::onPressLeft(int x, int y)
{
	this->x = x;
	this->y = y;
	leftPressed = true;
	eventBuffer.push(MouseEvent(MouseEvent::Event::LeftPressed, x, y));
}

void Mouse::onReleaseLeft(int x, int y)
{
	this->x = x;
	this->y = y;
	leftPressed = false;
	eventBuffer.push(MouseEvent(MouseEvent::Event::LeftReleased, x, y));
}

bool Mouse::isPressedLeft()
{
	return leftPressed;
}

void Mouse::onPressRight(int x, int y)
{
	this->x = x;
	this->y = y;
	rightPressed = true;
	eventBuffer.push(MouseEvent(MouseEvent::Event::RightPressed, x, y));
}

void Mouse::onReleaseRight(int x, int y)
{
	this->x = x;
	this->y = y;
	rightPressed = false;
	eventBuffer.push(MouseEvent(MouseEvent::Event::RightReleased, x, y));
}

bool Mouse::isPressedRight()
{
	return rightPressed;
}

void Mouse::onPressWheel(int x, int y)
{
	this->x = x;
	this->y = y;
	wheelPressed = true;
	eventBuffer.push(MouseEvent(MouseEvent::Event::MouseWheelPressed, x, y));
}

void Mouse::onReleaseWheel(int x, int y)
{
	this->x = x;
	this->y = y;
	wheelPressed = false;
	eventBuffer.push(MouseEvent(MouseEvent::Event::MouseWheelReleased, x, y));
}

bool Mouse::isPressedWheel()
{
	return wheelPressed;
}

void Mouse::onWheelUp(int x, int y)
{
	this->x = x;
	this->y = y;
	eventBuffer.push(MouseEvent(MouseEvent::Event::MouseWheelUp, x, y));
}

void Mouse::onWheelDown(int x, int y)
{
	this->x = x;
	this->y = y;
	eventBuffer.push(MouseEvent(MouseEvent::Event::MouseWheelDown, x, y));
}

void Mouse::onMove(int ax, int ay)
{
	this->x = ax;
	this->y = ay;
	eventBuffer.push(MouseEvent(MouseEvent::Event::Move, ax, ay));
}

void Mouse::onMoveRaw(int ax, int ay)
{
	this->x = ax;
	this->y = ay;
	eventBuffer.push(MouseEvent(MouseEvent::Event::RawMove, ax, ay));
}

MousePoint Mouse::getPosition() const
{
	return { x, y };
}

int Mouse::getPositionX() const
{
	return x;
}

int Mouse::getPositionY() const
{
	return y;
}

bool Mouse::isEventBufferEmpty()
{
	return eventBuffer.empty();
}

MouseEvent Mouse::readEvent()
{
	if (this->eventBuffer.empty())
		return MouseEvent();

	MouseEvent e = this->eventBuffer.front();
	eventBuffer.pop();
	return e;
}
