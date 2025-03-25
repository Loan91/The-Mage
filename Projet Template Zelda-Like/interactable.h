#pragma once

#include "includes.h"

class Interactable {
public:
	std::string keyNumber = "null";
	float posX = 0;
	float posY = 0;
	bool state = true;
	std::string type;
	sf::Sprite sprite;
	float regen = 0;

	Interactable();

	virtual bool interact(sf::Sprite& playerSprite, std::vector<std::shared_ptr<Interactable>>& mapObjects,std::vector<std::shared_ptr<Interactable>>& inventaire) = 0;
	//void destroy(std::vector<Interactable>& objects);
};
