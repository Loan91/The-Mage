#pragma once

#include "interactable.h"

class Key : public Interactable {
public:

	Key(std::string keyNb);
	Key(std::string keyNb, float xPos, float yPos);

	bool interact(sf::Sprite& playerSprite, std::vector<std::shared_ptr<Interactable>>& mapObjects, std::vector<std::shared_ptr<Interactable>>& inventaire) override;
};