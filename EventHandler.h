#pragma once
#include"Vector2.h"
#include"Vector3.h"
class EventHandler
{
	bool isRunning = true;
	int mousedX = 0;
	int mousedY = 0;
	int verticalMove = 0;
	Vector3 WSAD;
public:
	void handleEvents();
	bool getIsRunning() const;
	int getMousedX()const;
	int getMousedY()const;
	int getVerticalMove() const;
	Vector3 getWSAD();
};

