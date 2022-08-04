#ifndef flyingObject_h
#define flyingObject_h

#include "point.h"
#include "velocity.h"

class flyingObject
{
public:
	flyingObject()
	{
		alive = true;
		size = 0;
		lives = 0;
	}

	Point getPoint();
	void setPoint(Point point);
	Velocity getVelocity();
	void setVelocity(Velocity velocity);
	void advance();
	bool isAlive();
	void wrap(Point tl, Point br);
	void kill();
	float getSize() const;
	void setSize(float s);
	void setLives(int l);
	int getLives();

protected:
	Point point;
	Velocity velocity;
	bool alive;
	int size;
	int lives;

private:
	
};




#endif /* flyingObject_h */
