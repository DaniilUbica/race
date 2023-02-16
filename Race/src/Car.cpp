#include "Car.h"

Car::Car(sf::Sprite sprite) {
	_sprite = sprite;
	_x = 300;
	_y = 600;
	_speed = _angle = 0;
	_mass = 2.0f;
	_acc = 0.00002f;
	_dec = 0.00003f;
	_direction = STOP;

	_sprite.setPosition(_x, _y);
}

void Car::checkBorders() {
	if (_x >= SCREEN_WIDTH + CAR_SIDE) {
		_x = _x - SCREEN_WIDTH - CAR_SIDE;
		_sprite.setPosition(_x, _y);
	}

	if (_x <= -CAR_SIDE) {
		_x = _x + SCREEN_WIDTH + CAR_SIDE;
		_sprite.setPosition(_x, _y);
	}
}

void Car::setDirection(Direction direction) {
	_direction = direction;
}

void Car::Update() {
	if (_direction == UP && _speed < MAX_SPEED) {
		if (_speed < 0) {
			_speed += _dec / _mass;
		}
		else {
			_speed += _acc;
		}
	}

	if (_direction == DOWN && _speed > -MAX_SPEED / 2) {
		if (_speed > 0) {
			_speed -= _dec / _mass;
		}
		else {
			_speed -= _acc;
		}
	}

	if (_direction == RIGHT && _speed != 0) {
		_angle += TURN_SPEED * _speed / (MAX_SPEED * 10);
	}

	if (_direction == LEFT && _speed != 0) {
		_angle -= TURN_SPEED * _speed / (MAX_SPEED * 10);
	}

	if (_direction == STOP) {
		if (_speed - _dec > 0) {
			_speed -= _dec / _mass;
		}
		else if (_speed + _dec < 0) {
			_speed += _dec / _mass;
		}
		else {
			_speed = 0;
		}
	}

	_x += sin(_angle) * _speed;
	_y -= cos(_angle) * _speed;

	_sprite.setRotation(_angle * 180 / PI);
	_sprite.setPosition(_x, _y);
	checkBorders();
}

Direction Car::getDirection()
{
	return _direction;
}