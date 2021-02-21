#pragma once

struct MousePoint {
	int x;
	int y;
};

class MouseEvent
{
public:
	enum Event {
		LeftPressed,
		LeftReleased,
		RightPressed,
		RightReleased,
		MouseWheelUp,
		MouseWheelDown,
		MouseWheelPressed,
		MouseWheelReleased,
		Move,
		RawMove,
		Invalid
	};

private:
	Event etype;
	int x, y;

public:
	MouseEvent();
	MouseEvent(const Event etype, const int x, const int y);
	
	bool isValid() const;
	Event getType() const;
	
	MousePoint getPosition() const;
	int getPositionX() const;
	int getPositionY() const;
};

