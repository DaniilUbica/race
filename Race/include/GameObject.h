#pragma once

#include <SFML/Graphics.hpp>

class GameObject {
protected:
	sf::Sprite _sprite;
	float _x, _y, _angle, _speed;
	float _mass;

	virtual void checkBorders() = 0;
public:
	virtual float getX();
	virtual float getY();
	virtual float getSpeed();
	virtual float getMass();
	virtual float getAngle();
	virtual sf::Sprite getSprite();

	virtual void setX(float x);
	virtual void setY(float y);
	virtual void setSpeed(float speed);
	virtual void setAngle(float angle);
	virtual void setSprite(sf::Sprite& sprite);
};
