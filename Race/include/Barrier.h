#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

#include "GameObject.h"
#include "Globals.h"

class Barrier : public GameObject {
private:
	float _dec;

	void checkBorders() override;

public:
	Barrier();
	void setBarrier(float x, float y);
	void Update();
};
