#pragma once

#include <SFML/Graphics.hpp>

class GameObject {
protected:
	sf::Sprite _sprite;
	float _x, _y, _angle, _speed;
	float _mass;
public:
	virtual float getX() = 0;
	virtual float getY() = 0;
	virtual float getSpeed() = 0;
	virtual float getMass() = 0;

	virtual void setX(float x) = 0;
	virtual void setY(float y) = 0;
	virtual void setSpeed(float speed) = 0;

	virtual float getAngle() = 0;

	virtual sf::Sprite getSprite() = 0;
};