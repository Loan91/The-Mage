#pragma once

#include "entity.h"
#include "enemy.h"
#include "mapEntities.h"
#include "bomb.h"
#include "key.h"
#include "heart.h"

class Enemy;

class Player : public Entity {
public:
	bool hitboxVisible = false;
	float hp = 100;
	float hpMax = 100;
	sf::Text hpText;
	float atk = 10;
	float bombAtk = atk * 3;
	bool potion = false;
	bool pnj = false;
	bool pnjMove = false;
	float potionTimer = 0;
	float baseSpeed = 300;
	bool key1 = false;
	bool lock1opened = false;
	sf::Vector2f checkpoint = { 75, 75 };
	bool gotHit = false;
	float invincibleTimer = 0;
	float invincibleLimit = 3;

	std::vector<std::shared_ptr<Interactable>> inventaire;
	int bombCount = 0;
	int bombCountMax = 5;
	sf::Text bombText;
	float bombThrowTimer = 0;
	float bombThrowCooldown = 2;
	bool throwingOneAtATime = false;
	std::vector<std::shared_ptr<Bomb>> moovingBomb;
	float lastSpeedX = 0;
	float lastSpeedY = 0;
	bool hitLimit = false;

	sf::Sprite sword1, sword2, sword3;
	sf::Texture sword1Texture, sword2Texture, sword3Texture;

	sf::RectangleShape attackHitbox;
	bool isAttacking = false;
	float attackDuration = 0.2f;
	float attackTimer = 0;
	sf::Vector2f attackOffset;
	sf::Vector2f swordOffset;

	float attackCooldown;
	float attackCooldownTimer;

	sf::Vector2f mousePos = { 0,0 };
	sf::Vector2f playerPos = { 0,0 };
	sf::Vector2f direction = { 0,0 };

	Player();
	void update(float deltaTime) override;
	void draw(sf::RenderWindow& window, sf::Sprite& sprite1, sf::Sprite& sprite2, sf::Texture& texture1, sf::Texture& texture2) override;

	void handleInput(float deltaTime, sf::RenderWindow& window, sf::Sprite wall, std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls, sf::View& view, std::vector<std::unique_ptr<Enemy>>& enemies, sf::Sound& slashSound);

	float checkpointHp = 100;
	bool checkpointKey1 = false;
	bool checkpointLock1opened = false;
	std::vector<std::shared_ptr<Interactable>> checkpointInventaire;
	void checkpointUpdate();
	void checkpointResetPlayer();
};
