#pragma once

#include "enemy.h"
#include "map.h"

class PatrollingEnemy : public Enemy {
public:
	std::vector<float> randomSpeed = { 100, -100, 125, -125, 150, -150 };

	PatrollingEnemy(float xPos, float yPos);

	void behavior(float& deltaTime, sf::View& view, std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls, Player& player) override;
};