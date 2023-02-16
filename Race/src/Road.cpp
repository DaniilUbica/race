#include "Road.h"

Road::Road(sf::Sprite& sprite, sf::Sprite spriteBarrier, Car* car) {
	srand(time(NULL));

	_sprite = sprite;
	_sprite2 = sprite;

	_sprite.setPosition(0, 0);
	_sprite2.setPosition(_sprite.getPosition().x, _sprite.getPosition().y - ROAD_LENGTH);

	float x = rand() % (SCREEN_WIDTH - BARRIER_WIDTH) + 0;
	float y = rand() % int((car->getY() - 2000)) + (car->getY() - 1000);

	barrier.setSprite(spriteBarrier);
	barrier.setBarrier(float(x), float(y));
}

void Road::Update(Car* car) {

	if (car->getY() < _sprite.getPosition().y - SCREEN_HEIGHT / 2) {
		_sprite.setPosition(_sprite2.getPosition().x, _sprite2.getPosition().y - ROAD_LENGTH);
	}

	if (car->getY() < _sprite2.getPosition().y - SCREEN_HEIGHT / 2) {
		_sprite2.setPosition(_sprite.getPosition().x, _sprite.getPosition().y - ROAD_LENGTH);
	}
}

inline Barrier Road::getBarrier()
{
	return barrier;
}

std::pair<sf::Sprite, sf::Sprite> Road::getSprite()
{
	return { _sprite, _sprite2 };
}
