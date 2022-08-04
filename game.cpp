/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"
#include "uiDraw.h"
#include <limits>
#include <algorithm>
#include <vector>
using namespace std;

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/

float Game :: getClosestDistance(flyingObject &obj1, flyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

/****************************************************************
 * Advances the game.
 ****************************************************************/
void Game::advance()
{
	//advance ship
	if (ship.isAlive())
	{
		ship.advance();
		ship.wrap(tL, bR);
	}

	//advance the poweup
	advancePowerUp();

	//advance asteroids
	if (ship.isAlive())
	{	
		int count = 0;
		for (vector<Rocks*>::iterator it = asteroids.begin(); it != asteroids.end(); ++it)
		{
			if (*it != NULL)
			{
				count++;
			}
		}
		if (count == 0)
		{
			createRocks();
		} 

		for (int i = 0; i < asteroids.size(); i++)
		{
			asteroids[i]->advance();
			asteroids[i]->wrap(tL, bR);
		}
	}

	//advance bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			bullets[i].advance();
			bullets[i].wrap(tL, bR);
			bullets[i].setLives(bullets[i].getLives() - 1);

			if (bullets[i].getLives() < 0) 
			{ 
				bullets.erase(bullets.begin() + i); 
			}
		}
	}

	handleCollision();
	cleanUpZombies();
	setLevel(astro);
	drawResults();
}

/****************************************************************
 * Creates 5 large asteroids if there are no more on screen.
 ****************************************************************/
void Game::createRocks()
{
	advanceLevel();

	for (int i = 0; i < 4 + astro; i++)
	{
		Rocks* tempRock = NULL;
		tempRock = new LargeRock;
		asteroids.push_back(tempRock);
	}
}

/****************************************************************
 * Advance to next level and get one extra life + more rocks.
 ****************************************************************/
void Game::advanceLevel()
{
	astro++;
	ship.setLives(ship.getLives() + 1);
}

/****************************************************************
 * Allows the user to move ship around screen.
 ****************************************************************/
void Game::handleInput(const Interface& ui)
{
	if (ship.isAlive())
	{
		if (ui.isUp())
		{
			ship.applyThrust();
			ship.setThrust(true);
		}

		if (ui.isDown())
		{
			
		}

		if (ui.isLeft())
		{
			ship.turnLeft();
		}

		if (ui.isRight())
		{
			ship.turnRight();
		}
		if (ui.isSpace())
		{
			createBullet(type);
		}
	}
}
/****************************************************************
 * Creates different types of bullets
 ****************************************************************/
void Game::createBullet(int type)
{
	//standard bullet
	if (type == 1)
	{
		Bullet newBullet;
		newBullet.fire(ship.getPoint(), ship.getAngle() + 180);

		bullets.push_back(newBullet);
	}
	//shotgun bullet
	else if (type == 2)
	{
		int angle = 160;
		for (int i = 0; i < 5; i++)
		{

			Bullet newBullet;
			newBullet.setSpeed(9);
			newBullet.fire(ship.getPoint(), ship.getAngle() + angle);

			bullets.push_back(newBullet);

			angle += 10;
		}
	}
	//sniper bullet
	else if (type == 3)
	{
		Bullet newBullet;
		newBullet.setSpeed(22);
		newBullet.fire(ship.getPoint(), ship.getAngle() + 180);

		bullets.push_back(newBullet);
	}
	//360 laser gun
	else if (type == 4)
	{
		int angle = 0;
		for (int i = 0; i < 18; i++)
		{
			Bullet newBullet;
			newBullet.setSpeed(4);
			newBullet.fire(ship.getPoint(), ship.getAngle() + angle);

			bullets.push_back(newBullet);
			angle += 20;
		}
	}

	//Limits the powerup gun to 5 shots
	if (type != 1)
	{
		setTime(getTime() - 1);
	}
	if (getTime() <= 0)
	{
		setType(1);
		setTime(5);
	}
}

/****************************************************************
 * Advances the powerups on the screen.
 ****************************************************************/
void Game::advancePowerUp()
{
	if (power == NULL)
	{
		if (random(0, 120) == 0)
		{
			power = createPowerup();
		}
	}
	else
	{
		if (power->isAlive() && ship.isAlive())
		{
			power->draw();

			if (getClosestDistance(ship, *power) <=
				fabs((ship.getSize() + power->getSize())))
			{
				setType(power->getGun());
				setTime(5);
				power->kill();
			}
		}
	}
}

/****************************************************************
 * Creates a random powerup
 ****************************************************************/
Powerup* Game::createPowerup()
{
	Powerup* newPower = NULL;

	int rand = random(1, 4);

	if (rand == 1)
	{
		newPower = new Sniper;
	}
	if (rand == 2)
	{
		newPower = new Shotgun;
	}
	if (rand == 3)
	{
		newPower = new Laser;
	}
	return newPower;
}

/****************************************************************
 * Kills off asteroids/bullets/ship/powerup when they collide.
 ****************************************************************/
void Game::handleCollision()
{ 
	for (int a = 0; a < asteroids.size(); a++) 
	{
		Rocks* rPoint = asteroids[a];

		for (int b = 0; b < bullets.size(); b++) 
		{
			if (getClosestDistance(bullets[b], *asteroids[a]) <= 
				fabs((bullets[b].getSize() + asteroids[a]->getSize())))
			{
				bullets[b].kill();
				asteroids[a]->die();
				if (!asteroids[a]->getLife() && getType() != 3)
				{
					createNewAsteroids(rPoint->getKind(), rPoint);
					setScore(getScore() + asteroids[a]->getScoreType());
				}
				else
				{
					setScore(getScore() + 100);
				}
				astroidsDestoyed++;
			}
		}
		if (getClosestDistance(ship, *asteroids[a]) <=
			fabs((ship.getSize() + asteroids[a]->getSize())))
		{
			ship.setLives(ship.getLives() - 1);
			asteroids[a]->die();

			if (ship.getLives() <= 0)
			{
				ship.kill();
				cout << "Game Over!" << endl;
				cout << "Your final score: " << getScore() << endl;
				cout << "You reached level: " << getLevel() << endl;
				cout << "You destroyed " << getDestroyed() << " asteroids!" << endl;
			}
		}
	}
}

/****************************************************************
 * Creates new smaller asteroids when old ones die.
 ****************************************************************/
void Game::createNewAsteroids(int number, Rocks* rPoint)
{
	if (number == 1)
	{
		//create two medium rocks
		for (int i = 0; i < 2; i++)
		{
			int angle = -1;
		
			Rocks* tempRock = NULL;
			tempRock = new MediumRock;
			tempRock->setPoint(rPoint->getPoint());
			tempRock->getVelocity().setDy(angle);
			asteroids.push_back(tempRock);

			angle += 2;
		}
	
		//create small rock
		Rocks* tempRockSmall = NULL;
		tempRockSmall = new SmallRock;
		tempRockSmall->setPoint(rPoint->getPoint());
		tempRockSmall->getVelocity().setDx(-2);
		asteroids.push_back(tempRockSmall);
	}
	if (number == 2)
	{
		//create two small rocks
		for (int i = 0; i < 2; i++)
		{
			int angle = -3;
	
			Rocks* tempRock = NULL;
			tempRock = new SmallRock;
			tempRock->setPoint(rPoint->getPoint());
			tempRock->getVelocity().setDx(angle);
			asteroids.push_back(tempRock);
		
			angle += 6;
		}
	}
}

/****************************************************************
 * Deletes old objects that are no longer in use.
 ****************************************************************/
void Game::cleanUpZombies() 
{
	//clean up asteroids if dead
	vector<Rocks*>::iterator it = asteroids.begin();
	while (it != asteroids.end())
	{
		Rocks* rock = *it;

		if (!rock->getLife())
		{
			it = asteroids.erase(it);
		}
		else
		{
			it++;
		}
	}
	for (int i = 0; i < asteroids.size(); i++)
	{
		if (!asteroids[i]->isAlive())
		{
			delete asteroids[i];
		}
	}
	//cleans up bullets if they are dead
	vector<Bullet>::iterator itb = bullets.begin();
	while (itb != bullets.end())
	{
		Bullet bullet = *itb;

		if (!bullet.isAlive())
		{
			itb = bullets.erase(itb);
		}
		else
		{
			itb++;
		}
	}
	if (power != NULL && !power->isAlive())
	{
		delete power;
		power = NULL;
	}
}
	
/****************************************************************
 * Draws all of the assets on screen.
 ****************************************************************/
void Game::draw(const Interface & pUI)
{
	if (ship.isAlive())
	{
		ship.draw();

		//draws the score
		Point scoreLocation;
		scoreLocation.setX(tL.getX() + 45);
		scoreLocation.setY(tL.getY() - 5);

		Point scoreLabel;
		scoreLabel.setX(tL.getX() + 5);
		scoreLabel.setY(tL.getY() - 15);

		//draws the lives
		Point livesLocation;
		livesLocation.setX(tL.getX() + 385);
		livesLocation.setY(tL.getY() - 5);

		Point livesLabel;
		livesLabel.setX(tL.getX() + 345);
		livesLabel.setY(tL.getY() - 15);

		//draws the level
		Point levelLocation;
		levelLocation.setX(tL.getX() + 220);
		levelLocation.setY(tL.getY() - 5);

		Point levelLabel;
		levelLabel.setX(tL.getX() + 180);
		levelLabel.setY(tL.getY() - 15);

		drawNumber(scoreLocation, getScore());
		drawText(scoreLabel, "Score: ");

		drawNumber(livesLocation, ship.getLives());
		drawText(livesLabel, "Lives: ");

		drawNumber(levelLocation, getLevel());
		drawText(levelLabel, "Level: ");

		for (int i = 0; i < asteroids.size(); i++)
		{
			if (asteroids[i]->getLife())
			{
				asteroids[i]->draw();
			}
		}

		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i].isAlive())
			{
				bullets[i].draw(getType());
			}
		}
	}
}

/****************************************************************
 * Draws the results at the end of the game.
 ****************************************************************/
void Game::drawResults()
{
	if (!ship.isAlive())
	{
		//draws Game Over
		Point gameOver;
		gameOver.setX(tL.getX() + 130);
		gameOver.setY(tL.getY() - 150);

		drawText(gameOver, "Game Over");

		//Draws Final Score
		Point fScore;
		fScore.setX(tL.getX() + 130);
		fScore.setY(tL.getY() - 190);

		Point fPoints;
		fPoints.setX(tL.getX() + 300);
		fPoints.setY(tL.getY() - 182);

		drawText(fScore, "Final Score: ");
		drawNumber(fPoints, getScore());

		//Draws level reached
		Point fLevel;
		fLevel.setX(tL.getX() + 130);
		fLevel.setY(tL.getY() - 230);

		Point flNum;
		flNum.setX(tL.getX() + 300);
		flNum.setY(tL.getY() - 222);

		drawText(fLevel, "Level Reached: ");
		drawNumber(flNum, getLevel());

		//Draws number of asteroids destroyed
		Point AstroDes;
		AstroDes.setX(tL.getX() + 130);
		AstroDes.setY(tL.getY() - 270);

		Point numAstro;
		numAstro.setX(tL.getX() + 300);
		numAstro.setY(tL.getY() - 262);

		drawText(AstroDes, "Asteroids destroyed: ");
		drawNumber(numAstro, getDestroyed());
	}
}

