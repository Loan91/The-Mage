#pragma once

#include "interactable.h"

class Heart : public Interactable {
public:

	Heart();
	Heart(std::string type, float xPos, float yPos);

	bool interact(sf::Sprite& playerSprite, std::vector<std::shared_ptr<Interactable>>& mapObjects, std::vector<std::shared_ptr<Interactable>>& inventaire) override;
};