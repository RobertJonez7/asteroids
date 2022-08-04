#pragma once
#include "point.h"
#include "uiDraw.h"
#include "flyingObject.h"

class Powerup : public flyingObject
{
public:
	Powerup()
	{
		setPoint(Point(random(-200, 200), random(-200, 200)));
		setGun(1);
	}
	virtual void draw() = 0;

	//getters and setters
	int getGun() { return gun; }
	void setGun(int g) { this->gun = g; }
	
private:
	int gun;
};

class Shotgun : public Powerup
{
public:
	Shotgun()
	{

	}
	void draw();

private:
};

class Sniper : public Powerup
{
public:
	Sniper()
	{

	}
	void draw();

private:
};

class Laser : public Powerup
{
public:
	Laser()
	{

	}
	void draw();

private:
};

