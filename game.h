/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>
#include "uiInteract.h"
#include "uiDraw.h"
#include "rocks.h"
#include "ship.h"
#include "bullet.h"
#include "powerup.h"

class Game
{
public:
	Game(Point tL, Point bR)
	{
		this->tL = tL;
		this->bR = bR;
		score = 0;
		level = 1;
		astro = 0;
		astroidsDestoyed = 0;
		setType(1);
		setTime(5);
		power = NULL;
	}

	void advance();
	void handleInput(const Interface & pUI);
	void draw(const Interface & pUI);
	void handleCollision();
	void createRocks();
	void cleanUpZombies();
	float getClosestDistance(flyingObject& obj1, flyingObject& obj2) const;
	void createNewAsteroids(int number, Rocks* rPoint);
	void advanceLevel();
	void drawResults();
	void createBullet(int type);
	Powerup* createPowerup();
	void advancePowerUp();

	//getters and setters
	void setScore(int s) { this->score = s; };
	int getScore() { return score; };
	void setLevel(int l) { this->level = l; };
	int getLevel() { return level; };
	int getDestroyed() { return astroidsDestoyed; };
	void setType(int t) { this->type = t; };
	int getType() { return type; };
	int getTime() { return time; }
	void setTime(int t) { this->time = t; }

private:
	std::vector<Rocks*> asteroids;
	std::vector<Bullet> bullets;
	Ship ship;
	Point tL;
	Point bR;
	int score;
	int level;
	int astro;
	int astroidsDestoyed;
	int type;
	Powerup* power;
	int time;
};


#endif /* GAME_H */
