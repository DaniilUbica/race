#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Car.hpp"

class Barrier {
private:
	sf::Sprite _sprite;

public:
	void setBarrier(float x, float y);
	void setSprite(sf::Sprite& sprite);

	sf::Sprite getSprite();
};

inline void Barrier::setBarrier(float x, float y) {
	_sprite.setPosition(x, y);
}

inline void Barrier::setSprite(sf::Sprite& sprite) {
	_sprite = sprite;
}

inline sf::Sprite Barrier::getSprite()
{
	return _sprite;
}
