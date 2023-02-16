#include "Barrier.h"

Barrier::Barrier() {
	_x = 0;
	_y = 60;
	_dec = 0.000015;
	_speed = _angle = 0;
	_mass = 2.0;

	_sprite.setOrigin(0, 0);
	_sprite.setPosition(_x, _y);
}

void Barrier::checkBorders() {
	if (_x >= SCREEN_WIDTH + BARRIER_WIDTH / 2) {
		_x = _x - SCREEN_WIDTH - BARRIER_WIDTH / 2;
		_sprite.setPosition(_x, _y);
	}

	if (_x <= -BARRIER_WIDTH / 2) {
		_x = _x + SCREEN_WIDTH + BARRIER_WIDTH / 2;
		_sprite.setPosition(_x, _y);
	}
}

void Barrier::setBarrier(float x, float y) {
	_x = x;
	_y = y;
	_sprite.setPosition(x, y);
}

void Barrier::Update() {
	_x += sin(_angle) * _speed;
	_y -= cos(_angle) * _speed;

	if (_speed - _dec > 0) {
		_speed -= _dec / _mass;
	}
	else if (_speed + _dec < 0) {
		_speed += _dec / _mass;
	}
	else {
		_speed = 0;
	}

	_sprite.setRotation(_angle * 180 / PI);
	_sprite.setPosition(_x, _y);

	checkBorders();
}