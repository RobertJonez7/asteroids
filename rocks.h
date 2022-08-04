#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#include "flyingObject.h"
#include "point.h"
#include "velocity.h"
#include "uiDraw.h"

class Rocks : public flyingObject
{
public:
	Rocks()
	{
		setPoint(Point(200, random(-200, 200)));

		float x = 1.0 * (-sin(3.14 / 180.0 * random(1, 360)));
		float y = 1.0 * (cos(3.14 / 180.0 * random(1, 360)));

		velocity.setDx(x);
		velocity.setDy(y);

		kind = 1;
		scoreType = 0;
		life = true;
	}

	virtual void draw() {}
	void setKind(int k);
	int getKind();
	int getScoreType();
	void setScoreType(int s);
	void die();
	bool getLife();


private:
	int kind;
	int scoreType;
	bool life;
};

class SmallRock : public Rocks
{
public:
	SmallRock()
	{
		float x = 2.0 * (-sin(3.14 / 180.0 * random(1, 360)));
		float y = 2.0 * (cos(3.14 / 180.0 * random(1, 360)));

		setSize(10);
		setKind(3);
		setScoreType(50);
	}

	void draw();

private:

};

class MediumRock : public Rocks
{
public:
	MediumRock()
	{
		float x = 1.5 * (-sin(3.14 / 180.0 * random(1, 360)));
		float y = 1.5 * (cos(3.14 / 180.0 * random(1, 360)));

		setSize(15);
		setKind(2);
		setScoreType(30);
	}

	void draw();

private:

};

class LargeRock : public Rocks
{
public:
	LargeRock()
	{
		float x = 1.0 * (-sin(3.14 / 180.0 * random(1, 360)));
		float y = 1.0 * (cos(3.14 / 180.0 * random(1, 360)));

		setSize(17);
		setKind(1);
		setScoreType(15);
	}

	void draw();

private:

};



#endif /* rocks_h */
