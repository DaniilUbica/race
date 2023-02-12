#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <box2d/box2d.h>

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

	Car(sf::Sprite sprite, b2World& world);

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

Car::Car(sf::Sprite sprite, b2World& world) {
	_sprite = sprite;
	_x = 60;
	_y = 600;
	_speed = _angle = 0;
	_acc = 0.002;
	_dec = 0.003;
	_direction = STOP;

	_shape.SetAsBox(CAR_SIDE / 2 / SCALE, CAR_SIDE / 2 / SCALE);
	_bodyDef.type = b2_dynamicBody;
	_bodyDef.position.Set(_x / SCALE, _y / SCALE);
	_bodyDef.fixedRotation = true;
	_body = world.CreateBody(&_bodyDef);
	_body->CreateFixture(&_shape, 1);
	//_body->GetAngle();
	_sprite.setPosition(_x, _y);
	_sprite.setRotation(_body->GetAngle()*DEG);
}

void Car::setDirection(Direction direction) {
	_direction = direction;
}

inline void Car::checkBorder() {
	if (_x >= SCREEN_WIDTH + CAR_SIDE) {
		_x = _x - SCREEN_WIDTH - CAR_SIDE;
		_body->SetTransform(b2Vec2(_x / SCALE, _y / SCALE), _body->GetAngle());
	}

	if (_x <= -CAR_SIDE) {
		_x = _x + SCREEN_WIDTH + CAR_SIDE;
		_body->SetTransform(b2Vec2(_x / SCALE, _y / SCALE), _body->GetAngle());
	}
}

void Car::Update() {
	b2Vec2 velocity = _body->GetLinearVelocity();

	std::cout << _body->GetAngle() * DEG << "\n";

	if (_body->GetAngle() > 360 / DEG || _body->GetAngle() < -360 / DEG) {
		_body->SetTransform(_body->GetPosition(), 0);
	}

	if (_direction == UP && velocity.y < MAX_SPEED / SCALE) {

		/// UP ///
		if (_body->GetAngle() < 45 / DEG && _body->GetAngle() > -45 / DEG) {
			velocity.x = 0;
			velocity.y -= _acc;
			velocity.x = velocity.x * cos(_body->GetAngle()) - velocity.y * sin(_body->GetAngle());
		}

		/// DOWN ///
		if ((_body->GetAngle() > 135 / DEG && _body->GetAngle() < 225 / DEG) 
			|| (_body->GetAngle() < -135 / DEG && _body->GetAngle() > -225 / DEG)) {
			velocity.x = 0;
			velocity.y += _acc;
			velocity.x = -(velocity.x * cos(_body->GetAngle()) - velocity.y * sin(_body->GetAngle()));
		}

		/// RIGHT ///
		if ((_body->GetAngle() > 45 / DEG && _body->GetAngle() < 135 / DEG) 
			|| (_body->GetAngle() < -225 / DEG && _body->GetAngle() > -315 / DEG)) {
			velocity.y = 0;
			velocity.x += _acc;
			velocity.y = velocity.x * cos(_body->GetAngle()) + velocity.y * sin(_body->GetAngle());
			velocity.y *= -1;
		}

		/// LEFT ///
		if ((_body->GetAngle() < -45 / DEG && _body->GetAngle() > -135 / DEG) 
			|| (_body->GetAngle() > 225 / DEG && _body->GetAngle() < 315 / DEG)) {
			velocity.y = 0;
			velocity.x -= _acc;
			velocity.y = velocity.x * cos(_body->GetAngle()) + velocity.y * sin(_body->GetAngle());
		}
	}

	if (_direction == DOWN && velocity.y < MAX_SPEED / SCALE) {
		/// UP ///
		if (_body->GetAngle() < 45 / DEG && _body->GetAngle() > -45 / DEG) {
			velocity.x = 0;
			velocity.y += _acc;
			velocity.x = velocity.x * cos(_body->GetAngle()) - velocity.y * sin(_body->GetAngle());
		}

		/// DOWN ///
		if ((_body->GetAngle() > 135 / DEG && _body->GetAngle() < 225 / DEG)
			|| (_body->GetAngle() < -135 / DEG && _body->GetAngle() > -225 / DEG)) {
			velocity.x = 0;
			velocity.y -= _acc;
			velocity.x = -(velocity.x * cos(_body->GetAngle()) - velocity.y * sin(_body->GetAngle()));
		}

		/// RIGHT ///
		if ((_body->GetAngle() > 45 / DEG && _body->GetAngle() < 135 / DEG)
			|| (_body->GetAngle() < -225 / DEG && _body->GetAngle() > -315 / DEG)) {
			velocity.y = 0;
			velocity.x -= _acc;
			velocity.y = velocity.x * cos(_body->GetAngle()) + velocity.y * sin(_body->GetAngle());
			velocity.y *= -1;
		}

		/// LEFT ///
		if ((_body->GetAngle() < -45 / DEG && _body->GetAngle() > -135 / DEG)
			|| (_body->GetAngle() > 225 / DEG && _body->GetAngle() < 315 / DEG)) {
			velocity.y = 0;
			velocity.x += _acc;
			velocity.y = velocity.x * cos(_body->GetAngle()) + velocity.y * sin(_body->GetAngle());
		}
	}

	if (_direction == LEFT) {
		_body->SetTransform(_body->GetPosition(), _body->GetAngle() - 0.2 / DEG);
	}

	if (_direction == RIGHT) {
		_body->SetTransform(_body->GetPosition(), _body->GetAngle() + 0.2 / DEG);
	}

	if (_direction == STOP) {
		velocity.x = 0;
		velocity.y = 0;
	}

	_body->SetLinearVelocity(velocity);

	b2Vec2 pos = _body->GetPosition();
	_x = pos.x * SCALE;
	_y = pos.y * SCALE;
	_sprite.setPosition(_x, _y);
	_sprite.setRotation(_body->GetAngle() * DEG);

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
