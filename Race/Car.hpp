#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Globals.h"

enum Direction {
	STOP,
	UP,
	DOWN,
	RIGHT,
	LEFT,
};


class Car {
private:
	sf::Sprite _sprite;
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

	void setPosition(float x, float y);
};

inline void Car::checkBorder() {
	if (_x >= SCREEN_WIDTH + CAR_SIDE) {
		_x = _x - SCREEN_WIDTH - CAR_SIDE;
	}

	if (_x <= -CAR_SIDE) {
		_x = _x + SCREEN_WIDTH + CAR_SIDE;
	}
}

Car::Car(sf::Sprite sprite) {
	_sprite = sprite;
	_x = 60;
	_y = 600;
	_speed = _angle = 0;
	_acc = 0.0002;
	_dec = 0.0003;
	_direction = STOP;
}

void Car::setDirection(Direction direction) {
	_direction = direction;
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

	if (_direction == DOWN && _speed > -MAX_SPEED) {
		if (_speed > 0) {
			_speed -= _dec;
		}
		else {
			_speed -= _acc;
		}
	}

	if (_direction == STOP) {
		if (_speed > 0) {
			_speed -= _dec;
		}
		else if (_speed < 0) {
			_speed += _dec;
		}
		else {
			_speed = 0;
		}
	}

	if (_direction == RIGHT) {
		_angle += TURN_SPEED * _speed / MAX_SPEED;
	}

	if (_direction == LEFT) {
		_angle -= TURN_SPEED * _speed / MAX_SPEED;
	}

	_x += sin(_angle) * _speed;
	_y -= cos(_angle) * _speed;

	_sprite.setPosition(_x, _y);
	_sprite.setRotation(_angle * 180 / PI);

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

inline void Car::setPosition(float x, float y) {
	_x = x;
	_y = y;
}
