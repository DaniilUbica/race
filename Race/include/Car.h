#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Globals.h"
#include "GameObject.h"

enum Direction {
	STOP,
	UP,
	DOWN,
	RIGHT,
	LEFT,
};

class Car : public GameObject {
private:
	float _acc, _dec;
	Direction _direction;

	void checkBorders() override;
public:

	Car(sf::Sprite sprite);
	void Update();

	Direction getDirection();

	void setDirection(Direction direction);
};
