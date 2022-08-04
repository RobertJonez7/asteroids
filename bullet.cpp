#include "bullet.h"
#include "uiDraw.h"
#include "ship.h"

/****************************************************************
 * Fires the bullet where the ship is facing.
 ****************************************************************/
void Bullet::fire(Point point, float angle)
{
	this->angle = angle;
	this->point = point;

	velocity.setDy(getSpeed() * (-cos(3.14 / 180.0 * angle)));
	velocity.setDx(getSpeed() * (sin(3.14 / 180.0 * angle)));
}


/****************************************************************
 * Draws the ship.
 ****************************************************************/
void Bullet::draw(int type)
{
	drawDot(point, type);
}


/****************************************************************
 * Getter/setters for lives
 ****************************************************************/
int Bullet::getLives()
{
	return lives;
}

void Bullet::setLives(int l)
{
	this->lives = l;
}

