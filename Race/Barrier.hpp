#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "GameObject.hpp"
#include "Car.hpp"

class Barrier : public GameObject {
public:
	void setBarrier(float x, float y);
	void setSprite(sf::Sprite& sprite);
	void Update();

	sf::Sprite getSprite();
};

inline void Barrier::setBarrier(float x, float y) {
	_sprite.setPosition(x, y);
}

inline void Barrier::setSprite(sf::Sprite& sprite) {
	_sprite = sprite;
}

inline void Barrier::Update() {

}

inline sf::Sprite Barrier::getSprite()
{
	return _sprite;
}