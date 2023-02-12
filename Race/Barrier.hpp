#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <cmath>

#include "GameObject.hpp"
#include "Car.hpp"

class Barrier : public GameObject {
private:
	void checkBorder() override;

public:
	void setBarrier(float x, float y, b2World& world, int n);
	void setSprite(sf::Sprite& sprite);
	void Update() override;

	sf::Sprite getSprite();
	b2Body* getBody();
};

inline void Barrier::checkBorder() {
	float _x = _sprite.getPosition().x;
	float _y = _sprite.getPosition().y;

	if (_x >= SCREEN_WIDTH + CAR_SIDE) {
		_sprite.setPosition(_x - SCREEN_WIDTH - BARRIER_WIDTH, _y);
		_x = _sprite.getPosition().x;

		_body->SetTransform(b2Vec2(_x / SCALE, _y / SCALE), _body->GetAngle());
	}

	if (_x <= -CAR_SIDE) {
		_sprite.setPosition(_x + SCREEN_WIDTH + BARRIER_WIDTH, _y);
		_x = _sprite.getPosition().x;

		_body->SetTransform(b2Vec2(_x / SCALE, _y / SCALE), _body->GetAngle());
	}
}

inline void Barrier::setBarrier(float x, float y, b2World& world, int n) {
	_shape.SetAsBox(BARRIER_WIDTH / 2 / SCALE, BARRIER_HEIGHT / 2 / SCALE);
	_bodyDef.type = b2_dynamicBody;
	_bodyDef.position.Set(x / SCALE, y / SCALE);
	_body = world.CreateBody(&_bodyDef);
	_body->CreateFixture(&_shape, 1);
	_sprite.setPosition(x, y);
}

inline void Barrier::setSprite(sf::Sprite& sprite) {
	_sprite = sprite;
}

inline void Barrier::Update() {
	b2Vec2 pos = _body->GetPosition();
	_sprite.setPosition(pos.x * SCALE, pos.y * SCALE);
	_sprite.setRotation(_body->GetAngle() * DEG);

	checkBorder();
}

inline sf::Sprite Barrier::getSprite()
{
	return _sprite;
}

inline b2Body* Barrier::getBody()
{
	return _body;
}
