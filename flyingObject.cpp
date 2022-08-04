#include "flyingObject.h"

/****************************************************************
 * Getter/setters for point.
 ****************************************************************/
Point flyingObject::getPoint()
{
	return point;
}

void flyingObject::setPoint(Point point)
{
	this->point = point;
}

/****************************************************************
 * Getter/setters for velocity.
 ****************************************************************/
Velocity flyingObject::getVelocity()
{
	return velocity;
}

void flyingObject::setVelocity(Velocity velocity)
{
	this->velocity = velocity;
}

/****************************************************************
 * Advance the flying object.
 ****************************************************************/
void flyingObject::advance()
{
	point.setX(point.getX() + velocity.getDx());
	point.setY(point.getY() + velocity.getDy());
}

/****************************************************************
 * Check to see if alive.
 ****************************************************************/
bool flyingObject::isAlive()
{
	return alive;
}

/****************************************************************
 * Handles the screen wrap for all flying objects.
 ****************************************************************/
void flyingObject::wrap(Point tl, Point br)
{
	if (point.getX() < tl.getX())
	{
		point.setX(br.getX());
	}
	if (point.getX() > br.getX())
	{
		point.setX(tl.getX());
	}
	if (point.getY() > tl.getY())
	{
		point.setY(br.getY());
	}
	if (point.getY() < br.getY())
	{
		point.setY(tl.getY());
	}
}

/****************************************************************
 * Kills off the object.
 ****************************************************************/
void flyingObject::kill()
{
	alive = false;
} 

/****************************************************************
 * Getter/setters for size.
 ****************************************************************/
float flyingObject::getSize() const 
{ 
	return size; 
}

void flyingObject::setSize(float s) 
{ 
	this->size = s; 
}

/****************************************************************
 * Getter/setters for lives.
 ****************************************************************/
void flyingObject::setLives(int l) 
{ 
	this->lives = l; 
}

int flyingObject::getLives() 
{ 
	return lives; 
}
		

