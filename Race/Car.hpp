#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Globals.h"
#include "GameObject.hpp"

enum Direction {
	STOP,
	UP,
	DOWN,
	RIGHT,
	LEFT,
};

class Car : public GameObject {
private:
	float _x, _y;
	float _speed, _angle;
	float _acc, _dec;
	Direction _direction;

	void checkBorder();

public:

	Car(sf::Sprite sprite);

	void setDirection(Direction direction);

	void Update();

	float getX();
	float getY();
	float getAngle();
	float getSpeed();
	sf::Sprite getSprite();
	Direction getDirection();

	void setPosition(float x, float y);
	void setSpeed(float speed);
};

Car::Car(sf::Sprite sprite) {
	_sprite = sprite;
	_x = 60;
	_y = 600;
	_speed = _angle = 0;
	_acc = 0.0002;
	_dec = 0.0003;
	_direction = STOP;

	_sprite.setPosition(_x, _y);
}

void Car::setDirection(Direction direction) {
	_direction = direction;
}

inline void Car::checkBorder() {
	if (_x >= SCREEN_WIDTH + CAR_SIDE) {
		_x = _x - SCREEN_WIDTH - CAR_SIDE;
		_sprite.setPosition(_x, _y);
	}

	if (_x <= -CAR_SIDE) {
		_x = _x + SCREEN_WIDTH + CAR_SIDE;
		_sprite.setPosition(_x, _y);
	}
}

void Car::Update() {
	if (_direction == UP && _speed < MAX_SPEED) {
		if (_speed < 0) {
			_speed += _dec;
		}
		else {
			_speed += _acc;
		}
	}

	if (_direction == DOWN && _speed > -MAX_SPEED / 2) {
		if (_speed > 0) {
			_speed -= _dec;
		}
		else {
			_speed -= _acc;
		}
	}

	if (_direction == RIGHT && _speed != 0) {
		_angle += TURN_SPEED * _speed / (MAX_SPEED*10);
	}

	if (_direction == LEFT && _speed != 0) {
		_angle -= TURN_SPEED * _speed / (MAX_SPEED * 10);
	}

	if (_direction == STOP) {
		if (_speed - _dec > 0) {
			_speed -= _dec;
		}
		else if (_speed + _dec < 0) {
			_speed += _dec;
		}
		else {
			_speed = 0;
		}
	}

	_x += sin(_angle) * _speed;
	_y -= cos(_angle) * _speed;

	_sprite.setRotation(_angle * 180 / PI);
	_sprite.setPosition(_x, _y);
	checkBorder();
}

float Car::getX()
{
	return _x;
}

float Car::getY()
{
	return _y;
}

float Car::getAngle()
{
	return _angle;
}

inline float Car::getSpeed()
{
	return _speed;
}

sf::Sprite Car::getSprite()
{
	return _sprite;
}

inline Direction Car::getDirection()
{
	return _direction;
}

inline void Car::setPosition(float x, float y) {
	_x = x;
	_y = y;
}

inline void Car::setSpeed(float speed) {
	_speed = speed;
}
