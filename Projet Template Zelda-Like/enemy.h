#pragma once

#include "player.h"
#include "mapEntities.h"

class Player;

class Enemy : public Entity {
public:
	std::string type;
	float health = 30;
	float atk = 0;

	sf::Color originalColor = sf::Color::White;
	float damageTimer = 0;
	float damageDuration = 0.5f;

	Enemy();
	~Enemy();

	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window, sf::Sprite& sprite1, sf::Sprite& sprite2, sf::Texture& texture1, sf::Texture& texture2) override;

	virtual void behavior(float& deltaTime, sf::View& view, std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls, Player& player);
	virtual void takeDamage(float damage);
};
