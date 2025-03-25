#pragma once

#include "interactable.h"

class Bomb : public Interactable {
public:
	float direction = 0;
	float speedX = 0;
	float speedY = 0;

	Bomb();
	Bomb(float xPos, float yPos);

	bool interact(sf::Sprite& playerSprite, std::vector<std::shared_ptr<Interactable>>& mapObjects, std::vector<std::shared_ptr<Interactable>>& inventaire) override;
};
