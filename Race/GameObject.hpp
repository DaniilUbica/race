#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class GameObject {
protected:
	sf::Sprite _sprite;
	b2PolygonShape _shape;
	b2BodyDef _bodyDef;
public:
	b2Body* _body;

	virtual void checkBorder() = 0;
	virtual void Update() = 0;
};