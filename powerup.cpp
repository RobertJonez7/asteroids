#include "powerup.h"
#include "uiDraw.h"

/****************************************************************
 * Draws the shotgun powerup
 ****************************************************************/
void Shotgun::draw()
{
	drawToughBird(getPoint(), 10, 1, 1);
	setGun(2);
}

/****************************************************************
 * Draws the sniper powerup
 ****************************************************************/
void Sniper::draw()
{
	drawToughBird(getPoint(), 10, 2, 2);
	setGun(3);
}

/****************************************************************
 * Draws the 360 laser powerup
 ****************************************************************/
void Laser::draw()
{
	drawToughBird(getPoint(), 10, 3, 3);
	setGun(4);
}
