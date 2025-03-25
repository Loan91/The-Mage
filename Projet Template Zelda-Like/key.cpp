
#include "key.h"

Key::Key(std::string keyNb) {
	type = "key";
	keyNumber = keyNb;
}
Key::Key(std::string keyNb, float xPos, float yPos) {
	type = "key";
	keyNumber = keyNb;
	sprite.setPosition(xPos, yPos);
	posX = xPos;
	posY = yPos;
}

bool Key::interact(sf::Sprite& playerSprite, std::vector<std::shared_ptr<Interactable>>& mapObjects, std::vector<std::shared_ptr<Interactable>>& inventaire) {
	if (playerSprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
		//player.key1 = true;
		inventaire.emplace_back(std::make_shared<Key>(keyNumber));
		state = false;
		return true;
	}

	else { return false; }
}
