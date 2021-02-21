#pragma once

#include "MouseEvent.h"
#include <queue>

class Mouse
{
public:
	void onPressLeft(int x, int y);
	void onReleaseLeft(int x, int y);
	bool isPressedLeft();

	void onPressRight(int x, int y);
	void onReleaseRight(int x, int y);
	bool isPressedRight();

	void onPressWheel(int x, int y);
	void onReleaseWheel(int x, int y);
	bool isPressedWheel();

	void onWheelUp(int x, int y);
	void onWheelDown(int x, int y);
	void onMove(int ax, int ay);
	void onMoveRaw(int ax, int ay);

	MousePoint getPosition() const;
	int getPositionX() const;
	int getPositionY() const;

	bool isEventBufferEmpty();
	MouseEvent readEvent();

private:
	std::queue<MouseEvent> eventBuffer;
	bool leftPressed = false;
	bool rightPressed = false;
	bool wheelPressed = false;
	int x = 0, y = 0;
};

