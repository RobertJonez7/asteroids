#include "ship.h"
#include "uiDraw.h"
#include "uiInteract.h"

#define ROTATE_AMOUNT 6

/****************************************************************
 * Draws the ship
 ****************************************************************/
void Ship::draw()
{
	drawShip(point, angle, getThrust());
}

/****************************************************************
 * Check to see if alive.
 ****************************************************************/
bool Ship::isAlive()
{
	return alive;
}

/****************************************************************
 * Advance forward depending on where you're looking
 ****************************************************************/
void Ship::engageThrusters()
{
	float x = 3 * (-sin(3.14 / 180.0 * angle));
	float y = 3 * (cos(3.14 / 180.0 * angle));

	velocity.setDy(y);
	velocity.setDx(x);
}

/****************************************************************
 * Calls the engageThrusters() method.
 ****************************************************************/
void Ship::applyThrust()
{
	engageThrusters();
}

/****************************************************************
 * Turns the ship left.
 ****************************************************************/
void Ship::turnLeft()
{
	angle += 6;
}

/****************************************************************
 * Turns the ship right.
 ****************************************************************/
void Ship::turnRight()
{
	angle -= 6;
}

/****************************************************************
 * Gets the angle of the ship.
 ****************************************************************/
float Ship::getAngle() const
{ 
	return angle; 
}

/****************************************************************
 * Getters/setters for thrust (If flames are activated or not).
 ****************************************************************/
bool Ship::getThrust()
{
	return thrust;
}

void Ship::setThrust(bool t)
{
	this->thrust = t;
}
