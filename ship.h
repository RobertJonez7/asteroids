#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

#include "flyingObject.h"

// Put your Ship class here
class Ship : public flyingObject
{
public:
	Ship()
	{
		velocity.setDx(0);
		velocity.setDy(0);
		angle = 0.0;
		setSize(10);
		setLives(2);
		thrust = false;
	}

	void draw();
	bool isAlive();
	void applyThrust();
	void turnLeft();
	void turnRight();
	float getAngle() const;
	void engageThrusters();
	bool getThrust();
	void setThrust(bool t);

private:
	float angle;
	float thrust;
};

#endif /* ship_h */
