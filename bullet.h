#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40

#include "flyingObject.h"
#include "uiDraw.h"

// Put your Bullet class here
class Bullet : public flyingObject
{
public:
	Bullet()
	{
		angle = 0.0;
		setSpeed(7);
		setLives(40);
	}

	void draw(int type);
	void fire(Point point, float angle);
	int getLives();
	void setLives(int l);

	//getters and setters
	void setSpeed(int s) { this->speed = s; }
	int getSpeed() { return speed; }

private:
	float angle;
	int speed;
	int time;
};


#endif /* bullet_h */
