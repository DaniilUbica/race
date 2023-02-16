#include "GameObject.h"

void GameObject::setSprite(sf::Sprite& sprite) {
	_sprite = sprite;
}


sf::Sprite GameObject::getSprite()
{
	return _sprite;
}

float GameObject::getX()
{
	return _x;
}

float GameObject::getY()
{
	return _y;
}

float GameObject::getSpeed()
{
	return _speed;
}

float GameObject::getMass()
{
	return _mass;
}

void GameObject::setX(float x)
{
	_x = x;
}

void GameObject::setY(float y)
{
	_y = y;
}

void GameObject::setSpeed(float speed) {
	_speed = speed;
}

void GameObject::setAngle(float angle) {
	_angle = angle;
}

float GameObject::getAngle()
{
	return _angle;
}