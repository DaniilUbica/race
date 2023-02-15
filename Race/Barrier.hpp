#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "GameObject.hpp"
#include "Car.hpp"

class Barrier : public GameObject {
private:
	float _dec;

public:
	Barrier();
	void setBarrier(float x, float y);
	void Update();

	float getX() override;
	float getY() override;
	float getSpeed() override;
	float getMass() override;
	float getAngle() override;
	sf::Sprite getSprite();

	void setX(float x) override;
	void setY(float y) override;
	void setSpeed(float speed) override;
	void setAngle(float angle) override;
	void setSprite(sf::Sprite& sprite);

};

Barrier::Barrier() {
	_x = 0;
	_y = 60;
	_dec = 0.00003;
	_speed = _angle = 0;
	_mass = 1.0;

	_sprite.setOrigin(0, 0);
	_sprite.setPosition(_x, _y);
}

inline void Barrier::setBarrier(float x, float y) {
	_x = x;
	_y = y;
	_sprite.setPosition(x, y);
}

inline void Barrier::setSprite(sf::Sprite& sprite) {
	_sprite = sprite;
}

inline void Barrier::Update() {
	_x += sin(_angle) * _speed;
	_y -= cos(_angle) * _speed;

	if (_speed - _dec > 0) {
		_speed -= _dec;
	}
	else if (_speed + _dec < 0) {
		_speed += _dec;
	}
	else {
		_speed = 0;
	}

	_sprite.setRotation(_angle * 180 / PI);
	_sprite.setPosition(_x, _y);

	checkBorders();
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

inline void Barrier::setAngle(float angle) {
	_angle = angle;
}

float Barrier::getAngle()
{
	return _angle;
}
