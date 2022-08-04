#pragma once
class Velocity
{
public:
	Velocity()
	{
		dx = 0.0;
		dy = 0.0;
	}
	Velocity(float x, float y)
	{
		dx = x;
		dy = y;
	}

	float getDx() const;
	float getDy() const;
	void setDx(float dx);
	void setDy(float dy);

protected:
	float dx;
	float dy;

};
