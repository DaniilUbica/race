#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

#include "Globals.h"
#include "Car.h"
#include "Barrier.h"

class Road {
private:
	sf::Sprite _sprite;
	sf::Sprite _sprite2;
	Barrier barrier;

public:
	Road(sf::Sprite& sprite, sf::Sprite spriteBarrier, Car* car);

	void Update(Car* car);
	Barrier getBarrier();

	std::pair<sf::Sprite, sf::Sprite> getSprite();
};
