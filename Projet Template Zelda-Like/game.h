#pragma once

#include "includes.h"
#include "player.h"
#include "chaser.h"
#include "patrolling.h"
#include "bomb.h"
#include "key.h"
#include "map.h"


class Game {
private:
	float volume;
public:
	bool start = true;
	sf::RenderWindow window;
	sf::View view;
	Player player;
	Map theMap;
	sf::Clock Clock;
	float deltaTime = 0;
	bool playing = false;
	bool win = false;
	bool gameOver = false;
	bool pause = false;
	bool pnjPositionReached = false;
	sf::Vector2f pnjFinalPosition = { 0,0 };

	sf::Texture playerTexture;
	sf::Texture chaserTexture;
	sf::Texture patrollingTexture;
	sf::Texture bombTexture;
	sf::Texture keyTexture;
	sf::Texture wallTexture;
	sf::Texture breakableWallTexture;
	sf::Texture wallDebrisTexture;
	sf::Texture floorTexture;
	sf::Texture lockTexture;
	sf::Texture pnjTexture;
	sf::Texture checkpointTexture;
	sf::Texture checkpointOnTexture;
	sf::Texture explosionTexture;
	sf::Texture bossTexture;
	sf::Texture projectileTexture;
	sf::Texture heartTexture;

	float pnjMoveTime = 0.f;
	const float pnjMoveDuration = 3.f;
	float pnjMoveDistance = 0.f;
	const float maxDistance = 200.f;

	sf::Sprite keyIcone;
	sf::Sprite bombIcone;
	sf::Sprite heartIcone;
	sf::Sprite wallSprite;
	sf::Sprite floorSprite;
	sf::Sprite lockSprite;
	sf::Sprite pnjSprite;
	sf::Sprite explosionSprite;

	sf::Font baseFont;
	sf::Text winText;
	sf::Text menuText;
	sf::Text volumeText;
	sf::Text gameOverText;
	sf::Text retryText;
	sf::Text reprendreText;
	sf::Text optionText;
	sf::Text dialogue;
	sf::Text backText;

	sf::Music musicSound;
	sf::SoundBuffer swordSlashBuffer;
	sf::SoundBuffer explosionBuffer;
	sf::Sound swordSlashSound;
	sf::Sound explosionSound;

	float dialogueTimer = 0.0f;
	float dialogueLimit = 3.0f;
	std::string dialogueText = "";

	Game(std::vector<sf::VideoMode> modes);

	void loadTextures();
	void gameLoop();
	void pollEvent();
	void showMenu();
	void loadFont();
	void showOptionsMenu();
	void updateAll();
	void drawAll();
	void reset();
	void run();
};