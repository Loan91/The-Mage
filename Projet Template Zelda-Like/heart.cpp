#include "heart.h"

Heart::Heart() {}

Heart::Heart(std::string t, float xPos, float yPos) {
	sprite.setPosition(xPos, yPos);
	type = t;
	posX = xPos;
	posY = yPos;
	regen = 30;
}

bool Heart::interact(sf::Sprite& playerSprite, std::vector<std::shared_ptr<Interactable>>& mapObjects, std::vector<std::shared_ptr<Interactable>>& inventaire) {
	if (playerSprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
		state = false;
		return true;
	}

	else { return false; }
}