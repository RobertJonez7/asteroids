#include "velocity.h"
#include <math.h>

/****************************************************************
 * Getters and setters for Dx/Dy.
 ****************************************************************/
float Velocity::getDx() const
{
	return dx;
}

float Velocity::getDy() const
{
	return dy;
}

void Velocity::setDx(float dx)
{
	this->dx = dx;
}

void Velocity::setDy(float dy)
{
	this->dy = dy;
}




