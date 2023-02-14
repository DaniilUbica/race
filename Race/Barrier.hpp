#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "GameObject.hpp"
#include "Car.hpp"

class Barrier : public GameObject {
public:
	Barrier();
	void setBarrier(float x, float y);
	void setSprite(sf::Sprite& sprite);
	void Update();

	sf::Sprite getSprite();

	float getX() override;
	float getY() override;
	float getSpeed() override;
	float getMass() override;

	void setX(float x) override;
	void setY(float y) override;
	void setSpeed(float speed) override;

	float getAngle() override;
};

Barrier::Barrier() {
	_x = 0;
	_y = 60;
	_speed = _angle = 0;
	_mass = 2;

	_sprite.setPosition(_x, _y);
}

inline void Barrier::setBarrier(float x, float y) {
	_sprite.setPosition(x, y);
}

inline void Barrier::setSprite(sf::Sprite& sprite) {
	_sprite = sprite;
}

inline void Barrier::Update() {

}

inline sf::Sprite Barrier::getSprite()
{
	return _sprite;
}

float Barrier::getX()
{
	return _x;
}

float Barrier::getY()
{
	return _y;
}

inline float Barrier::getSpeed()
{
	return _speed;
}

inline float Barrier::getMass()
{
	return _mass;
}

inline void Barrier::setX(float x)
{
	_x = x;
}

inline void Barrier::setY(float y)
{
	_y = y;
}

inline void Barrier::setSpeed(float speed) {
	_speed = speed;
}

float Barrier::getAngle()
{
	return _angle;
}
