#include "rocks.h"
#include "uiDraw.h"
#include "point.h"

/****************************************************************
 * Draws the small rock
 ****************************************************************/
void SmallRock::draw()
{
	drawSmallAsteroid(point, 2);
}

/****************************************************************
 * Draws the medium rock
 ****************************************************************/
void MediumRock::draw()
{
	drawMediumAsteroid(point, 3);
}

/****************************************************************
 * Draws the large rock
 ****************************************************************/
void LargeRock::draw()
{
	drawLargeAsteroid(point, 10);
}

/****************************************************************
 * Getters/setters for the kind of rock it is.
 ****************************************************************/
void Rocks::setKind(int k)
{
	this->kind = k;
}

int Rocks::getKind()
{
	return kind;
}

/****************************************************************
 * Getters/setters for score. Score will be present in update.
 ****************************************************************/
int Rocks::getScoreType()
{
	return scoreType;
}

void Rocks::setScoreType(int s)
{
	this->scoreType = s;
}

/****************************************************************
 * Kills off rocks
 ****************************************************************/
void Rocks::die()
{
	life = false;
}

/****************************************************************
 * Check to see if rock is dead.
 ****************************************************************/
bool Rocks::getLife() 
{ 
	return life; 
}
